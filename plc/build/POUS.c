#ifdef  DISABLE_EN_ENO_PARAMETERS
  #include "iec_std_FB_no_ENENO_impl.h"
#else
  #include "iec_std_FB_impl.h"
#endif

static void MAIN_init__(MAIN_data__ *data__, BOOL retain);
#ifndef __POUS_INIT_ONLY__
static void MAIN_body__(MAIN_data__ *data__);
#endif

static void MAIN_init__(MAIN_data__ *data__, BOOL retain) {
  __INIT_VAR(data__->START_BUTTON,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PUMP_RUNNING,__BOOL_LITERAL(FALSE),retain)
}

#ifndef __POUS_INIT_ONLY__
// Code part
static void MAIN_body__(MAIN_data__ *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,PUMP_RUNNING,,__GET_VAR(data__->START_BUTTON,));

  goto __end;

__end:
  return;
} // MAIN_body__() 

#endif




