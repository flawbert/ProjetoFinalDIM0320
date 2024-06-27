#include <stdio.h>
#include <stdlib.h>
#include "modules/impl/tools.h"
#include "modules/impl/campo.h"
#include "modules/impl/jogo.h"

int main() {
    int aux = 1;
    int pontos = 0;

    do {
        char campo[SIZE][SIZE], campoBombas[SIZE][SIZE], campoJogo[SIZE][SIZE];

        CLEAR_SCREEN();
        inicializaMenu(&pontos);

        int op;

        printf("\n\t\t  ESCOLHA: ");
        scanf("%d", &op);

        inicializaCampo(campo);
        inicializaCampo(campoBombas);
        inicializaCampo(campoJogo);

        switch (op) {
            case 1:
                CLEAR_SCREEN();
                inicializaBombas(10, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, &pontos, 3, 10);
                waitForEnter();
                break;
            case 2:
                CLEAR_SCREEN();
                inicializaBombas(26, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, &pontos, 15, 26);
                waitForEnter();
                break;
            case 3:
                CLEAR_SCREEN();
                inicializaBombas(57, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, &pontos, 30, 57);
                waitForEnter();
                break;
            case 4:
                CLEAR_SCREEN();
                inicializaBombas(80, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, &pontos, 200, 80);
                waitForEnter();
                break;
            case 5:
                CLEAR_SCREEN();
                mostraInstrucoes();
                waitForEnter();
                break;
            default:
                CLEAR_SCREEN();
                printf(RED"\n\n\tATE A PROXIMA\n\n\tREINICIE O JOGO\n\n" RESET);
                aux = 0;
                break;
        }
    } while (aux);

    return 0;
}