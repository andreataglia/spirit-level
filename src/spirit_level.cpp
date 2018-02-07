/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * SpiritLevel app logic
 */

#include <miosix.h>
#include "spirit_level.h"
#include "lis3dsh.h"
#include "led_matrix_driver.h"

using namespace miosix;

Lis3dsh accelerometer;
LedMatrix ledMatrix;

/**
 * Configure the SpiritLevel class
 * @param sensitivity is the minimum variation in acceleration (in milliG) which is recognized as a change in position
 */
void SpiritLevel::config(short sensitivity){
    this->sensitivity = sensitivity;
    accelerometer.config(sensitivity);
}

/**
 * Wait for a new measure from accelerometer,
 * then compute the position based on a 8x8 available postions,
 * then call the led matrix driver to print the corresponding sprite
 */
void SpiritLevel::start() {
    short measure; 
    //central position is 3,3
    short x_position = 3;
    short y_position = 3;
    for (;;) 
    {   
        measure = accelerometer.waitForNewMeasure();

        short x = 1500;
        short y = 200;
        
        //compute the position in a linear manner.
        x_position = 3 + x/sensitivity;
        y_position = 3 + y/sensitivity;

        //print out relative sprite
        ledMatrix.printOutSpriteOnMockLeds(x_position, y_position);
    }
}