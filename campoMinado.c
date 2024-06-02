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
    printf("\n");
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
        printf("\t");
        for (int j = 0; j < SIZE; j++) {
            printf("%c  ", campo[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void printaBomba() {
    printf("\t       _.-^^---....,,--\n");
    printf("\t   _--                  --_\n");
    printf("\t  <                        >)\n");
    printf("\t  |                         |\n");
    printf("\t   \\._                   _./\n");
    printf("\t      ```--. . , ; .--'''\n");
    printf("\t            | |   |\n");
    printf("\t         .-=||  | |=-.\n");
    printf("\t         `-=#$#&#$#=-'\n");
    printf("\t            | ;  :|\n");
    printf("\t   _____.,-##&$@##&#~,._____\n");
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
}

void sensorBombas (char (*campo)[SIZE], char (*campoClone)[SIZE]) { 
    char bombas[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'}; // utiliza char ao invés de números
    int contaBomba = 0;

    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (campo[i][j] != 'B' && i > 0 && j > 0) { // If para que na varredura do loop ele altere apenas as células sem bombas
                contaBomba = 0;

                for (int k = -1; k <= 1; k++) {
                    for (int q = -1; q <= 1; q++) { // Loop de varredura de matriz ao redor da célula
                        int new_i = i + k;
                        int new_j = j + q;

                        if (new_i > 0 && new_i < SIZE && new_j > 0 && new_j < SIZE && campo[new_i][new_j] == 'B') contaBomba++; // verificação de tamanho da varredura para não varrer fora da matriz disponível
                        
                    }
                }

                campoClone[i][j] = bombas[contaBomba];
            }
            else campoClone[i][j] = 'B';
        }
    }
}

void jogaJogo (char (*campo)[SIZE], char (*campoClone)[SIZE], int numBomb) {
    int aux = 1;
    int freeFields = 81 - numBomb;

    while (aux) {
        int x = 0, y = 0;

        printf("\tRESTAM %d CAMPOS LIVRES...\n", freeFields);
        printf("\tESCOLHA SUAS COORDENADAS PRA JOGAR\n");  // Faz o usuário escolher as coordenadas que ele deseja para jogar o jogo
        printf("\t(DIGITE X: 0 E Y: 0 PARA SAIR DO JOGO)\n"); // Indica como o usuário sai do jogo durante ele

        printf("\t\tX: ");
        scanf("%d", &x);
        printf("\t\tY: ");
        scanf("%d", &y);

        if (x > 0 && x < SIZE && y > 0 && y < SIZE) {  // Realiza a verificação das coordenadas para que não acesse locais inválidos na matriz

            if (campoClone[x][y] == 'B'){  // Verifica se há uma bomba no local, caso não passa adiante
                printf("\n\n");
                printaBomba();
                printf("\n\n\tVoce explodiu....\n\n");

                printf("\tAINDA RESTAVAM %d CAMPOS LIVRES", freeFields);

                aux = 0;
            } 
            else {

               campo[x ][y] = campoClone[x][y];  // Compara com a matriz Clone e caso não haja bomba, o elemento recebe o contador da matriz clone no local do '#'
               freeFields--;
               printCampo(campo);

            }

        }
        else if (x == 0 && y == 0) {
            printf("\tVOCE ACABOU DE SAIR DO JOGO\n");
            printf("\tRESTAVAM %d CAMPOS LIVRES\n", freeFields);
            aux = 0;
        }
        else printf("\n\n\tESCOLHA INVALIDA, TENTE NOVAMENTE.\n\n");
    }

    
}


int main() {
    int aux = 1;

    do {

        char campo[SIZE][SIZE], campoBombas[SIZE][SIZE], campoJogo[SIZE][SIZE];
        
        inicializaMenu();

        int op;

        printf("\n\t\t  ESCOLHA: ");

        scanf("%d", &op);

        inicializaCampo(campo);
        inicializaCampo(campoBombas);
        inicializaCampo(campoJogo);


        switch (op) {
            case 1:
                printCampo(campo);
                inicializaBombas(10, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, 10);
                break;
            case 2:
                printCampo(campo);
                inicializaBombas(26, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, 26);
                break;
            case 3:
                printCampo(campo);
                inicializaBombas(57, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, 57);
                break;
            case 4:
                printCampo(campo);
                inicializaBombas(80, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, 80);
                break;
            default:
                aux = 0;
                break;
        }
    } while (aux);

    return 0;
}