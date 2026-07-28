#ifndef EDITOR_H
#define EDITOR_H

void quick_menu(int cols, int rows, const char *filename, char *buf, int *buf_len, int *cursor_pos);
void editmode(int cols, int rows, char *buf, int *buf_len, const char *filename);
void start(const char *tekst, int cols, int rows, const char *filename);

#endif
