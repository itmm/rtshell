#if !defined(csv_h)
#define ttsv_h

#include <stdio.h>

void next_ttsv_cell(FILE* out);
void next_ttsv_line(FILE* out);

void write_ttsv_ch(FILE* out, char ch);
void write_ttsv_str(FILE* out, const char* str);

#endif
