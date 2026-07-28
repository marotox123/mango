#include "common.h"
#include "fileio.h"
#include "terminal.h"

char* odczytaj(const char *nazwa, int *dlugosc) {
    FILE *f = fopen(nazwa, "r");
    if (!f) {
        printf("Nie można otworzyć pliku: %s\n", nazwa);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    *dlugosc = ftell(f);
    rewind(f);
    char *buf = malloc(*dlugosc + 65536); /* zapas na edycję */
    if (!buf) {
        fclose(f);
        return NULL;
    }
    fread(buf, 1, *dlugosc, f);
    buf[*dlugosc] = '\0';
    fclose(f);
    return buf;
}

void save_file(int cols, int rows, const char *filename, char *buf, int buf_len, int cx, int cy) {
    FILE *f = fopen(filename, "w");
    if (f) {
        fwrite(buf, 1, buf_len, f);
        fclose(f);
    }

    char top[256];
    snprintf(top, sizeof(top), " %s  [Saved!]", filename);
    int used = strlen(top);
    printf("\033[30;47m");
    gotoxy(1, 1);
    printf("%s", top);
    for (int i = used; i < cols; i++) printf(" ");
    printf("\033[0m");

    gotoxy(cx, cy);
    fflush(stdout);
}
