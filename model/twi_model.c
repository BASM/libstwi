#include <stdio.h>
#include <string.h>
#include <twi_model.h>

#define DEBUG
#ifdef DEBUG
#define D(...) ({printf("\033[33mTWI MOD> \033[0m");printf(__VA_ARGS__);})
#include <stdio.h>
#endif /*DEBUG*/

int twi_model_init(twi_model *self, int addr) {

  memset(self,0,sizeof(twi_model));
  self->addr=addr;
  //0x4f

  return 0;
}


int twi_model_scl_set(twi_model *self) {
  D("SCL_SET\n");
  return 0;
}
int twi_model_scl_unset(twi_model *self) {
  D("SCL_UNSET\n");

  return 0;
}

int twi_model_sda_set(twi_model *self) {
  D("SDA_SET\n");

  return 0;
}

int twi_model_sda_unset(twi_model *self) {
  D("SDA_UNSET\n");
  return 0;
}


#ifdef DEBUG
#undef D 
#endif /*DEBUG*/
