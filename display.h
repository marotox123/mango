#ifndef DISPLAY_H
#define DISPLAY_H

void print_top_bar(int cols, int rows, const char *filename);
void obszar_tekstu(int cols, int rows);
void wyswietl_tekst(const char *buf, int cols, int rows);
void wyswietl_tekst_silent(const char *buf, int cols, int rows);
void refresh_from_line(const char *buf, int buf_len, int cols, int rows, int from_y);
void refresh_top_bar_with_pos(int cols, int rows, const char *filename, int x, int y, int cur_x, int cur_y);

#endif
