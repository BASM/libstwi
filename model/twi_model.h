#include <inttypes.h>

typedef enum {
  STAGE_ADDR,
  STAGE_REG
} twi_model_stages;


typedef struct {
  _Bool down_scl;//Wait flag
  _Bool down_sda;//Answer flag
  int sda;
  int scl;

  twi_model_stages stage;
  uint8_t dir; //0--write, 1--read
  _Bool inwork;
  _Bool ask;
  uint8_t addr;
  uint8_t idx;
  uint8_t reg;

  uint8_t self_addr;

  char regs[0xff];
} twi_model;

_Bool twi_model_sdaget(twi_model *self);
_Bool twi_model_sclget(twi_model *self);
int twi_model_init(twi_model *self, int addr);
int twi_model_scl_set(twi_model *self);
int twi_model_scl_unset(twi_model *self);
int twi_model_sda_set(twi_model *self);
int twi_model_sda_unset(twi_model *self);
