#include "common.h"
#include "display.h"
#include "terminal.h"

void print_top_bar(int cols, int rows, const char *filename) {
    int title_len = strlen(filename);

    printf("\033[30;47m");
    gotoxy(1, 1);
    printf(" %s", filename);
    for (int i = title_len + 1; i < cols; i++) printf(" ");
    printf("\033[0m");

    const char *credits = " mango marotox123 2026 ";
    int credits_len = strlen(credits);

    printf("\033[30;47m");
    gotoxy(1, rows);
    for (int i = 0; i < cols - credits_len; i++) printf(" ");
    printf("%s", credits);
    printf("\033[0m");
}

void obszar_tekstu(int cols, int rows) {
    for (int i = 2; i < rows; i++) {
        gotoxy(1, i);
        for (int j = 0; j < cols; j++) printf(" ");
    }
    gotoxy(1, 2);
}

void wyswietl_tekst(const char *buf, int cols, int rows) {
    int wiersz = 2;
    int kol = 1;
    gotoxy(kol, wiersz);
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '\n' || kol > cols) {
            wiersz++;
            kol = 1;
            if (wiersz >= rows) break;
            gotoxy(kol, wiersz);
            if (buf[i] == '\n') continue;
        }
        putchar(buf[i]);
        kol++;
    }
}

void wyswietl_tekst_silent(const char *buf, int cols, int rows) {
    printf("\033[?25l");
    obszar_tekstu(cols, rows);
    wyswietl_tekst(buf, cols, rows);
    printf("\033[?25h");
    fflush(stdout);
}

/*
 * Odświeża tylko wiersze od from_y do końca ekranu.
 * Dużo szybsze niż pełne odświeżenie - używane przy zwykłym pisaniu.
 */
void refresh_from_line(const char *buf, int buf_len, int cols, int rows, int from_y) {
    printf("\033[?25l");

    /* wyczyść tylko wiersze od from_y w dół */
    for (int i = from_y; i < rows; i++) {
        gotoxy(1, i);
        for (int j = 0; j < cols; j++) printf(" ");
    }

    /* znajdź pozycję w buforze odpowiadającą from_y */
    int x = 1, y = 2;
    int start_i = 0;
    int found = 0;
    for (int i = 0; i < buf_len; i++) {
        if (y == from_y && x == 1) {
            start_i = i;
            found = 1;
            break;
        }
        if (buf[i] == '\n') { y++; x = 1; }
        else { x++; if (x > cols) { x = 1; y++; } }
    }
    if (!found && y == from_y) start_i = buf_len;

    /* narysuj od start_i */
    int wiersz = from_y;
    int kol = 1;
    gotoxy(kol, wiersz);
    for (int i = start_i; i < buf_len; i++) {
        if (buf[i] == '\n' || kol > cols) {
            wiersz++;
            kol = 1;
            if (wiersz >= rows) break;
            gotoxy(kol, wiersz);
            if (buf[i] == '\n') continue;
        }
        putchar(buf[i]);
        kol++;
    }

    printf("\033[?25h");
    fflush(stdout);
}

void refresh_top_bar_with_pos(int cols, int rows, const char *filename, int x, int y, int cur_x, int cur_y) {
    printf("\033[?25l");

    char top[256];
    snprintf(top, sizeof(top), " %s  [x:%d y:%d]", filename, x, y);
    int used = strlen(top);

    printf("\033[30;47m");
    gotoxy(1, 1);
    printf("%s", top);
    for (int i = used; i < cols; i++) printf(" ");
    printf("\033[0m");

    const char *shortcuts = " Ctrl+S:Save  Ctrl+Z:Undo  Ctrl+C:Copy  Ctrl+V:Paste  Ctrl+X:Cut  Ctrl+F:Find  Ctrl+A:SelectAll  ESC:Exit ";
    int slen = strlen(shortcuts);
    printf("\033[30;47m");
    gotoxy(1, rows);
    printf("%s", shortcuts);
    for (int i = slen; i < cols; i++) printf(" ");
    printf("\033[0m");

    gotoxy(cur_x, cur_y);
    printf("\033[?25h");
    fflush(stdout);
}
