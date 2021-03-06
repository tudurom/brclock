#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>

#define LIN 4
#define COL 2
#define START 0x2800

char* toDotArray(char n);
wchar_t toBraille(char *m[COL]);

/* Holds binary representation of hours, minutes and seconds */
char *mat[3][COL];

/* Map for braille dots exponents */
char map[COL][LIN] = {{0, 1, 2, 6},
                      {3, 4, 5, 7}};

int main() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    /* Hours */
    mat[0][0] = toDotArray(tm.tm_hour / 10);
    mat[0][1] = toDotArray(tm.tm_hour % 10);

    /* Minutes */
    mat[1][0] = toDotArray(tm.tm_min / 10);
    mat[1][1] = toDotArray(tm.tm_min % 10);

    /* Seconds */
    mat[2][0] = toDotArray(tm.tm_sec / 10);
    mat[2][1] = toDotArray(tm.tm_sec % 10);

    /* Print wide chars */
    setlocale(LC_ALL, "");
    wprintf(L"%C\n%C\n%C\n", toBraille(mat[0]), toBraille(mat[1]), toBraille(mat[2]));
    return 0;
}

/* Get binary representation of n */
char* toDotArray(char n) {
    char *ret = malloc(LIN * sizeof(char));
    int i = LIN - 1;
    memset(ret, 0, LIN * sizeof(char));
    while (n > 0) {
        ret[i] = n % 2;
        i--;
        n /= 2;
    }

    return ret;
}

/* binary number to braille character */
wchar_t toBraille(char *m[COL]) {
    /* START is the empty braille character */
    wchar_t c = START;
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            c |= m[i][j] * (1 << map[i][j]);
        }
    }

    return c;
}
