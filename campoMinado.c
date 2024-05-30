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
            else if (i == 0 && j == 0) {
                campo[i][j] = '@';
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
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c  ", campo[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void inicializaBombas(int numBomb, char (*campo)[SIZE]) {
    srand(time(NULL));

    int cont = 0; // Contador de bombas colocadas

    while (cont < numBomb) {
        int colRand = (rand() % 9) + 1; // Gera uma coluna aleatória (1 a 9)
        int linRand = (rand() % 9) + 1; // Gera uma linha aleatória (1 a 9)

        // Verifica se a posição não tem uma bomba
        if (campo[linRand][colRand] != 'B') {
            campo[linRand][colRand] = 'B'; // Posiciona a bomba
            cont++;
        }
    }

    printCampo(campo);
}

void sensorBombas (char (*campo)[SIZE], char (*campoClone)[SIZE]) {  // NECESSITA DE CORREÇÃO NA VARREDURA DA MATRIX 3X3 PARA AS BOMBAS ADJACENTES
    char bombas[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    int contaBomba = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (campo[i][j] != 'B' && i > 0 && j > 0) {
                contaBomba = 0;

                for (int k = -1; k <= 1; k++) {
                    for (int q = -1; q <= 1; q++) {

                        //if (i + k < SIZE && j + q < SIZE){
                            if (campo[i + k][j + q] == 'B') contaBomba += 1;
                        //}
                        
                    }
                }

                campoClone[i][j] = bombas[contaBomba];
            }
        }
    }

    printCampo(campoClone);
}

int main() {
    int aux = 1;

    while (aux) {

        char campo[SIZE][SIZE], campoBombas[SIZE][SIZE], campoContador[SIZE][SIZE];
        
        inicializaMenu();

        int op;

        printf("\n\t\tESCOLHA: ");

        scanf("%d", &op);

        inicializaCampo(campo);
        inicializaCampo(campoBombas);
        inicializaCampo(campoContador);

        printCampo(campo);

        switch (op) {
            case 1:
                inicializaBombas(10, campoBombas);
                sensorBombas(campo, campoBombas);
                break;
            case 2:
                inicializaBombas(20, campoBombas);
                sensorBombas(campo, campoBombas);
                break;
            case 3:
                inicializaBombas(45, campoBombas);
                sensorBombas(campo, campoBombas);
                break;
            case 4:
                inicializaBombas(80, campoBombas);
                sensorBombas(campo, campoBombas);
                break;
            default:
                aux = 0;
                break;
        }
    }

    return 0;
}