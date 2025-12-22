#include "ttsv.h"


#include "log/log.h"

static void write_ch(int ch, FILE* out) {
    if (! out) { log_fatal("null pointer", "write_ch"); }
    if (fputc(ch, out) == EOF) {
        log_fatal_errno("Fehler beim Schreiben");
    }
}

void next_ttsv_cell(FILE* out) {
    write_ch('\t', out);
}

void next_ttsv_line(FILE* out) {
    write_ch('\n', out);
}

static void write_nibble(int value, FILE* out) {
    static const char digits[] = "0123456789abcdef";
    write_ch(digits[value & 0xf], out);
}

void write_ttsv_ch(FILE* out, char ch) {
    if (ch >= ' ') { write_ch(ch, out); return; };
    write_ch('\\', out);
    write_nibble(ch >> 4, out);
    write_nibble(ch, out);
}

void write_ttsv_str(FILE* out, const char* str) {
    if (! str) { log_fatal("null pointer", "write_ttsv_str"); }
    for (; *str; ++str) { write_ttsv_ch(out, *str); }
}
