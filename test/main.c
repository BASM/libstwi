#include <stdio.h>
#include <twi_sw.h>

static int s_scl_set() {
  printf("SCL set\n");
  return 0;
}

static int s_scl_unset() {
  printf("SCL unset\n");
  return 0;
}

static int s_sda_set() {
  printf("SDA set\n");
  return 0;
}

static int s_sda_unset() {
  printf("SDA unset\n");
  return 0;
}

int main(void) {
  int res;
//  twi_model model_obj;
//  twi_model *model=model_obj;

  twi_data twi_obj;
  twi_data *twi=&twi_obj;

  twi->scl_set  =s_scl_set;
  twi->scl_unset=s_scl_unset;
  twi->sda_set  =s_sda_set;
  twi->sda_unset=s_sda_unset;
  twi_sw_init(twi);

  printf("Test TWI library\n");


  twi_sw_req_read(twi,0x77,0x00);
  res=twi_sw_read(0)<<8;
  res|=twi_sw_read(1);
  twi_sw_stop();


  printf("Read result: %i\n");

  return 0;
}
