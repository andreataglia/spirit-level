/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * Driver for the led matrix. 
 * Note that also the leds on STM32 Discovery boards are considered as a very simple matrix, identified as the mock matrix
 */

#include <miosix.h>
#include <cmath>
#include "led_matrix_driver.h"
#include "spi.h"

using namespace miosix;

typedef Gpio<GPIOD_BASE, 12> greenLed;
typedef Gpio<GPIOD_BASE, 13> orangeLed;
typedef Gpio<GPIOD_BASE, 14> redLed;
typedef Gpio<GPIOD_BASE, 15> blueLed;

/**
 * Turn off all the leds on the matrix
 */
void LedMatrix::clearDisplay(){
    uint8_t address;
    uint8_t data = 0x00;
    for (int i = 0; i < 8; ++i)
    { 
        address = i+1;
        spi->write_matrix(address, data);
    }
}

/**
 * Config the Led Matrix Controller Max7219
 */
LedMatrix::LedMatrix(){

    greenLed::mode(Mode::OUTPUT);
    orangeLed::mode(Mode::OUTPUT); 
    redLed::mode(Mode::OUTPUT);
    blueLed::mode(Mode::OUTPUT); 

    spi = Spi::getInstance();

    uint8_t address;
    uint8_t data;

    //display test to zero
    address = 0x0F;
    data = 0x00;
    spi->write_matrix(address, data);
    
    //scan limit
    address = 0x0B;
    data = 0x07;
    spi->write_matrix(address, data);

    //led intensity
    address = 0x0A;
    data = 0x07;
    spi->write_matrix(address, data);

    //decode mode
    address = 0x09;
    data = 0x00;
    spi->write_matrix(address, data);

    //shutdown mode
    address = 0x0C;
    data = 0x00;
    spi->write_matrix(address, data);

    //shutdown mode
    address = 0x0C;
    data = 0x01;
    spi->write_matrix(address, data);

    clearDisplay();
}

/**
 * Translate sprite into leds on the matrix
 * @param x_position calculated for the accelerometer
 * @param y_position calculated for the accelerometer
 */
void LedMatrix::printOutSprite(short x_position, short y_position){
    x_position = x_position > 7 ? 7 : x_position;
    x_position = x_position < 1 ? 1 : x_position;
    y_position = y_position > 8 ? 8 : y_position;
    y_position = y_position < 2 ? 2 : y_position;

    clearDisplay();

    //print out sprite
    short y_calculated = (pow(2, y_position-1) + pow(2, y_position-2));
    spi->write_matrix(9-x_position, y_calculated);
    spi->write_matrix(8-x_position, y_calculated);
}

/**
 * Use the leds on the board to highlight the accelerometer position. For debug purposes mainly
 * @param x_position calculated for the accelerometer
 * @param y_position calculated for the accelerometer
 */
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