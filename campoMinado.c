#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void inicializaCampo(char (*campo)[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 && j > 0) {
                campo[i][j] = '0' + j;
            }
            else if (j == 0 && i > 0) {
                campo[i][j] = '0' + i;
            }
            else {
                campo[i][j] = '#';
            }
        }
    }
}

void inicializaMenu() {
    printf("||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||        BEM VINDO AO CAMPO-MINADO       |||\n");
    printf("|||                                        |||\n");
    printf("|||         ESCOLHA SUA DIFICULDADE        |||\n");
    printf("|||                                        |||\n");
    printf("|||                                        |||\n");
    printf("|||            1 - FACIL                   |||\n");
    printf("|||            2 - NORMAL                  |||\n");
    printf("|||            3 - DIFICIL                 |||\n");
    printf("|||            4 - IMPOSSIVEL              |||\n");
    printf("|||                                        |||\n");
    printf("|||           APERTE '0' PARA SAIR         |||\n");
    printf("|||                                        |||\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||\n");
}

void printCampo(char campo[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", campo[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int aux = 1;

    while (aux) {
        srand(time(NULL));

        char campo[SIZE][SIZE];
        
        inicializaCampo(campo);

        inicializaMenu();

        int op;

        printf("\n\t\tESCOLHA: ");

        scanf("%d'", &op);

        printCampo(campo);

        switch (op) {
            case 1:
                // 3 bombas;
                break;
            case 2:
                // 10 bombas;
                break;
            case 3:
                // 28 bombas;
                break;
            case 4:
                // 35 bombas;
                break;
            default:
                aux = 0;
                break;

        }
    }
    


    return 0;
}