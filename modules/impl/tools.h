#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>

// Macros para limpar a tela
#if defined(_WIN32) || defined(_WIN64)
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif

// Função para esperar o usuário pressionar Enter
void waitForEnter();

#endif