#include "common.h"
#include "cursor.h"

void cursor_pos_to_xy(const char *buf, int cursor_pos, int cols, int *out_x, int *out_y) {
    int x = 1, y = 2;
    for (int i = 0; i < cursor_pos; i++) {
        if (buf[i] == '\n') {
            y++;
            x = 1;
        } else {
            x++;
            if (x > cols) {
                x = 1;
                y++;
            }
        }
    }
    *out_x = x;
    *out_y = y;
}

int xy_to_cursor_pos(const char *buf, int buf_len, int target_x, int target_y, int cols) {
    int x = 1, y = 2;
    for (int i = 0; i <= buf_len; i++) {
        if (x == target_x && y == target_y) return i;
        if (buf[i] == '\n') {
            y++;
            x = 1;
        } else {
            x++;
            if (x > cols) {
                x = 1;
                y++;
            }
        }
    }
    return buf_len;
}
