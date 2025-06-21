#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_ERROS 3
#define MAX_NIVEIS 5
#define TAM_LINHA 512

typedef enum {
    JOGAR = 1,
    SAIR
} OpcaoMenu;

typedef struct {
    char* texto;
    char** alternativas;
    char resposta_correta;
    int num_alternativas;
} Pergunta;

typedef struct {
    Pergunta* perguntas;
    int num_perguntas;
} Nivel;

Nivel carregar_perguntas_do_arquivo(const char* nome_arquivo) {
    Nivel nivel;
    nivel.num_perguntas = 0;
    nivel.perguntas = NULL;

    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(1);
    }

    char linha[TAM_LINHA];
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '\n') continue; 

        Pergunta p;
        p.texto = strdup(linha);
        p.num_alternativas = 0;
        p.alternativas = NULL;

        while (fgets(linha, sizeof(linha), arquivo)) {
            if (strncmp(linha, "RESPOSTA:", 9) == 0) {
                p.resposta_correta = toupper(linha[9]);
                break;
            }
            p.alternativas = realloc(p.alternativas, (p.num_alternativas + 1) * sizeof(char*));
            p.alternativas[p.num_alternativas] = strdup(linha);
            p.num_alternativas++;
        }

        nivel.perguntas = realloc(nivel.perguntas, (nivel.num_perguntas + 1) * sizeof(Pergunta));
        nivel.perguntas[nivel.num_perguntas] = p;
        nivel.num_perguntas++;
    }

    fclose(arquivo);
    return nivel;
}

void liberar_nivel(Nivel* nivel) {
    for (int i = 0; i < nivel->num_perguntas; i++) {
        free(nivel->perguntas[i].texto);
        for (int j = 0; j < nivel->perguntas[i].num_alternativas; j++) {
            free(nivel->perguntas[i].alternativas[j]);
        }
        free(nivel->perguntas[i].alternativas);
    }
    free(nivel->perguntas);
}

int main() {
    Nivel niveis[MAX_NIVEIS];
    char nome_arquivo[30];
    srand(time(NULL));

    for (int i = 0; i < MAX_NIVEIS; i++) {
        sprintf(nome_arquivo, "nivel%d.txt", i + 1);
        niveis[i] = carregar_perguntas_do_arquivo(nome_arquivo);
    }

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Jogar\n");
        printf("2. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == JOGAR) {
            int nivel = 0;
            int erros = 0;
            char resposta;

            printf("\nBem-vindo ao Jogo de Perguntas de Algoritmos!\n");
            printf("Responda corretamente para avancar de nivel. 3 erros e o jogo acaba.\n\n");

            while (nivel < MAX_NIVEIS && erros < MAX_ERROS) {
                Nivel atual = niveis[nivel];
                int perguntaIndex = rand() % atual.num_perguntas;
                Pergunta p = atual.perguntas[perguntaIndex];

                printf("Nivel %d:\n", nivel + 1);
                printf("%s", p.texto);
                for (int i = 0; i < p.num_alternativas; i++) {
                    printf("%s", p.alternativas[i]);
                }

                do {
                    printf("Sua resposta: ");
                    scanf(" %c", &resposta);
                    resposta = toupper(resposta);
                    if (resposta < 'A' || resposta >= 'A' + p.num_alternativas) {
                        printf("Resposta invalida! Por favor digite uma letra entre A e %c.\n", 'A' + p.num_alternativas - 1);
                    }
                } while (resposta < 'A' || resposta >= 'A' + p.num_alternativas);

                if (resposta == p.resposta_correta) {
                    printf("Correto!\n\n");
                    nivel++;
                } else {
                    printf("Errado!\n\n");
                    erros++;
                }
            }

            if (nivel == MAX_NIVEIS) {
                printf("Parabens! Voce venceu o jogo!\n");
            } else {
                printf("Voce perdeu! Numero maximo de erros atingido.\n");
            }
        } else if (opcao != SAIR) {
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != SAIR);

    for (int i = 0; i < MAX_NIVEIS; i++) {
        liberar_nivel(&niveis[i]);
    }

    return 0;
}
