/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * Main class for the SpiritLevel project
 */

#include <miosix.h>
#include <pthread.h>
#include "spirit_level.h"

using namespace miosix;

const short SENSITIVITY = 200;

typedef Gpio<GPIOD_BASE, 13> orangeLed;

/**
 * Blink a led, just for debugging purpose, while the application is running 
 */
void appRunningLed() 
{
    orangeLed::high();
    usleep(1000000);
    orangeLed::low();
    usleep(1000000);
}

SpiritLevel spiritLevel;

/**
 * Spirit level application logic thread 
 */
void *spiritLevelLoop(void *arg)
{
    miosix::Thread::getCurrentThread()->setPriority(PRIORITY_MAX-1); //Give priority to the application logic thread
    spiritLevel.start();
    return 0;
}

/**
 * Start the application thread and in the main thread blink a led just to know when the application is running
 */
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
