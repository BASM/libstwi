#include <twi_sw.h>

#define DEBUG
#ifdef DEBUG
#define D(...) ({printf("\033[31mTWI LIB> \033[0m");printf(__VA_ARGS__);})
#define DB(...) {}
//#define DB(...) ({printf("\033[33mTWI MOD> \033[0m");printf(__VA_ARGS__);})
#include <stdio.h>
#else
#define D(...)
#define DB(...)
#endif /*DEBUG*/

#define SDA_RL ({ if (!s->sda) { s->sda_rl(s->userdata); s->sda=1; } })
#define SDA_DN ({ if ( s->sda) { s->sda_dn(s->userdata); s->sda=0; } })
#define SDA_READ s->sda_read(s->userdata)

#define SCL_RL ({ if (!s->scl) { \
    if (s->scl_rl(s->userdata)) return FERROR; \
    s->scl=1; } })

#define SCL_DN ({ if ( s->scl) { s->scl_dn(s->userdata); s->scl=0; } })
#define WAIT   s->cycle_wait(s->userdata)

static fres s_start_bit(twi_data *s) {
  D("(Re)Start\n");
  SCL_DN;
  if (s->sda==0) {
    SDA_RL;
    WAIT;
  }
  SCL_RL;
  WAIT;
  SDA_DN;
  WAIT;
  return FTRUE;
}

static int s_stop_bit(twi_data *s) {
  D("Stop\n");
  SCL_DN;
  SDA_DN;
  WAIT;
  SCL_RL;
  SDA_RL;
  return FTRUE;
}


static fres s_send_bit(twi_data *s, int byte) {
  DB("BITE: %i\n", byte&1);

  SCL_DN;
  WAIT;
  if (byte&1) SDA_RL;
  else        SDA_DN;
  WAIT;
  SCL_RL;
  WAIT;
  return FTRUE;
}

static fres s_get_bit(twi_data *s) {
  SCL_DN;
  if (s->sda==0) SDA_RL;
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

  D("REQ READ\n");
  D("ADDR: %x\n",addr);
  s_start_bit(s);

  i=7;
  while (i) s_send_bit(s,addr>>--i);
  s_send_bit(s,0);//WRITE
  if (s_get_bit(s)==false) {//NASK get
    s_stop_bit(s);
    D("NASK 1\n");
    return 1;
  }
  i=8;
  while (i) s_send_bit(s,reg>>--i);
  if (s_get_bit(s)==false) { //NASK get
    D("NASK 2\n");
    return 1;
  }
  s_start_bit(s);
  i=7;
  while (i) s_send_bit(s,addr>>--i);
  s_send_bit(s,1);//READ
  if (s_get_bit(s)==false) {
    s_stop_bit(s);
    D("NASK 3\n");
    return 1;
  }

  return 0;
}

int twi_sw_read(twi_data *s,int type) {
  uint8_t data=0;
  int     i;
  
  D("READ\n");
  i=8;
  while (i) {
    --i; 
    if (s_get_bit(s)==0) data|=1<<i;
  }
  if (type==0) s_send_bit(s,0);//ASK send
  else         s_send_bit(s,1);//NACK send
  D("DATA GET: %x\n",data);
  return data;
}

int twi_sw_stop(twi_data *s) {
  s_stop_bit(s);
  return 0;
}

#undef SDA_RL
#undef SDA_DN
#undef SCL_RL
#undef SCL_DN

#ifdef DEBUG
#undef D
#endif
