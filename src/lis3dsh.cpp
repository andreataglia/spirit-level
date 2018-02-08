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

using namespace miosix;

IRQhandler irqHandler;

/**
 * configure the accelorometer to acquire measures 
 */
void Lis3dsh::config(Spi &spiComm) {
    this->spi = spiComm;

    uint8_t address;
    uint8_t data;

    address = CTRL_REG4;
    data = CTRL_REG4_XEN | CTRL_REG4_YEN; //accelerometer axis enabled
    data |= FREQ_50; //output data rate in Hz
    this->spi.write(address, data);

    address = CTRL_REG3;
    data = CTRL_REG3_INT1EN; //interrupt1 enabled
    data |= CTRL_REG3_DR_EN; //data ready enabled
    data |= CTRL_REG3_IEA; //interrupt signal active high
    this->spi.write(address, data);

    address = MASK1_B;
    data = MASK1_B_P_X | MASK1_B_P_Y; //enable positive X, Y
    this->spi.write(address, data);

    address = MASK1_A;
    data = MASK1_A_P_X | MASK1_A_P_Y; //enable positive X, Y
    this->spi.write(address, data);
}

void Lis3dsh::start(){
    irqHandler.configureAccInterrupt(); //configure interrupt 1 handler
}

/**
 * @return new measure
 */
void Lis3dsh::waitForNewMeasure(short * measure) {
    
    irqHandler.waitForAccMeasure();

    uint8_t lsbX = this->spi.read(OUT_X_L);
    uint8_t msbX = this->spi.read(OUT_X_H);
    uint8_t lsbY = this->spi.read(OUT_Y_L);
    uint8_t msbY = this->spi.read(OUT_Y_H);

    short Xmeasure = ((msbX << 8) | (lsbX & 0xff));
    Xmeasure /= 16.384;

    short Ymeasure = ((msbY << 8) | (lsbY & 0xff));
    Ymeasure /= 16.384;

    measure[X] = Xmeasure;
    measure[Y] = Ymeasure;

    return;
}