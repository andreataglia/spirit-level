/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * SpiritLevel app logic
 */

#include <miosix.h>
#include "spirit_level.h"
#include "lis3dsh.h"

using namespace miosix;

Lis3dsh accelerometer;

typedef Gpio<GPIOD_BASE, 12> greenLed;
typedef Gpio<GPIOD_BASE, 13> orangeLed;
typedef Gpio<GPIOD_BASE, 14> redLed;
typedef Gpio<GPIOD_BASE, 15> blueLed;

void SpiritLevel::config(short sensitivity){
    greenLed::mode(Mode::OUTPUT);
    orangeLed::mode(Mode::OUTPUT); 
    redLed::mode(Mode::OUTPUT);
    blueLed::mode(Mode::OUTPUT); 

    accelerometer.config(sensitivity);
}

/**
 * Wait for a new measure and set the new level based on the measure
 */
void SpiritLevel::start() {
    for (;;) 
    {   
        short measure[2];     
        accelerometer.waitForNewMeasure(measure);

        if (measure[X] > 400) {
            greenLed::low();
            redLed::high();
        } else if (measure[X] < -400){
            redLed::low();
            greenLed::high();
        } else if (measure[Y] > 400){
            blueLed::low();
            orangeLed::high();
        } else if (measure[Y] < -400){
            orangeLed::low();
            blueLed::high();
        } else {
            greenLed::low();
            orangeLed::low();
            redLed::low();
            blueLed::low();
        }
    }
}