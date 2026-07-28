#include "common.h"
#include "terminal.h"

int ctrl_held(void) {
    return GetAsyncKeyState(VK_CONTROL) & 0x8000;
}

void gotoxy(int col, int row) {
    printf("\033[%d;%dH", row, col);
}
