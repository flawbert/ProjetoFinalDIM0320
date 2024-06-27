#ifndef CAMPO_H
#define CAMPO_H

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define SIZE 10

void inicializaCampo(char (*campo)[SIZE]);

void inicializaMenu(int *points);

void printCampo(char campo[SIZE][SIZE]);

void printBomba();

void mostraInstrucoes();

#endif
