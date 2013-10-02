#include <twi_sw.h>
#include <stdbool.h>

#define DEBUG
#ifdef DEBUG
#define D(...) ({printf("\033[31mTWI LIB> \033[0m");printf(__VA_ARGS__);})
#include <stdio.h>
#endif /*DEBUG*/

#define SDA_RL ({ if (!s->sda) { s->sda_rl(s->userdata); s->sda=1; } })
#define SDA_DN ({ if ( s->sda) { s->sda_dn(s->userdata); s->sda=0; } })
#define SDA_READ s->sda_read(s->userdata)

#define SCL_RL ({ if (!s->scl) { s->scl_rl(s->userdata); s->scl=1; } })

#define SCL_DN ({ if ( s->scl) { s->scl_dn(s->userdata); s->scl=0; } })
#define WAIT   s->cycle_wait(s->userdata)

static void s_start_bit(twi_data *s) {
  D("(Re)Start\n");
  SCL_DN;
  SDA_RL;
  WAIT;
  SCL_RL;
  SDA_DN;
}

static void s_stop_bit(twi_data *s) {
  D("Stop\n");
  SCL_DN;
  SDA_DN;
  WAIT;
  SCL_RL;
  SDA_RL;
}


static void s_send_bit(twi_data *s, int byte) {
  D("BYTE: %i\n", byte&1);

  SCL_DN;
  if (byte&1) SDA_RL;
  else        SDA_DN;
  WAIT;
  SCL_RL;
  WAIT;
}

static _Bool s_ask_bit(twi_data *s) {
  D("ASK\n");

  SCL_DN;
  WAIT;
  SCL_RL;
  WAIT;
  return SDA_READ;
}

/////////////////////////////////////////////////////
int twi_sw_init(twi_data *s, void *userdata) {
  D("TWI init\n");

  s->userdata=userdata;
  s->scl=0;
  s->sda=0;
  SDA_RL;
  SCL_RL;

  return 0;
}

int twi_sw_req_read(twi_data *s,int addr,int reg) {
  int i;

  s_start_bit(s);

  D("ADDR: %x\n",addr);
  i=7;
  while (i) s_send_bit(s,addr>>--i);
  s_send_bit(s,0);//WRITE
  if (s_ask_bit(s)==false) {
    s_stop_bit(s);
    return 1;
  }

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

#undef SDA_RL
#undef SDA_DN
#undef SCL_RL
#undef SCL_DN

#ifdef DEBUG
#undef D
#endif
