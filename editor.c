#include "common.h"
#include "editor.h"
#include "terminal.h"
#include "display.h"
#include "fileio.h"
#include "cursor.h"

void quick_menu(int cols, int rows, const char *filename, char *buf, int *buf_len, int *cursor_pos) {
    int cx, cy;
    cursor_pos_to_xy(buf, *cursor_pos, cols, &cx, &cy);
    refresh_top_bar_with_pos(cols, rows, filename, cx, cy, cx, cy);

    while (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
        if (GetAsyncKeyState('S') & 0x8000) {
            save_file(cols, rows, filename, buf, *buf_len, cx, cy);
            Sleep(200);
            break;
        }
        if (GetAsyncKeyState('Z') & 0x8000) { break; }
        if (GetAsyncKeyState('C') & 0x8000) { break; }
        if (GetAsyncKeyState('V') & 0x8000) { break; }
        if (GetAsyncKeyState('X') & 0x8000) { break; }
        if (GetAsyncKeyState('A') & 0x8000) { break; }
        Sleep(10);
    }

    print_top_bar(cols, rows, filename);
    gotoxy(cx, cy);
    fflush(stdout);
}

void editmode(int cols, int rows, char *buf, int *buf_len, const char *filename) {
    int ch;
    int cursor_pos = 0;
    int cx, cy;

    cursor_pos_to_xy(buf, cursor_pos, cols, &cx, &cy);
    gotoxy(cx, cy);

    while (1) {
        cursor_pos_to_xy(buf, cursor_pos, cols, &cx, &cy);

        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            quick_menu(cols, rows, filename, buf, buf_len, &cursor_pos);
            continue;
        }

        if (kbhit()) {
            ch = getch();
            if (ch == 0 || ch == 224) {
                ch = getch();
                switch (ch) {
                    case 72: // góra
                        if (cy > 2)
                            cursor_pos = xy_to_cursor_pos(buf, *buf_len, cx, cy - 1, cols);
                        break;
                    case 80: // dół
                        if (cy < rows - 1)
                            cursor_pos = xy_to_cursor_pos(buf, *buf_len, cx, cy + 1, cols);
                        break;
                    case 75: // lewo
                        if (cursor_pos > 0) cursor_pos--;
                        break;
                    case 77: // prawo
                        if (cursor_pos < *buf_len) cursor_pos++;
                        break;
                }
            } else {
                switch (ch) {
                    case 27: // ESC
                        return;
                    case 13: // Enter - pełne odświeżenie bo zmienia układ wierszy
                        memmove(buf + cursor_pos + 1, buf + cursor_pos, *buf_len - cursor_pos + 1);
                        buf[cursor_pos] = '\n';
                        (*buf_len)++;
                        cursor_pos++;
                        wyswietl_tekst_silent(buf, cols, rows);
                        break;
                    case 8: // Backspace
                        if (cursor_pos > 0) {
                            int prev_char = buf[cursor_pos - 1];
                            memmove(buf + cursor_pos - 1, buf + cursor_pos, *buf_len - cursor_pos + 1);
                            (*buf_len)--;
                            cursor_pos--;
                            cursor_pos_to_xy(buf, cursor_pos, cols, &cx, &cy);
                            if (prev_char == '\n')
                                wyswietl_tekst_silent(buf, cols, rows); /* newline usunięty - pełne odświeżenie */
                            else
                                refresh_from_line(buf, *buf_len, cols, rows, cy);
                        }
                        break;
                    default:
                        if (ch >= 32 && ch < 127) {
                            memmove(buf + cursor_pos + 1, buf + cursor_pos, *buf_len - cursor_pos + 1);
                            buf[cursor_pos] = ch;
                            (*buf_len)++;
                            cursor_pos++;
                            cursor_pos_to_xy(buf, cursor_pos, cols, &cx, &cy);
                            /* odśwież tylko od bieżącego wiersza w dół */
                            refresh_from_line(buf, *buf_len, cols, rows, cy);
                        }
                        break;
                }
            }
            cursor_pos_to_xy(buf, cursor_pos, cols, &cx, &cy);
            gotoxy(cx, cy);
            fflush(stdout);
        }
    }
}

void start(const char *tekst, int cols, int rows, const char *filename) {
    printf("\033[2J");
    print_top_bar(cols, rows, filename);
    gotoxy(1, 2);
    obszar_tekstu(cols, rows);
    wyswietl_tekst(tekst, cols, rows);
}
