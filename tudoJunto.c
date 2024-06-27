#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

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
    printf("||||||||||||||||||||||||||||||||||||||||||||||\n");
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
    printf("||||||||||||||||||||||||||||||||||||||||||||||\n");
}

void printCampo(char campo[SIZE][SIZE]) {
    printf("\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("\t");
        for (int j = 0; j < SIZE; j++) {
            printf("%c  ", campo[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printBomba() {
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

void mostraInstrucoes() {
    printf("\n\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||\n");
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
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n\n");
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
            printf("\tPOSICAO INVALIDA PARA BANDEIRA, TENTE NOVAMENTE.\n");
            return 0; // Retorna 0 indicando que nenhuma ação foi tomada
        }
    } else {
        printf("\tPOSICAO INVALIDA PARA BANDEIRA, TENTE NOVAMENTE.\n");
        return 0; // Retorna 0 indicando que nenhuma ação foi tomada
    }
}

void flagSuggestion (int *numFlags, char (*campo)[SIZE]) { // Posicionamento da bandeira 
    char opFlag;

    while (1) {
        printf("\tVOCE QUER POSICIONAR OU RETIRAR UMA BANDEIRA( Y - SIM || N - NAO)? ");
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
            printf("\tA OPCAO NAO EH VALIDA, TENTE NOVAMENTE.\n");
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
    printf("\n\n");
    printf("\t|||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\t|||                                           |||\n");
    printf("\t|||               PARABENS!                   |||\n");
    printf("\t|||            VOCE VENCEU O JOGO!            |||\n");
    printf("\t|||                                           |||\n");
    printf("\t|||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n\n");

}

void jogaJogo (char (*campo)[SIZE], char (*campoClone)[SIZE], int *points, int pointsValue, int numFlags) {
    int aux = 1;


    while (aux) {
        int x = 0, y = 0;

        printf("\tPONTUACAO: %d\n", *points);
        printf("\tBANDEIRAS DISPONIVEIS: %d\n", numFlags);

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
                printf("\n\n\tVoce explodiu....\n\n");

                return;
            }
            else if (campo[x][y] != '#') printf("\n\tESCOLHA INVALIDA, TENTE NOVAMENTE.\n\n");
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

        }
        else if (x == 0 && y == 0) {
            printf("\tVOCE ACABOU DE SAIR DO JOGO\n");
            aux = 0;
        }
        else printf("\n\n\tESCOLHA INVALIDA, TENTE NOVAMENTE.\n\n");
    }

}


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
                printf("\n\n\tATE A PROXIMA\n\n\tREINICIE O JOGO\n\n");
                aux = 0;
                break;
        }
    } while (aux);

    return 0;
}