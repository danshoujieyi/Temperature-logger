//#ifndef __IIC_H_ 
//#define __IIC_H_

///* 精确宽度有符号整数类型*/
//typedef   signed          char int8_t;
//typedef   signed short     int int16_t;
//typedef   signed           int int32_t;
//typedef   signed       __int64 int64_t;

//    /* 精确宽度无符号整数类型 */
//typedef unsigned          char uint8_t;
//typedef unsigned short     int uint16_t;
//typedef unsigned           int uint32_t;
//typedef unsigned       __int64 uint64_t;

///* If I2C SEEPROM is tested, make sure FAST_MODE_PLUS is 0.
//For board to board test, this flag can be turned on. */

//#define FAST_MODE_PLUS	0
//#define BUFSIZE			6
//#define MAX_TIMEOUT		0x00FFFFFF

//#define I2CMASTER		0x01
//#define I2CSLAVE		0x02

//#define PCF8594_ADDR	0xA0
//#define READ_WRITE		0x01

//#define RD_BIT			0x01

//#define I2C_IDLE			0
//#define I2C_STARTED			1
//#define I2C_RESTARTED		2
//#define I2C_REPEATED_START	3
//#define DATA_ACK			4
//#define DATA_NACK			5

//#define I2CONSET_I2EN		0x00000040  /* I2C Control Set Register */
//#define I2CONSET_AA			0x00000004
//#define I2CONSET_SI			0x00000008
//#define I2CONSET_STO		0x00000010
//#define I2CONSET_STA		0x00000020

//#define I2CONCLR_AAC		0x00000004  /* I2C Control clear Register */
//#define I2CONCLR_SIC		0x00000008
//#define I2CONCLR_STAC		0x00000020
//#define I2CONCLR_I2ENC		0x00000040

//#define I2DAT_I2C			0x00000000  /* I2C Data Reg */
//#define I2ADR_I2C			0x00000000  /* I2C Slave Address Reg */
//#define I2SCLH_SCLH			0x00000180  /* I2C SCL Duty Cycle High Reg */
//#define I2SCLL_SCLL			0x00000180  /* I2C SCL Duty Cycle Low Reg */
//#define I2SCLH_HS_SCLH		0x00000030  /* Fast Plus I2C SCL Duty Cycle High Reg */
//#define I2SCLL_HS_SCLL		0x00000030  /* Fast Plus I2C SCL Duty Cycle Low Reg */

//extern void I2C_IRQHandler( void );
//extern uint32_t I2CInit( uint32_t I2cMode );
//extern uint32_t I2CStart( void );
//extern uint32_t I2CStop( void );
//extern uint32_t I2CEngine( void );

//#endif
