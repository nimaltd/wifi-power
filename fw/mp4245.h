
#ifndef _MP4245_H_
#define _MP4245_H_

#include <Wire.h>
#include "config.h"

#define MP4245_I2C_ADDRESS          0x61

class mp4245
{
  public:

  mp4245(int pin_sck, int pin_sda, uint8_t address = MP4245_I2C_ADDRESS);
  ~mp4245(void);

  bool      begin(void);
  void      enable(bool enable);
  void      cfg_set_vout(uint32_t vout_mv);
  void      cfg_set_iout(uint32_t iout_ma);
  uint32_t  cfg_get_vout(void);
  uint32_t  cfg_get_iout(void);
  uint32_t  get_vin(void);
  uint32_t  get_current(void);

  private:
  int _pin_sck = -1;
  int _pin_sda = -1;
  uint8_t _address = 0;
};
#endif
