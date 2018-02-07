/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef LED_MATRIX_DRIVER_H
#define	LED_MATRIX_DRIVER_H

class LedMatrix {
public:    
    LedMatrix();
    void printOutSprite(short x_position, short y_position);
    void printOutSpriteOnMockLeds(short x_position, short y_position);
    
private:
    
};

#endif	/* LED_MATRIX_DRIVER_H */

