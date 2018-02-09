/* 
 * @Authors: Sinico Matteo, Taglia Andrea
 */

#ifndef SPI_H
#define	SPI_H

#define SPI_READ 1<<7

class Spi {
public:    
    void config();
    void write_acc(uint8_t address, uint8_t data);
    void write_matrix(uint8_t address, uint8_t data);
    uint8_t read_acc(uint8_t address);
    
private:
    void cs_acc_on();
    void cs_acc_off();
    void cs_matrix_on();
    void cs_matrix_off();
    uint8_t transfer(uint8_t data);
};

#endif	/* SPI_H */

