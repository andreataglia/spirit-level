/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * LIS3DSH accelerometer class abstraction. Configures the accellerometer and acquires new measure
 */

#include <miosix.h>
#include "lis3dsh_reg.h"
#include "lis3dsh.h"
#include "IRQhandler.h"
#include "led_matrix_driver.h"
#include "spi.h"

using namespace miosix;

IRQhandler irqHandler;

/**
 * Configure the LIS3DSH accelorometer to acquire measures. 
 * No state machine is necessary.
 */
Lis3dsh::Lis3dsh() {
    spi = Spi::getInstance();

    uint8_t address;
    uint8_t data;

    address = CTRL_REG4;
    data = CTRL_REG4_XEN | CTRL_REG4_YEN; //accelerometer axis enabled
    data |= FREQ_50; //output data rate in Hz
    spi->write_acc(address, data);

    address = CTRL_REG3;
    data = CTRL_REG3_INT1EN; //interrupt1 enabled
    data |= CTRL_REG3_DR_EN; //data ready enabled
    data |= CTRL_REG3_IEA; //interrupt signal active high
    spi->write_acc(address, data);
}

/**
 * Configure the interrupt INT1 and enable it
 */
void Lis3dsh::start(){
    irqHandler.configureAccInterrupt(); //configure interrupt 1 handler
}

/**
 * Wait for the interrupt INT1 to wake up the thread and read the new measure values. 
 * Interrupts happening in the meantime are ignored 
 * @param measure acquired
 */
void Lis3dsh::waitForNewMeasure(short * measure) {
    
    irqHandler.waitForAccMeasure();

    uint8_t lsbX = spi->read_acc(OUT_X_L);
    uint8_t msbX = spi->read_acc(OUT_X_H);
    uint8_t lsbY = spi->read_acc(OUT_Y_L);
    uint8_t msbY = spi->read_acc(OUT_Y_H);

    short Xmeasure = ((msbX << 8) | (lsbX & 0xff));
    Xmeasure /= 16.384;

    short Ymeasure = ((msbY << 8) | (lsbY & 0xff));
    Ymeasure /= 16.384;

    measure[X] = Xmeasure;
    measure[Y] = Ymeasure;

    return;
}