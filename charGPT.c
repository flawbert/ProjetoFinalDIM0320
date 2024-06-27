#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição das cores do terminal
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define SIZE 10

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void wait_for_enter() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
    getchar();
}

void inicializaCampo(char (*campo)[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 && j > 0) {
                campo[i][j] = '0' + j;
            } else if (j == 0 && i > 0) {
                campo[i][j] = '0' + i;
            } else if (i == 0 && j == 0) {
                campo[i][j] = '@';
            } else {
                campo[i][j] = '#';
            }
        }
    }
}

void inicializaMenu(int *points) {
    clear_screen();
    printf("\n");
    printf(YELLOW "||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||        BEM VINDO AO CAMPO-MINADO       |||\n");
    printf("|||                                        |||\n");
    printf("|||            SEUS PONTOS: %-7d        |||\n", *points);
    printf("|||                                        |||\n");
    printf("|||         ESCOLHA SUA DIFICULDADE        |||\n");
    printf("|||                                        |||\n");
    printf("|||                                        |||\n");
    printf("|||            1 - FACIL                   |||\n");
    printf("|||            2 - NORMAL                  |||\n");
    printf("|||            3 - DIFICIL                 |||\n");
    printf("|||            4 - IMPOSSIVEL              |||\n");
    printf("|||            5 - INSTRUCOES              |||\n");
    printf("|||                                        |||\n");
    printf("|||           APERTE '0' PARA SAIR         |||\n");
    printf("|||                                        |||\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||\n" RESET);
}

void printCampo(char campo[SIZE][SIZE]) {
    printf("\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("\t");
        for (int j = 0; j < SIZE; j++) {
            if (campo[i][j] == 'B') {
                printf(RED "%c  " RESET, campo[i][j]);
            } else if (campo[i][j] == '>') {
                printf(CYAN "%c  " RESET, campo[i][j]);
            } else {
                printf("%c  ", campo[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printBomba() {
    printf(RED "\t       _.-^^---....,,--\n");
    printf("\t   _--                  --_\n");
    printf("\t  <                        >)\n");
    printf("\t  |                         |\n");
    printf("\t   \\._                   _./\n");
    printf("\t      ```--. . , ; .--'''\n");
    printf("\t            | |   |\n");
    printf("\t         .-=||  | |=-.\n");
    printf("\t         `-=#$#&#$#=-'\n");
    printf("\t            | ;  :|\n");
    printf("\t   _____.,-##&$@##&#~,._____\n" RESET);
}

void mostraInstrucoes() {
    clear_screen();
    printf("\n\n");
    printf(CYAN "|||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("|||            INSTRUCOES DO JOGO             |||\n");
    printf("|||                                           |||\n");
    printf("|||  1. Escolha a dificuldade do jogo.        |||\n");
    printf("|||                                           |||\n");
    printf("|||  2. O campo de jogo sera gerado com as    |||\n");
    printf("|||     bombas posicionadas aleatoriamente.   |||\n");
    printf("|||                                           |||\n");
    printf("|||  3. Voce deve escolher coordenadas para   |||\n");
    printf("|||     revelar os campos.                    |||\n");
    printf("|||                                           |||\n");
    printf("|||  4. Quando voce revela um campo, o jogo   |||\n");
    printf("|||     mostra quantas bombas estao ao redor  |||\n");
    printf("|||     dos campos em volta desse campo, o    |||\n");
    printf("|||     marcando como '-'.                    |||\n");
    printf("|||                                           |||\n");
    printf("|||  5. Se voce revelar uma bomba, voce perde.|||\n");
    printf("|||                                           |||\n");
    printf("|||  6. O objetivo eh revelar todos os campos |||\n");
    printf("|||     sem bombas.                           |||\n");
    printf("|||                                           |||\n");
    printf("|||  7. Voce pode sair do jogo a qualquer     |||\n");
    printf("|||     momento digitando 0 para X e Y.       |||\n");
    printf("|||                                           |||\n");
    printf("|||  8. Voce pode colocar bandeiras em        |||\n");
    printf("|||     campos suspeitos digitando 'Y' quando |||\n");
    printf("|||     for solicitado, ou negando ao digitar |||\n");
    printf("|||     'N'.                                  |||\n");
    printf("|||                                           |||\n");
    printf("|||  9. Apos revelar todos os campos sem      |||\n");
    printf("|||     bombas, voce acumula pontos e vence   |||\n");
    printf("|||     o jogo.                               |||\n");
    printf("|||                                           |||\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||\n" RESET);
    printf("\n\n");
    wait_for_enter();
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
    if (x <= 0 || x >= SIZE || y <= 0 || y >= SIZE) {
        printf(RED "Coordenadas invalidas! Tente novamente.\n" RESET);
    } else if (campo[y][x] == '>') {
        printf(YELLOW "Campo ja revelado. Tente outra coordenada.\n" RESET);
    } else if (campo[y][x] == 'B') {
        clear_screen();
        printCampo(campo);
        printf(RED "\nVoce perdeu!\n" RESET);
        printBomba();
        *points -= pointsValue;
        wait_for_enter();
    } else {
        campo[y][x] = '>';
        campoClone[y][x] = '>';
        *points += pointsValue;
    }
}

int main() {
    int points = 0;
    int opcao;
    int numBomb, pointsValue;
    char campo[SIZE][SIZE], campoClone[SIZE][SIZE];

    do {
        inicializaMenu(&points);
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Facil
                numBomb = 10;
                pointsValue = 1;
                break;
            case 2: // Normal
                numBomb = 20;
                pointsValue = 2;
                break;
            case 3: // Dificil
                numBomb = 30;
                pointsValue = 3;
                break;
            case 4: // Impossivel
                numBomb = 40;
                pointsValue = 4;
                break;
            case 5: // Instruções
                mostraInstrucoes();
                continue;
            case 0:
                printf(RED "\nSaindo do jogo...\n" RESET);
                exit(0);
            default:
                printf(RED "\nOpcao invalida! Tente novamente.\n" RESET);
                continue;
        }

        inicializaCampo(campo);
        inicializaCampo(campoClone);
        inicializaBombas(numBomb, campo);
        sensorBombas(campo, campoClone);

        int x, y;
        do {
            clear_screen();
            printCampo(campo);
            printf(CYAN "\nPontuacao: %d\n" RESET, points);
            printf("Digite as coordenadas X e Y (0 para sair): ");
            scanf("%d %d", &x, &y);

            if (x == 0 || y == 0) {
                printf(RED "\nSaindo do jogo...\n" RESET);
                exit(0);
            }

            verificaCampo(campo, campoClone, x, y, &points, pointsValue);
        } while (x != 0 && y != 0);
    } while (1);

    return 0;
}