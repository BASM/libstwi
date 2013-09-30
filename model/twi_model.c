#include <stdio.h>
#include <string.h>
#include <twi_model.h>

int twi_model_init(twi_model *self, int addr) {

  memset(self,0,sizeof(twi_model));
  self->addr=addr;
  //0x4f

  return 0;
}


int twi_model_scl_set(twi_model *self) {

  return 0;
}
int twi_model_scl_unset(twi_model *self) {

  return 0;
}

int twi_model_sda_set(twi_model *self) {

  return 0;
}

int twi_model_sda_unset(twi_model *self) {
  return 0;
}


