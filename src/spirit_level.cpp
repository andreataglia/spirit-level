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

/**
 * Configure the SpiritLevel class
 * @param sensitivity is the minimum variation in acceleration (in milliG) which is recognized as a change in position
 */
void SpiritLevel::config(short sensitivity){
    this->sensitivity = sensitivity;
    ledMatrix.config();
    accelerometer.config();
    accelerometer.start();
}

/**
 * Wait for a new measure from accelerometer,
 * then compute the position based on a 8x8 available postions,
 * then call the led matrix driver to print the corresponding sprite
 */
void SpiritLevel::start() {
    short measure[2]; 
    short count_x = 0;
    short count_y = 0;
    //central position out of 1..8, 1..8
    short current_x = 4;
    short current_y = 4;
    short new_x;
    short new_y;
    for (;;) 
    {   
        accelerometer.waitForNewMeasure(measure); //wait for the interrupt to get new measure
        
        //compute the position in a linear manner.
        //the negation is due to the board accelerometer axis direction
        new_x = 4 - measure[X]/sensitivity;
        new_y = 5 - measure[Y]/sensitivity;

        //anti-bounce algorithm 
        if (new_x - current_x == 1 || new_x - current_x == -1) {
        	if (count_x < 2){
        		count_x++;
        	} else {
        		count_x=0;
        		current_x = new_x;
        	}
        } else {current_x = new_x; count_x = 0;}

        if (new_y - current_y == 1 || new_y - current_y == -1) {
        	if (count_y < 2){
        		count_y++;
        	} else {
        		count_y=0;
        		current_y = new_y;
        	}
        } else {current_y = new_y; count_y = 0;}

        //print out relative sprite
        ledMatrix.printOutSpriteOnMockLeds(current_x, current_y);
        ledMatrix.printOutSprite(current_x, current_y);
    }
}