#ifndef CURSOR_H
#define CURSOR_H

void cursor_pos_to_xy(const char *buf, int cursor_pos, int cols, int *out_x, int *out_y);
int xy_to_cursor_pos(const char *buf, int buf_len, int target_x, int target_y, int cols);

#endif
