/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef LIS3DSH_H
#define	LIS3DSH_H
#include <unistd.h>

class Lis3dsh {
public:    
    void config(short sensitivity);
    short waitForNewMeasure();
    
private:

};

#endif	/* LIS3DSH_H */

