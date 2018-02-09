/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 * 
 * ST SPI protocol implementation
 */

#include <miosix.h>
#include "spi.h"

using namespace miosix;

typedef Gpio<GPIOA_BASE,5> SCK;
typedef Gpio<GPIOA_BASE,6> MISO;
typedef Gpio<GPIOA_BASE,7> MOSI;

typedef Gpio<GPIOE_BASE,3> CS_acc;
typedef Gpio<GPIOE_BASE,4> CS_matrix;

void Spi::cs_acc_on(){
    CS_acc::low();
    usleep(1);
}

void Spi::cs_acc_off(){
    CS_acc::high();
    usleep(1);
}

void Spi::cs_matrix_on(){
    CS_matrix::low();
    usleep(1);
}

void Spi::cs_matrix_off(){
    CS_matrix::high();
    usleep(1);
}

/**
 * SPI config
 */
void Spi::config(){
    
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN ; //pheripheral clock enabled
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN; //enable clock on GPIO that will be used
    
    //configure pins
    SCK::mode(Mode::ALTERNATE);
    SCK::alternateFunction(5);
    
    MISO::mode(Mode::ALTERNATE);
    MISO::alternateFunction(5);
    
    MOSI::mode(Mode::ALTERNATE);
    MOSI::alternateFunction(5);
    
    CS_acc::mode(Mode::OUTPUT);
    cs_acc_off();

    CS_matrix::mode(Mode::OUTPUT);
    cs_matrix_off();
    
    // reset the SPI registers
    RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST; 
    RCC->APB2RSTR &= !(RCC_APB2RSTR_SPI1RST);
    
    // SPI protocol configuration
    SPI1->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2; //set the lowest baud rate (328kHz)
    SPI1->CR1 &= ~SPI_CR1_CPHA ; //sampling on clock rising edge
    SPI1->CR1 &= ~SPI_CR1_CPOL ; //idle clock low
    SPI1->CR1 &= ~SPI_CR1_DFF ; //8-bit frame
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST ; //msb trasmission
    SPI1->CR1 |= SPI_CR1_SSM ; //software CS management
    SPI1->CR1 |= SPI_CR1_SSI ; //avoid master mode fault
    SPI1->CR2 &= ~SPI_CR2_FRF ; //select the motorola protocol instead of TI
    SPI1->CR1 |= SPI_CR1_MSTR ; //master config
    SPI1->CR1 |= SPI_CR1_SPE ; //spi enabled
}

void Spi::write_acc(uint8_t address, uint8_t data){
    while(SPI1->SR & SPI_SR_BSY){}; //wait while SPI is busy
    
    cs_acc_on(); //start transmission
    transfer(address);
    transfer(data);
    
    while(SPI1->SR & SPI_SR_BSY){}; //wait for the SPI to be free
    cs_acc_off(); //end transmission
}

void Spi::write_matrix(uint8_t address, uint8_t data){
	while(SPI1->SR & SPI_SR_BSY){}; //wait while SPI is busy
	
	cs_matrix_on();
    transfer(address);
    transfer(data);
    
    while(SPI1->SR & SPI_SR_BSY){}; //wait for the SPI to be free
	cs_matrix_off(); //end transmission
}

uint8_t Spi::read_acc(uint8_t address){
    while(SPI1->SR & SPI_SR_BSY){}; //wait while SPI is busy
    cs_acc_on(); //start transmission
    
    //concatenate command bit 1<<7 indicating a read operation
    transfer(address | SPI_READ); //global status returned byte is not of interest

    uint8_t data = 0x00; //dummy write needed by the protocol
    data = transfer(0x00); //here is the data I want to read.     
    
    while(SPI1->SR & SPI_SR_BSY){};
    cs_acc_off(); //end transmission
    
    return data;
}

/**
 * send data and return the reply received 
 * @param  data to send
 * @return reply received
 */
uint8_t Spi::transfer(uint8_t data){
    while((SPI1->SR & SPI_SR_TXE) == 0){}; //wait for the trasnmitter buffer to be empty
    SPI1->DR = data; //write data
    while((SPI1->SR & SPI_SR_RXNE) == 0){}; //wait for the reply
    data = SPI1->DR; //read data
    return data;
}
