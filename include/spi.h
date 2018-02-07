/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef SPI_H
#define	SPI_H

#define SPI_READ 1<<7

class Spi {
public:    
    void config();
    void write(uint8_t address, uint8_t data);
    uint8_t read(uint8_t address);
    
private:
    void csOn();
    void csOff();
    uint8_t transfer(uint8_t data);
};

#endif	/* SPI_H */

