#include <stdio.h>

int main() {
    int v[6] = {8, 3, 5, 12, 7, 2};
    int i, temp;

    for (i = 0; i < 5; i++) {
        if (v[i] % 2 != 0 && v[i + 1] % 2 == 0) {
            temp = v[i];
            v[i] = v[i + 1];
            v[i + 1] = temp;
        }
    }

    for (i = 0; i < 6; i++)
        printf("%d ", v[i]);

    return 0;
}