/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef SPIRIT_LEVEL_H
#define	SPIRIT_LEVEL_H
#include <unistd.h>

class SpiritLevel {
public:    
    void config(short sensitivity);
    void start();
    
private:
	short sensitivity;
};

#endif	/* SPIRIT_LEVEL_H */

