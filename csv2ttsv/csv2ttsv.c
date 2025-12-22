#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "csv/csv.h"
#include "ttsv/ttsv.h"

static void do_line(struct Csv_State* csv) {
    for (;;) {
        int ch;
        while ((ch = next_char_in_csv_cell(csv)) != EOF) {
            write_ttsv_ch(stdout, ch);
        }
        if (! has_more_csv_cells(csv)) { next_ttsv_line(stdout); break; }
        next_ttsv_cell(stdout);
    }
}

int main(void) {
    struct Csv_State* csv = alloc_csv_state(stdin);
    for (;;) {
        do_line(csv);
		  if (! has_more_csv_lines(csv)) { break; }
    }
	 return 0;
}
