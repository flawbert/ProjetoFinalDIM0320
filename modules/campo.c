#include <stdio.h>
#include "impl/campo.h"



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
            if (campo[i][j] == '>') printf(BLUE "%c  " RESET, campo[i][j]);
            else printf("%c  ", campo[i][j]);
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
    printf("\n\n");
    printf(YELLOW "|||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
}