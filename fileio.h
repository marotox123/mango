#ifndef FILEIO_H
#define FILEIO_H

char* odczytaj(const char *nazwa, int *dlugosc);
void save_file(int cols, int rows, const char *filename, char *buf, int buf_len, int cx, int cy);

#endif
