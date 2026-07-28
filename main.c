#include "common.h"
#include "fileio.h"
#include "editor.h"

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    SetConsoleCtrlHandler(NULL, TRUE);

    if (argc < 2) {
        printf("Użycie: mango <plik>\n");
        return 1;
    }

    int dlugosc = 0;
    char *tekst = odczytaj(argv[1], &dlugosc);
    if (!tekst) return 1;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int columns = 80, rows = 24;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    start(tekst, columns, rows, argv[1]);
    editmode(columns, rows, tekst, &dlugosc, argv[1]);
    printf("\e[1;1H\e[2J");
    free(tekst);
    return 0;
}
