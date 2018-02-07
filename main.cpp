/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * Main class for the SpiritLevel project
 */

#include <miosix.h>
#include <pthread.h>
#include "spirit_level.h"

using namespace miosix;

const short SENSITIVITY = 50;


typedef Gpio<GPIOD_BASE, 13> orangeLed;

void appRunningLed() 
{
    orangeLed::high();
    usleep(1000000);
    orangeLed::low();
    usleep(1000000);
}

SpiritLevel spiritLevel;

/**
 * spirit level application logic thread 
 */
void *spiritLevelLoop(void *arg)
{
    miosix::Thread::getCurrentThread()->setPriority(PRIORITY_MAX-1);
    spiritLevel.start();
    return 0;
}

int main()
{
    pthread_t spiritLevelThread;

    spiritLevel.config(SENSITIVITY);
    pthread_create(&spiritLevelThread, NULL, &spiritLevelLoop, NULL);
    
    for(;;)
    {
        //appRunningLed();
    }
    
    pthread_join(spiritLevelThread,NULL);
    
    return 0;
} 
