/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * Driver for the led matrix. 
 * Note that also the leds on STM32 Discovery boards are considered as a very simple matrix, identified as the mock matrix
 */

#include <miosix.h>
#include <cmath>
#include "led_matrix_driver.h"

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

void LedMatrix::clearDisplay(){
    uint8_t address;
    uint8_t data = 0x00;
    for (int i = 0; i < 8; ++i)
    { 
        address = i+1;
        this->spi.writeOnly(address, data);
    }
}

void LedMatrix::config(Spi &spiComm){

    this->spi = spiComm;

    uint8_t address;
    uint8_t data;

    //display test to zero
    address = 0x0F;
    data = 0x00;
    this->spi.writeOnly(address, data);
    
    //scan limit
    address = 0x0B;
    data = 0x07;
    this->spi.writeOnly(address, data);

    //led intensity
    address = 0x0A;
    data = 0x07;
    this->spi.writeOnly(address, data);

    //decode mode
    address = 0x09;
    data = 0x00;
    this->spi.writeOnly(address, data);

    //shutdown mode
    address = 0x0C;
    data = 0x00;
    this->spi.writeOnly(address, data);

    //shutdown mode
    address = 0x0C;
    data = 0x01;
    this->spi.writeOnly(address, data);

    clearDisplay();
    // for (int i = 0; i < 8; ++i)
    // { 
    //     address = i+1;
    //     data = 0x00;
    //     this->spi.writeOnly(address, data);
    // }

    //set row
    // address = 0x0F;
    // data = 0x01;
    address = 0x07;
    data = 0x2F;
    this->spi.writeOnly(address, data);
}

void LedMatrix::printOutSprite(short x_position, short y_position){
    x_position = x_position > 7 ? 7 : x_position;
    x_position = x_position < 1 ? 1 : x_position;
    y_position = y_position > 8 ? 8 : y_position;
    y_position = y_position < 2 ? 2 : y_position;

    clearDisplay();
    short y_calculated = (pow(2, y_position-1) + pow(2, y_position-2));
    this->spi.writeOnly(9-x_position, y_calculated);
    this->spi.writeOnly(8-x_position, y_calculated);
}

void LedMatrix::printOutSpriteOnMockLeds(short x_position, short y_position){
    if (x_position >= 6){
        greenLed::high();
        redLed::low();
    } else if (x_position <= 2){
        greenLed::low();
        redLed::high();
    } else{
        greenLed::low();
        redLed::low();
    }

    if (y_position >= 7){
        blueLed::high();
        orangeLed::low();
    } else if (y_position <= 3){
        orangeLed::high();
        blueLed::low();
    } else{
        blueLed::low();
        orangeLed::low();
    }
}