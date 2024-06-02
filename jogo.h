#ifndef JOGO_H
#define JOGO_H

#include "campo.h"

void inicializaBombas(int numBomb, char (*campo)[SIZE]);
void sensorBombas(char (*campo)[SIZE], char (*campoClone)[SIZE]);
void jogaJogo(char (*campo)[SIZE], char (*campoClone)[SIZE], int numBomb);

#endif
