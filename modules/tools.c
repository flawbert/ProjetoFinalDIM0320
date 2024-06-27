#include "impl/tools.h"

void waitForEnter() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Ignora qualquer entrada anterior
    getchar(); // Espera por Enter
}
