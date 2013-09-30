
typedef struct {
  int sda;
  int scl;

  int addr;

  char regs[0xff];
} twi_model;

int twi_model_init(twi_model *self, int addr);
int twi_model_scl_set(twi_model *self);
int twi_model_scl_unset(twi_model *self);
int twi_model_sda_set(twi_model *self);
int twi_model_sda_unset(twi_model *self);
