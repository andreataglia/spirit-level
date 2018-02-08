/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * SpiritLevel app logic
 */

#include <miosix.h>
#include "spirit_level.h"
#include "lis3dsh.h"
#include "led_matrix_driver.h"
#include "spi.h"

using namespace miosix;

Lis3dsh accelerometer;
LedMatrix ledMatrix;
Spi spi;

/**
 * Configure the SpiritLevel class
 * @param sensitivity is the minimum variation in acceleration (in milliG) which is recognized as a change in position
 */
void SpiritLevel::config(short sensitivity){
    this->sensitivity = sensitivity;
    spi.config();
    accelerometer.config(spi);
    ledMatrix.config(spi);
    accelerometer.start();
}

/**
 * Wait for a new measure from accelerometer,
 * then compute the position based on a 8x8 available postions,
 * then call the led matrix driver to print the corresponding sprite
 */
void SpiritLevel::start() {
    short measure[2]; 
    //central position is 3,3
    short x_position = 3;
    short y_position = 3;
    for (;;) 
    {   
        accelerometer.waitForNewMeasure(measure); //wait for the interrupt to get new measure
        
        //compute the position in a linear manner.
        //the negation is due to the board accelerometer axis direction
        x_position = 3 - measure[X]/sensitivity;
        y_position = 3 - measure[Y]/sensitivity;

        //print out relative sprite
        ledMatrix.printOutSpriteOnMockLeds(x_position, y_position);
    }
}