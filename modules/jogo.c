#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "impl/tools.h"
#include "impl/jogo.h"
#include "impl/campo.h"

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

void sensorBombas(char (*campo)[SIZE], char (*campoClone)[SIZE]) {
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
            } else campoClone[i][j] = 'B';
        }
    }
}

void verificaCampo(char (*campo)[SIZE], char (*campoClone)[SIZE], int x, int y, int *points, int pointsValue) {
    if (x <= 0 || x >= SIZE || y <= 0 || y >= SIZE || campo[x][y] != '#') {
        return; // Condição de parada: fora dos limites ou já revelado ou igual a uma bandeira
    }

    campo[x][y] = campoClone[x][y]; // Revela o campo atual

    if (campo[x][y] == '0') campo[x][y] = '-'; // Substitui o '0' por '-' indicando campo nulo

    if (campoClone[x][y] == '0') { // Só propaga se o campo for '0'
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newX = x + i;
                int newY = y + j;
                if (i != 0 || j != 0) { // Evita chamar a função recursivamente sobre o mesmo campo
                    verificaCampo(campo, campoClone, newX, newY, points, pointsValue); // Chamada recursiva nos campos vazios
                }
            }
        }
    }

    *points += pointsValue;
}

int flagPosition(char (*campo)[SIZE]) {
    int x, y;

    printf("\tESCOLHA AS COORDENADAS PARA POSICIONAR OU RETIRAR UMA BANDEIRA\n");
    printf("\tX: ");
    scanf("%d", &y);
    printf("\tY: ");
    scanf("%d", &x);

    if (x > 0 && x < SIZE && y > 0 && y < SIZE) {
        if (campo[x][y] == '#') {
            campo[x][y] = '>'; // Coloca a bandeira
            printCampo(campo); // Printa o Campo
            return 1; // Indica que uma bandeira foi colocada
        } else if (campo[x][y] == '>') {
            campo[x][y] = '#'; // Remove a bandeira
            printCampo(campo); // Printa o Campo
            return -1; // Indica que uma bandeira foi removida
        } else {
            printf(RED "\tPOSICAO INVALIDA PARA BANDEIRA, TENTE NOVAMENTE.\n" RESET);
            return 0; // Retorna 0 indicando que nenhuma ação foi tomada
        }
    } else {
        printf(RED "\tPOSICAO INVALIDA PARA BANDEIRA, TENTE NOVAMENTE NA PROXIMA RODADA.\n" RESET);
        return 0;
    }
}

void flagSuggestion (int *numFlags, char (*campo)[SIZE]) { // Posicionamento da bandeira 
    char opFlag;

    while (1) {
        printf(BLUE "\tVOCE QUER POSICIONAR OU RETIRAR UMA BANDEIRA( Y - SIM || N - NAO)? " RESET);
        scanf(" %c", &opFlag);

        if (opFlag == 'Y') {
            printCampo(campo); // Printa o Campo
            int result = flagPosition(campo); // Chamada da função para posicionar ou remover bandeira
            if (result == 1 && *numFlags > 0) {
                (*numFlags)--; // Decrementa o número de bandeiras disponíveis se uma bandeira foi colocada
            } else if (result == -1) {
                (*numFlags)++; // Incrementa o número de bandeiras disponíveis se uma bandeira foi removida
            }
            break;
        }
        else if (opFlag == 'N') {
            break;
        }
        else {
            printf(RED "\tA OPCAO NAO EH VALIDA, TENTE NOVAMENTE.\n" RESET);
        }
    }
}

int verificaVitoria (char campo[SIZE][SIZE], char campoClone[SIZE][SIZE]) {
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (campoClone[i][j] != 'B' && campo[i][j] == '#') {
                return 0; // Ainda há células não reveladas, continuando o jogo
            }
        }
    }
    return 1; // Todas as células sem bombas foram reveladas, significando vitória
}

void printVitoria () {
    CLEAR_SCREEN();
    printf("\n\n");
    printf( GREEN "\t|||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\t|||                                           |||\n");
    printf("\t|||               PARABENS!                   |||\n");
    printf("\t|||            VOCE VENCEU O JOGO!            |||\n");
    printf("\t|||                                           |||\n");
    printf("\t|||||||||||||||||||||||||||||||||||||||||||||||||\n" RESET);
    printf("\n\n");
}

void jogaJogo (char (*campo)[SIZE], char (*campoClone)[SIZE], int *points, int pointsValue, int numFlags) {
    int aux = 1;


    while (aux) {

        printCampo(campo);

        int x = 0, y = 0;

        printf(GREEN "\tPONTUACAO: %d\n" RESET, *points);
        printf(BLUE "\tBANDEIRAS DISPONIVEIS: %d\n" RESET, numFlags);

        printf("\tESCOLHA SUAS COORDENADAS PRA JOGAR\n");  // Faz o usuário escolher as coordenadas que ele deseja para jogar o jogo
        printf("\tAPENAS CAMPOS VAZIOS SAO VALIDOS\n");
        printf("\t(DIGITE X: 0 E Y: 0 PARA SAIR DO JOGO)\n"); // Indica como o usuário sai do jogo durante ele

        printf("\t\tX: ");
        scanf("%d", &y);
        printf("\t\tY: ");
        scanf("%d", &x);

        if (x > 0 && x < SIZE && y > 0 && y < SIZE) {  // Realiza a verificação das coordenadas para que não acesse locais inválidos na matriz

            if (campoClone[x][y] == 'B'){  // Verifica se há uma bomba no local, caso não passa adiante
                printf("\n\n");
                printBomba();
                printf(RED "\n\n\tVoce explodiu....\n\n" RESET);

                return;
            }
            else if (campo[x][y] != '#') printf( RED "\n\tESCOLHA INVALIDA, TENTE NOVAMENTE.\n\n" RESET);
            else {

                if (campoClone[x][y] == '0') verificaCampo(campo, campoClone, x, y, points, pointsValue);
                else {
                    campo[x][y] = campoClone[x][y];  // Compara com a matriz Clone e caso não haja bomba, o elemento recebe o contador da matriz clone no local do '#'
                }   
                
                *points += pointsValue;

                printCampo(campo);

            }

            if (verificaVitoria(campo, campoClone)) {
                printVitoria();
                return;
            }

            flagSuggestion(&numFlags, campo);  // Chama função que sugestiona o posicionamento de bandeiras

            CLEAR_SCREEN();
        }
        else if (x == 0 && y == 0) {
            printf(RED "\tVOCE ACABOU DE SAIR DO JOGO\n" RESET);
            aux = 0;
        }
        else printf(RED "\n\n\tESCOLHA INVALIDA, TENTE NOVAMENTE.\n\n" RESET);
    }

}
