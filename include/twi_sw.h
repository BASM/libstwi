/* Software TWI interface */

typedef struct S_twi_sw_data {
  int (*scl_set)(void);
  int (*scl_unset)(void);
  int (*sda_set)(void);
  int (*sda_unset)(void);
} twi_data;


int twi_sw_init(twi_data *self);
int twi_sw_req_read(twi_data *self,int addr,int reg);
int twi_sw_read(twi_data *self,int type);
int twi_sw_stop(twi_data *self);
