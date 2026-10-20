#ifdef  DISABLE_EN_ENO_PARAMETERS
  #include "iec_std_FB_no_ENENO.h"
#else
  #include "iec_std_FB.h"
#endif

__DECLARE_PROGRAM_TYPE(MAIN,

  __DECLARE_VAR(BOOL,START_BUTTON)
  __DECLARE_VAR(BOOL,PUMP_RUNNING)

)

