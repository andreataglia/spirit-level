/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * Driver for the led matrix. 
 * Note that also the leds on STM32 Discovery boards are considered as a very simple matrix, identified as the mock matrix
 */

#include <miosix.h>
#include "led_matrix_driver.h"
#include "spi.h"

using namespace miosix;

typedef Gpio<GPIOD_BASE, 12> greenLed;
typedef Gpio<GPIOD_BASE, 13> orangeLed;
typedef Gpio<GPIOD_BASE, 14> redLed;
typedef Gpio<GPIOD_BASE, 15> blueLed;

LedMatrix::LedMatrix(){
    greenLed::mode(Mode::OUTPUT);
    orangeLed::mode(Mode::OUTPUT); 
    redLed::mode(Mode::OUTPUT);
    blueLed::mode(Mode::OUTPUT); 
}

void LedMatrix::printOutSprite(short x_position, short y_position){
    greenLed::high();
}

void LedMatrix::printOutSpriteOnMockLeds(short x_position, short y_position){
    if (x_position >= 5){
        greenLed::high();
        redLed::low();
    } else if (x_position <= 1){
        greenLed::low();
        redLed::high();
    } else{
        greenLed::low();
        redLed::low();
    }

    if (y_position >= 5){
        blueLed::high();
        orangeLed::low();
    } else if (y_position <= 1){
        blueLed::low();
        orangeLed::high();
    } else{
        blueLed::low();
        orangeLed::low();
    }
}