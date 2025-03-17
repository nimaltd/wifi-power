
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

mp4245::mp4245(int pin_sck, int pin_sda, uint8_t address)
{
  _pin_sck = pin_sck;
  _pin_sda = pin_sda;
  _address = address;
}

bool mp4245::begin(void)
{

  return true;
}

void mp4245::enable(bool enable)
{

}

void mp4245::cfg_set_vout(uint32_t vout_mv)
{

}

void mp4245::cfg_set_iout(uint32_t iout_ma)
{

}

uint32_t mp4245::cfg_get_vout(void)
{

}

uint32_t mp4245::cfg_get_iout(void)
{

}

uint32_t mp4245::get_vin(void)
{

}

uint32_t mp4245::get_current(void)
{

}

