
#ifndef _MP4245_H_
#define _MP4245_H_

#include "config.h"

#define MP4245_I2C_ADDRESS          0x61
#define MP4245_R1                   90.9f
#define MP4245_R2                   6.2f
#define MP4245_FEEDBACK_RATIO       ((MP4245_R1 + MP4245_R2) / MP4245_R2)

class mp4245
{
  public:

  mp4245(int pin_sda, int pin_sck, int pin_en, uint8_t address = MP4245_I2C_ADDRESS);
  ~mp4245(void);

  bool      begin(void);
  void      enable(bool enable);
  bool      is_enable(void);
  void      cfg_set_vout(uint32_t vout_mv);
  void      cfg_set_iout(uint32_t iout_ma);
  uint32_t  cfg_get_vout(void);
  uint32_t  cfg_get_iout(void);
  uint32_t  get_current(void);
  uint8_t   get_temp(void);

  private:

  void      i2c_write8(uint8_t reg, uint8_t data);
  void      i2c_write16(uint8_t reg, uint16_t data);
  uint8_t   i2c_read8(uint8_t reg);
  uint16_t  i2c_read16(uint8_t reg);
  
  bool _is_enable = false;
  int _pin_sda = -1;
  int _pin_sck = -1;
  int _pin_en = -1;
  uint8_t _address = 0;
};
#endif
