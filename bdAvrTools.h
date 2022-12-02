#pragma once
#include <stdint.h>
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//! @brief the CElapsedTime class provides a simple way to manage timed operations in the loop callback function
#define ELAPSED_NOW static_cast<uint8_t>(1) // to give to ctor in order to isElapsed() return 'true' at 1st call
class CElapsedTime  // used to check if set delay is elapsed
{
public:
    CElapsedTime(uint32_t delayms=0) { start(delayms); }  // disabled by default (delay=0) because of using it in generic derivated object
    ~CElapsedTime() {};

    void start(uint32_t delayms=0)  // start to count requested 'wait' time. If delay is 0, isElapsed() always returns 'false' (component disabled)
    {   if (delayms != 0) {  m_tStart = millis();  }
        m_delayms = delayms;
    }

    bool isElapsed()    // check if requested time is elapsed since previous call of 'start' function
    {   return (m_delayms != 0) && ((millis() - m_tStart) > m_delayms); // overflow (every 49.71 days) is natively managed by unsigned var (and tested w/ simulator)
    }

protected:
    uint32_t    m_tStart;
    uint32_t    m_delayms;
};
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//! @brief the CSwitch class provides a simple way to manage physical push button plugged to a digital AVR pin
enum { CLICK_NONE=0, CLICK_1=1, CLICK_LONG=99 }; // public/private state values
enum { TICK=1, T_SHORT=20, T_LONG=750 };         // timing scan/switch behaviour (millisecond)
//---------------------------------------------------------------------------------------------
class CSwitch // ultra light/efficient button management w/ advanced debounce cancellation
{
public:
    CSwitch(uint8_t pin) : _pin(pin), _cntLow(0), _et(ELAPSED_NOW) { }
    
    void setup() 
    {   pinMode(_pin, INPUT);        
        digitalWrite(_pin, HIGH);                // if pinmode is INPUT, enable (HIGH) or disable (LOW) internal pullup on the input pin        
    }
   
    int8_t getClick()
    {   int8_t ret = CLICK_NONE;
        if (_et.isElapsed())                                    // every TICK ms
        {   if (digitalRead(_pin) == LOW) { ++_cntLow; }
            else
            {   if (_cntLow >= T_LONG) { ret = CLICK_LONG; }    // if down during long time then long click
                else if (_cntLow >= T_SHORT) { ret = CLICK_1; } // if down during short time then short click
                _cntLow = 0;
            }
            _et.start(TICK);                                    // next action in TICK ms
        }
        return ret;
    }

    uint8_t         _pin;
    uint32_t        _cntLow;    // counter incremented during LOW state
    CElapsedTime    _et;
};
//---------------------------------------------------------------------------------------------
