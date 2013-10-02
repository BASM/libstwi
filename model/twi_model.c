#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <twi_model.h>

#define DEBUG
#ifdef DEBUG

#define D(...) ({printf("\033[33mTWI MOD> \033[0m");printf(__VA_ARGS__);})

#define DB(...) {}
//#define DB(...) ({printf("\033[33mTWI MOD> \033[0m");printf(__VA_ARGS__);})
#include <stdio.h>
#endif /*DEBUG*/

_Bool twi_model_getsda(twi_model *s) {
  return s->down_sda;
}

static int s_Start_cond(twi_model *s) {
  if (s->inwork==1) {
    D("RE START COND\n");
  }else{
    D("START COND\n");
  }

  s->stage=STAGE_ADDR;
  s->addr=0;
  s->idx=0;
  s->reg=0;
  s->inwork=1;

  return 0;
}

static int s_Stop_cond(twi_model *s) {
  D("STOP COND\n");

  s->inwork=0;

  return 0;
}

static int s_ask(twi_model *s) {
  D("XXX\n");
  if (s->stage==STAGE_ADDR) {
    if (s->addr == s->self_addr) {
      s->ask=true;
      D("ASK DOWN\n");
      s->down_sda=true;
      return 1;
    }
  }
  return 0;
}

static int s_Getbyte(twi_model *s, int byte) {
  DB("BITE %x,idx:%d\n", byte,s->idx);

  if (s->idx==7) {
    s->dir=byte;
    s->idx++;
    D("ADDR: %x\n", s->addr);
    D("DIR: %s\n", (byte)?"write":"read");
    return 0;
  }else if (s->idx==8) {
    if (s_ask(s) == false) {
      s->inwork=false;
    }
  }

  switch(s->stage) {
    case STAGE_ADDR:
      {
        if (s->idx==8) {
          s->idx=0;
          s->stage=STAGE_REG;
          D("ADDR: %x, DIR: %s\n",s->reg,(byte)?"write":"read");
        }
        if (byte) s->addr|=1<<(6-s->idx);
        s->idx++;
      } break;
    case STAGE_REG:
      {
        if (byte) s->reg|=1<<s->idx++;
      } break;
  }
  return 0;
}

/////////////////////////////////////////////////////
int twi_model_init(twi_model *self, int addr) {

  memset(self,0,sizeof(twi_model));
  self->self_addr=addr;
  //0x4f

  return 0;
}

int twi_model_scl_set(twi_model *s) {
  s->scl=1;
  DB("SCL_SET\n");
  if (s->inwork) {
    if (s->sda==1) s_Getbyte(s,1);
    if (s->sda==0) s_Getbyte(s,0);
  }

  return 0;
}
int twi_model_scl_unset(twi_model *s) {
  s->scl=0;
  if (s->ask==true) {
    s->ask=false;
    D("ASK RELEASE\n");
    s->down_sda=false;
  }
  DB("SCL_UNSET\n");

  return 0;
}

int twi_model_sda_set(twi_model *s) {
  s->sda=1;
  
  DB("SDA_SET\n");
  if (s->scl==1) s_Stop_cond(s);

  return 0;
}

int twi_model_sda_unset(twi_model *s) {
  s->sda=0;

  DB("SDA_UNSET\n");
  if (s->scl==1) s_Start_cond(s);
  
  return 0;
}


#ifdef DEBUG
#undef D 
#undef DB
#endif /*DEBUG*/
