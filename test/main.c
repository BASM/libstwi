#include <twi_sw.h>
#include <twi_model.h>

#define DEBUG
#ifdef DEBUG
#define D(...) ({printf("\033[32mTWI TST> \033[0m");printf(__VA_ARGS__);})
#include <stdio.h>
#endif /*DEBUG*/

twi_model model_obj;
twi_model *model=&model_obj;

static void s_cycle_wait(void *data) {
  D("WAIT\n");
}

static void s_scl_set(void *data) {
  twi_model *model=(twi_model*) data;
  twi_model_scl_set(model);
}

static void s_scl_unset(void *data) {
  twi_model *model=(twi_model*) data;
  twi_model_scl_unset(model);
}

static void s_sda_set(void *data) {
  twi_model *model=(twi_model*) data;
  twi_model_sda_set(model);
}

static void s_sda_unset(void *data) {
  twi_model *model=(twi_model*) data;
  twi_model_sda_unset(model);
}

int main(void) {
  int res;

  twi_data twi_obj;
  twi_data *twi=&twi_obj;

  twi_model_init(model,0x4f);
  twi->scl_up =s_scl_set;
  twi->scl_dn =s_scl_unset;
  twi->sda_up =s_sda_set;
  twi->sda_dn =s_sda_unset;
  twi->cycle_wait=s_cycle_wait;
  twi_sw_init(twi,(void*)model);

  D("Test TWI library\n");


  twi_sw_req_read(twi,0x4f,0x55);
  res=twi_sw_read(twi,0)<<8;
  res|=twi_sw_read(twi,1);
  twi_sw_stop(twi);


  D("Read result: %i\n",res);

  return 0;
}
