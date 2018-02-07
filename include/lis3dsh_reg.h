/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef LIS3DSH_REG_H
#define LIS3DSH_REG_H

#define CTRL_REG4   0x20
#define CTRL_REG1   0x21
#define CTRL_REG2   0x22
#define CTRL_REG3   0x23
#define CTRL_REG5   0x24
#define CTRL_REG6   0x25
#define MASK1_A     0x5A
#define MASK1_B     0x59
#define SETT1       0x5B

// Data Out Registers
#define OUT_X_L		0x28
#define OUT_X_H		0x29
#define OUT_Y_L		0x2A
#define OUT_Y_H		0x2B
#define OUT_Z_L		0x2C
#define OUT_Z_H		0x2D

// bitmask of CTRL_REG4
#define CTRL_REG4_XEN   0x01
#define CTRL_REG4_YEN   0x02
#define CTRL_REG4_ZEN   0x04
#define CTRL_REG4_BDU   0x08
#define CTRL_REG4_ODR0  0x10
#define CTRL_REG4_ODR1  0x20
#define CTRL_REG4_ODR2  0x40
#define CTRL_REG4_ODR3  0x80
#define REFERENCE (*((volatile uint8_t*)0x26));

// bitmask of CTRL_REG1
#define CTRL_REG1_SM1_EN    0x01
#define CTRL_REG1_SM1_PIN   0x08
#define CTRL_REG1_HYST0_1   0x20
#define CTRL_REG1_HYST1_1   0x40
#define CTRL_REG1_HYST2_1   0x80

// bitmask of CTRL_REG3
#define CTRL_REG3_STRT      0x01
#define CTRL_REG3_VFILT     0x04
#define CTRL_REG3_INT1EN    0x08
#define CTRL_REG3_INT2EN    0x10
#define CTRL_REG3_IEL       0x20
#define CTRL_REG3_IEA       0x40
#define CTRL_REG3_DR_EN     0x80

// bitmask of MASK1_A
#define MASK1_A_N_V         0x01
#define MASK1_A_P_V         0x02
#define MASK1_A_N_Z         0x04
#define MASK1_A_P_Z         0x08
#define MASK1_A_N_Y         0x10
#define MASK1_A_P_Y         0x20
#define MASK1_A_N_X         0x40
#define MASK1_A_P_X         0x80

// bitmask of MASK1_B
#define MASK1_B_N_V         0x01
#define MASK1_B_P_V         0x02
#define MASK1_B_N_Z         0x04
#define MASK1_B_P_Z         0x08
#define MASK1_B_N_Y         0x10
#define MASK1_B_P_Y         0x20
#define MASK1_B_N_X         0x40
#define MASK1_B_P_X         0x80

// bitmask of SETT1
#define SETT1_SITR          0x01
#define SETT1_R_TAM         0x02
#define SETT1_THR3_MA       0x04
#define SETT1_ABS           0x20
#define SETT1_THR3_SA       0x40
#define SETT1_P_DET         0x80

#endif /* LIS3DSH_REG_H */

