#include <stdbool.h>
#include <inttypes.h>

/* Software TWI interface */

typedef struct S_twi_sw_data {
  uint8_t sda,scl;
  void *userdata;
  /* Function need block if SCL is down */
  /* return false if need abort work */
  int  (*scl_rl)    (void *data);
  void (*scl_dn)    (void *data);
  void (*sda_rl)    (void *data);
  void (*sda_dn)    (void *data);
  int  (*sda_read)  (void *data);
  int  (*scl_read)  (void *data);
  void (*cycle_wait)(void *data);
} twi_data;

typedef enum {
  FERROR=-1,
  FTRUE =true,
  FFALSE=false,
} fres;

int twi_sw_init(twi_data *self, void *userdata);
int twi_sw_req_read(twi_data *self,int addr,int reg);
int twi_sw_read(twi_data *self,int type);
int twi_sw_stop(twi_data *self);
