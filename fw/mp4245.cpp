#include "esp32-hal-gpio.h"

#include <Arduino.h>
#include <Wire.h>
#include "mp4245.h"

#define I2C_OPERATION                   0x01
#define I2C_CLEAR_FAULTS                0x03
#define I2C_WRITE_PROTECT               0x10
#define I2C_STORE_USER_ALL              0x15
#define I2C_RESTORE_USER_ALL            0x16
#define I2C_VOUT_MODE                   0x20
#define I2C_VOUT_COMMAND                0x21
#define I2C_VOUT_SCALE_LOOP             0x29
#define I2C_STATUS_BYTE                 0x78
#define I2C_STATUS_WORD                 0x79
#define I2C_STATUS_VOUT                 0x7A
#define I2C_STATUS_INPUT                0x7C
#define I2C_STATUS_TEMPERATURE          0x7D
#define I2C_STATUS_CML                  0x7E
#define I2C_READ_VIN                    0x88
#define I2C_READ_VOUT                   0x8B
#define I2C_READ_IOUT                   0x8C
#define I2C_READ_TEMPERATURE            0x8D
#define I2C_MFR_MODE_CTRL               0xD0
#define I2C_MFR_CURRENT_LIMIT           0xD1
#define I2C_MFR_LINE_DROP_COMP          0xD2
#define I2C_MFR_OT_FAULT_LIMIT          0xD3
#define I2C_MFR_OT_WARN_LIMIT           0xD4
#define I2C_MFR_CRC_ERROR_FLAG          0xD5
#define I2C_MFR_MTP_CONFIGURATION_CODE  0xD6
#define I2C_MFR_MTP_REVISION_NUMBER     0xD7
#define I2C_MFR_STATUS_MASK             0xD8

mp4245::mp4245(int pin_sda, int pin_sck, int pin_en, uint8_t address)
{
  _pin_sck = pin_sck;
  _pin_sda = pin_sda;
  _pin_en = pin_en;
  _address = address;
}

bool mp4245::begin(void)
{
  pinMode(_pin_en, OUTPUT);
  digitalWrite(_pin_en, 1);
  if (!Wire.begin(_pin_sda, _pin_sck))
  {
    return false;
  }
  delay(10);
  i2c_write16(I2C_VOUT_SCALE_LOOP, 0xB042); // depends on R1,R2
  return true;
}

void mp4245::enable(bool enable)
{
  i2c_write8(I2C_OPERATION, enable ? 0x80 : 0x00);
}

bool mp4245::is_enable(void)
{
  return i2c_read8(I2C_OPERATION);
}

void mp4245::cfg_set_vout(uint32_t vout_mv)
{
  i2c_write16(I2C_VOUT_COMMAND, (uint16_t)(vout_mv * 1.024f));
}

void mp4245::cfg_set_iout(uint32_t iout_ma)
{
  i2c_write8(I2C_MFR_CURRENT_LIMIT, (uint8_t)(iout_ma / 50));
}

uint32_t mp4245::cfg_get_vout(void)
{
  return (uint32_t)(i2c_read16(I2C_VOUT_COMMAND) / 1.024f);
}

uint32_t mp4245::cfg_get_iout(void)
{
  return i2c_read8(I2C_MFR_CURRENT_LIMIT) * 50;
}

uint32_t mp4245::get_current(void)
{
  uint32_t tmp = 0;
  for (int i = 0; i < 5; i++)
  {
    tmp += (i2c_read16(I2C_READ_IOUT) & 0x07FF) / 64; 
  }
  return tmp / 5;
}


uint8_t mp4245::get_temp(void)
{
  uint32_t tmp = 0;
  for (int i = 0; i < 5; i++)
  {
    tmp += (i2c_read16(I2C_READ_TEMPERATURE) & 0x07FF) / 2; 
  }
  return tmp / 5;
}

// Function to write an 8-bit value to a register
void mp4245::i2c_write8(uint8_t reg, uint8_t data)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

// Function to write a 16-bit value to a register
void mp4245::i2c_write16(uint8_t reg, uint16_t data)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(data & 0xFF);         // Low byte
  Wire.write((data >> 8) & 0xFF);  // High byte
  Wire.endTransmission();
}

// Function to read an 8-bit value from a register
uint8_t mp4245::i2c_read8(uint8_t reg)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission(false); // Restart for repeated read
  Wire.requestFrom(_address, 1);
  if (Wire.available())
  {
    return Wire.read();
  }
  return 0; // Return 0 if no data received
}

// Function to read an 16-bit value from a register
uint16_t mp4245::i2c_read16(uint8_t reg)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission(false); // Restart for repeated read
  Wire.requestFrom(_address, 2);
  if (Wire.available() >= 2)
  {
    uint16_t value = Wire.read(); 
    value |= (Wire.read() << 8);
    return value;
  }
  return 0; // Return 0 if no data received
}


