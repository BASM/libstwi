#include <stdio.h>
#include <string.h>
#include <twi_model.h>

#define DEBUG
#ifdef DEBUG

#define D(...) ({printf("\033[33mTWI MOD> \033[0m");printf(__VA_ARGS__);})

#define DB(...) {}
//#define DB(...) ({printf("\033[33mTWI MOD> \033[0m");printf(__VA_ARGS__);})
#include <stdio.h>
#endif /*DEBUG*/


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

static int s_Getbyte(twi_model *s, int byte) {
  D("BITE %x,idx:%d\n", byte,s->idx);

  if (s->idx==8) {
    s->dir=byte;
    s->idx++;
    D("ADDR: %x\n", s->addr);
    D("DIR: %x\n", byte);
    return 0;
  }


  switch(s->stage) {
    case STAGE_ADDR:
      {
        if (s->idx==9) {
          s->idx=0;
          s->stage=STAGE_REG;
          D("BYTE: %x\n",s->reg);
        }
        if (byte) s->addr|=1<<(7-s->idx);
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
  if (s->sda==1) s_Getbyte(s,1);D("BYTE 1\n");
  if (s->sda==0) s_Getbyte(s,0);D("BYTE 0\n");
  return 0;
}
int twi_model_scl_unset(twi_model *s) {
  s->scl=0;
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
