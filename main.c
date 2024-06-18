#include <stdio.h>
#include <stdlib.h>
#include "modules/impl/campo.h"
#include "modules/impl/jogo.h"

int main() {
    int aux = 1;
    int pontos = 0;

    do {
        char campo[SIZE][SIZE], campoBombas[SIZE][SIZE], campoJogo[SIZE][SIZE];

        inicializaMenu(&pontos);

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
                jogaJogo(campo, campoJogo, &pontos, 3, 10);
                break;
            case 2:
                printCampo(campo);
                inicializaBombas(26, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, &pontos, 15, 26);
                break;
            case 3:
                printCampo(campo);
                inicializaBombas(57, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, &pontos, 30, 57);
                break;
            case 4:
                printCampo(campo);
                inicializaBombas(80, campoBombas);
                sensorBombas(campoBombas, campoJogo);
                jogaJogo(campo, campoJogo, &pontos, 200, 80);
                break;
            case 5:
                mostraInstrucoes();
                break;
            default:
                aux = 0;
                break;
        }
    } while (aux);

    return 0;
}