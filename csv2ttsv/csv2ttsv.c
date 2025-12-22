#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "log/log.h"
#include "csv/csv.h"
#include "ttsv/ttsv.h"

static void do_line(struct Csv_State* csv) {
    for (;;) {
        int ch;
        while ((ch = next_char_in_csv_cell(csv)) != EOF) {
            write_ttsv_ch(stdout, ch);
        }
        if (! has_more_csv_cells(state)) { break; }
        next_ttsv_cell(stdout);
    }
}

int main(void) {
    struct Csv_State* csv = alloc_csv_state(stdin);
    do {
        do_line(csv);
    } while (has_more_csv_lines(state));
}
