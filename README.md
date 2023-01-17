# Advanced Debouncer Button

## bd_avr_tools

The main motivation of this code is to manage "parasitic" (Wifi, thermostat, inductive device, ...) received by non insulated digital input connected to an Arduino (Uno, Pro mini, Nano, ...) physical push button.

Concerning me, the legitimacy of this implementation is justified by the fact that the Arduino library called "Debouncer" available in the IDE caused the destruction of the thermostats of 2 of my branded electric radiators.

## Features

  - Generic elpased time management (CElapsed object)
  - Physical button management w/ light efficient algorithm (CSwitch object) :
    - Short push
    - Long push

## Usage
```C++
#include <bdAvrTools.h>

CSwitch button(4); // gives the digital input in ctor (where physical push button is plugged)

void setup()
{   
    button.setup(); // configure the digital input pin
}

void loop()
{   
    if (CLICK_1 == button.getClick())
    {
        // do something when short push occurs
    }
    else if (CLICK_LONG == button.getClick())
    {
        // do stuff when long push occurs
    }
}
```

## Dependencies
  - None
