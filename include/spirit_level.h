/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef SPIRIT_LEVEL_H
#define	SPIRIT_LEVEL_H
#include <unistd.h>
#include "lis3dsh.h"
#include "led_matrix_driver.h"

class SpiritLevel {
public:   
    void config(short sensitivity);
    void start();
    
private:
	short sensitivity;
	LedMatrix ledMatrix;
	Lis3dsh accelerometer;
};

#endif	/* SPIRIT_LEVEL_H */

