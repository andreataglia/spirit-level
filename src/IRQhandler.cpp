/*
* @Author: Sinico Matteo, Taglia Andrea
*
* Interrupt handler class
*/

#include "IRQhandler.h"
#include <miosix.h>
#include <miosix/kernel/scheduler/scheduler.h>

using namespace miosix;

typedef Gpio<GPIOE_BASE, 0> MEMS_INT1;

static Thread *waiting=0;

void __attribute__((naked)) EXTI0_IRQHandler()
{
    saveContext();
    asm volatile("bl _Z16EXTI0HandlerImplv");
    restoreContext();
}

void __attribute__((used)) EXTI0HandlerImpl()
{
    EXTI->PR=EXTI_PR_PR0;
    
    if(waiting==0) return;
    waiting->IRQwakeup();
    if(waiting->IRQgetPriority() > Thread::IRQgetCurrentThread()->IRQgetPriority())
        Scheduler::IRQfindNextThread();
    waiting=0;
}

/**
 *  configures the interrupt in line 0 for the accelerometer;
 */
void IRQhandler::configureAccInterrupt()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; //enable GPIOE clock
    MEMS_INT1::mode(Mode::INPUT); //create interrupt on rising edge of the accelerometer interrupt
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // system configuration controller clock enable
    SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PE; //use PE0 for EXTI_Line0
    EXTI->IMR |= EXTI_IMR_MR0; //interrupt request from line 0 is not masked
    EXTI->RTSR |= EXTI_RTSR_TR0; //rising trigger enabled
    
    NVIC_EnableIRQ(EXTI0_IRQn);//EXTI0_IRQn = 6 : EXTI Line0 Interrupt = STM32 specific Interrupt Number 
    NVIC_SetPriority(EXTI0_IRQn,15); //low priority
}

/**
 *  puts the current thread in wait condition until the interrupt is received
 */
void IRQhandler::waitForAccMeasure()
{
    FastInterruptDisableLock dLock;
    waiting=Thread::IRQgetCurrentThread();
    while(waiting)
    {
        Thread::IRQwait(); //since interrupts disabled here the call returns immediately, just the thread wait status bit is set
        FastInterruptEnableLock eLock(dLock); //enable back the interrupt
        Thread::yield(); //the thread actually goes to sleep
    }
}