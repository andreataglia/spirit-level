/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef LIS3DSH_H
#define	LIS3DSH_H
#include <unistd.h>

const short X=0;
const short Y=1;

class Lis3dsh {
public:    
    void config(short sensitivity);
    void waitForNewMeasure(short * measure);
    
private:

};

#endif	/* LIS3DSH_H */

