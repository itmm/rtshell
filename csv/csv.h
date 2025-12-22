#if !defined(csv_h)
#define csv_h

#include <stdbool.h>
#include <stdio.h>

#define CSV_SEPARATOR ';'

struct Csv_State;

int next_char_in_csv_cell(struct Csv_State* state);

bool has_more_csv_cells(struct Csv_State* state);

void eat_csv_cell(struct Csv_State* state);

bool has_more_csv_lines(struct Csv_State* state);

void eat_csv_line(struct Csv_State* state);

struct Csv_State* alloc_csv_state(FILE* in);

void free_csv_state(struct Csv_State* state);

#endif
