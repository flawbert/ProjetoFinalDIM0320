#include <stdio.h>

void matriz(int valor, int valor_2) {
    int matriz[valor][valor_2];
    for (int i = 0; i < valor; i++) {
        for (int j = 0; j < valor_2; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
    for (int i = 0; i < valor; i++) {
        for (int j = 0; j < valor_2; j++) {
            if (matriz[i][j] == 1) {
                printf("9");
            } else {
                int contador = 0;
                if (i > 0 && matriz[i - 1][j] == 1) {
                    contador++;
                }
                if (i < valor - 1 && matriz[i + 1][j] == 1) { 
                    contador++;
                }
                if (j > 0 && matriz[i][j - 1] == 1) { 
                    contador++;
                }
                if (j < valor_2 - 1 && matriz[i][j + 1] == 1) {
                    contador++;
                }

                printf("%d", contador);
            }
        }
        printf("\n");
    }
}

int main(void) {
    int valor, valor_2;
    while (scanf("%d %d", &valor, &valor_2) != EOF) {
        matriz(valor, valor_2);
    }
    return 0;
}
