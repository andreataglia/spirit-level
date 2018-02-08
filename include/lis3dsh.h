/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef LIS3DSH_H
#define	LIS3DSH_H
#include <unistd.h>
#include "spi.h"

const short X=0;
const short Y=1;

class Lis3dsh {
public:    
    void config(Spi &spi);
    void start();
    void waitForNewMeasure(short *measure);
    
private:
	Spi spi;
};

#endif	/* LIS3DSH_H */

