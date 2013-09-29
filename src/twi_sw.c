#include <twi_sw.h>

#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#endif /*DEBUG*/

int twi_sw_init(twi_data *self) {
  printf("TWI init\n");

  return 0;
}

int twi_sw_req_read(twi_data *self,int addr,int reg) {
  printf("TWI req read %x, %x\n",addr,reg);

  return 0;
}

int twi_sw_read(twi_data *self,int type) {
  printf("TWI read %i\n",type);

  return 0;
}

int twi_sw_stop(twi_data *self) {
  printf("TWI stop\n");

  return 0;
}
