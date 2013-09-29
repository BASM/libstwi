/* Software TWI interface */

typedef struct S_twi_sw_data {
  int (*scl_set)(void);
  int (*scl_unset)(void);
  int (*sda_set)(void);
  int (*sda_unset)(void);
} twi_data;

