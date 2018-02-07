/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * LIS3DSH accelerometer class abstraction. Configures the accellerometer and acquires new measure
 */

#include <miosix.h>
#include "spi.h"
#include "lis3dsh_reg.h"
#include "lis3dsh.h"
#include "IRQhandler.h"

using namespace miosix;

Spi spi;
IRQhandler irqHandler;

/**
 * configure the accelorometer to acquire measures 
 * @param sensitivity : output data rate of the accelerometer
 */
void Lis3dsh::config(short sensitivity) {

    spi.config();

    uint8_t address;
    uint8_t data;

    address = CTRL_REG4;
    data = CTRL_REG4_XEN; //accelerometer axis enabled
    data |= CTRL_REG4_ODR0 | CTRL_REG4_ODR1 ; //output data rate at 100 Hz
    spi.write(address, data);

    address = CTRL_REG3;
    data = CTRL_REG3_INT1EN; //interrupt1 enabled, signals when freefall is detected
    data |= CTRL_REG3_DR_EN; //data ready enabled
    data |= CTRL_REG3_IEA; //interrupt signal active high
    spi.write(address, data);

    address = MASK1_B;
    data = MASK1_B_P_X; //enable positive X
    spi.write(address, data);

    address = MASK1_A;
    data = MASK1_A_P_X; //enable positive X
    spi.write(address, data);

    irqHandler.configureAccInterrupt(); //configure interrupt 1 handler
}

/**
 * @return new measure
 */
short Lis3dsh::waitForNewMeasure() {
    
    irqHandler.waitForAccMeasure();

    uint8_t lsb = spi.read(OUT_X_L);
    uint8_t msb = spi.read(OUT_X_H);

    short measure = ((msb << 8 ) | (lsb & 0xff));
    measure /= 16.384;

    return measure;
}