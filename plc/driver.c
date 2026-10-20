#include "iec_std_lib.h"
#include "accessor.h"
#include "POUS.h"
#include "POUS.c"

#include <stdio.h>

// matiec's standard library bundles in timer blocks (TON, TOF, ...) we don't
// use, but they reference this shared clock variable. We don't update it
// since we're not using timers yet — it just needs to exist for linking.
TIME __CURRENT_TIME;

static void print_state(int cycle, MAIN_data__ *m) {
    printf("cycle %2d: start_button=%s, pump_running=%s\n", cycle,
        m->START_BUTTON.value ? "TRUE" : "FALSE",
        m->PUMP_RUNNING.value ? "TRUE" : "FALSE");
}

int main(void) {
    MAIN_data__ main_inst;
    MAIN_init__(&main_inst, 0);

    FILE *log = fopen("plc/build/run_log.csv", "w");
    fprintf(log, "cycle,start_button,pump_running\n");

    for (int cycle = 1; cycle <= 10; cycle++) {
        // button pattern: off, off, on, on, on, on, on, off, off, off
        main_inst.START_BUTTON.value = (cycle >= 1 && cycle <= 3) ? TRUE : FALSE;

        MAIN_body__(&main_inst);

        print_state(cycle, &main_inst);
        fprintf(log, "%d,%d,%d\n", cycle,
            main_inst.START_BUTTON.value, main_inst.PUMP_RUNNING.value);
    }

    fclose(log);
    return 0;
}
