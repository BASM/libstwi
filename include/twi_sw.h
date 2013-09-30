/* Software TWI interface */

typedef struct S_twi_sw_data {
  void *userdata;
  void (*scl_up)    (void *data);
  void (*scl_dn)    (void *data);
  void (*sda_up)    (void *data);
  void (*sda_dn)    (void *data);
  int  (*scl_read)  (void *data);
  void (*cycle_wait)(void *data);
} twi_data;


int twi_sw_init(twi_data *self, void *userdata);
int twi_sw_req_read(twi_data *self,int addr,int reg);
int twi_sw_read(twi_data *self,int type);
int twi_sw_stop(twi_data *self);
