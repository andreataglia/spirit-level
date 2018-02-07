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

Spi spi2;

LedMatrix::LedMatrix(){
    greenLed::mode(Mode::OUTPUT);
    orangeLed::mode(Mode::OUTPUT); 
    redLed::mode(Mode::OUTPUT);
    blueLed::mode(Mode::OUTPUT); 
}

void LedMatrix::config(){
    uint8_t address;
    uint8_t data;

    //display test a zero
    address = 0x0F;
    data = 0x00;
    spi2.writeOnly(address, data);
    
    //scan limit
    address = 0x0B;
    data = 0x07;
    spi2.writeOnly(address, data);

    //decode mode
    address = 0x09;
    data = 0x00;
    spi2.writeOnly(address, data);

    //shutdown mode
    address = 0x0C;
    data = 0x00;
    spi2.writeOnly(address, data);

    //shutdown mode
    address = 0x0C;
    data = 0x01;
    spi2.writeOnly(address, data);

    for (int i = 0; i < 8; ++i)
    { 
        address = i+1;
        data = 0x00;
        spi2.writeOnly(address, data);
    }

    //set row
    address = 0x03;
    data = 0x2F;
    spi2.writeOnly(address, data);

    /////////
}

void LedMatrix::printOutSprite(short x_position, short y_position){
    // if (x_position == 1)
    // {
    //     greenLed::high();
    // } else if(x_position == 2){
    //     orangeLed::high();
    // }
    // else if(x_position == 3){
    //     redLed::high();
    // }
    // else if(x_position == 4){
    //     blueLed::high();
    // }
    
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