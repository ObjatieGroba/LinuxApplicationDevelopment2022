#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse(int argc, char **argv, int *n, int *m, int *s) {
    if (argc >= 2) {
        *n = atol(argv[1]);
    }
    if (argc >= 3) {
        *m = *n;
        *n = atol(argv[2]);
    }
    if (argc >= 4) {
        *s = atoi(argv[3]);
    }
}

int main(int argc, char **argv) {
    int n = 0, m = 0, s = 1;
    parse(argc, argv, &n, &m, &s);
    // printf("%d %d %d\n", m, n, s);
    for (int i = m; i < n; i += s) {
        printf("%d\n", i);
    }
}
