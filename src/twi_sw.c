#include <twi_sw.h>

#define DEBUG
#ifdef DEBUG
#define D(...) ({printf("\033[31mTWI LIB> \033[0m");printf(__VA_ARGS__);})
#include <stdio.h>
#endif /*DEBUG*/

#define SDA_UP s->sda_up(s->userdata)
#define SDA_DN s->sda_dn(s->userdata)
#define SCL_UP s->scl_up(s->userdata)
#define SCL_DN s->scl_up(s->userdata)
#define WAIT   s->cycle_wait(s->userdata)

int twi_sw_init(twi_data *s, void *userdata) {
  D("TWI init\n");

  s->userdata=userdata;
  SDA_UP;
  SCL_UP;

  return 0;
}

static int s_start_bit(twi_data *s) {
  D("Start\n");
  SCL_DN;
  WAIT;
  return 0;
}

int twi_sw_req_read(twi_data *s,int addr,int reg) {

  s_start_bit(s);

  D("TWI req read %x, %x\n",addr,reg);

  return 0;
}

int twi_sw_read(twi_data *self,int type) {
  D("TWI read %i\n",type);

  return 0;
}

int twi_sw_stop(twi_data *self) {
  D("TWI stop\n");

  return 0;
}

#undef SDA_UP
#undef SDA_DN
#undef SCL_UP
#undef SCL_DN

#ifdef DEBUG
#undef D
#endif
