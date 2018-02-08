/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef LED_MATRIX_DRIVER_H
#define	LED_MATRIX_DRIVER_H

#include "spi.h"

class LedMatrix {
public:    
    LedMatrix();
    void clearDisplay();
    void config(Spi &spiComm);
    void printOutSprite(short x_position, short y_position);
    void printOutSpriteOnMockLeds(short x_position, short y_position);
    
private:
    Spi spi;
};

#endif	/* LED_MATRIX_DRIVER_H */

