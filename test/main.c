#include <stdio.h>
#include <twi_sw.h>
#include <twi_model.h>

twi_model model_obj;
twi_model *model=&model_obj;

static int s_scl_set() {
  
  twi_model_scl_set(model);

  //printf("SCL set\n");
  return 0;
}

static int s_scl_unset() {
  twi_model_scl_unset(model);

  return 0;
}

static int s_sda_set() {
  twi_model_sda_set(model);
  return 0;
}

static int s_sda_unset() {
  twi_model_sda_unset(model);
  return 0;
}

int main(void) {
  int res;

  twi_data twi_obj;
  twi_data *twi=&twi_obj;

  twi_model_init(model,0x4f);
  twi->scl_set  =s_scl_set;
  twi->scl_unset=s_scl_unset;
  twi->sda_set  =s_sda_set;
  twi->sda_unset=s_sda_unset;
  twi_sw_init(twi);

  printf("Test TWI library\n");


  twi_sw_req_read(twi,0x77,0x00);
  res=twi_sw_read(twi,0)<<8;
  res|=twi_sw_read(twi,1);
  twi_sw_stop(twi);


  printf("Read result: %i\n",res);

  return 0;
}
