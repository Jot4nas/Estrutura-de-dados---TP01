#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

// Função para verificar se um valor existe no vetor
static int ExisteNoVetor(int *vetor, int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) return 1;
    }
    return 0;
}

// Função para ordenar processos por ID em ordem crescente
void OrdenarProcessosPorId(Processo *vetor, int n) {
    int i, j;
    Processo chave;
    FILE *arquivo_crescente = fopen("processo_043_202409032338 - CRESCENTE.csv", "w+");

    // Ordenação por inserção (Insertion Sort)
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j].id > chave.id) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }

    // Escreve o cabeçalho no arquivo
    fprintf(arquivo_crescente, "id,numero,data,classe,assunto,ano Eleicao\n");

    // Salva os dados ordenados no arquivo
    for (int i = 0; i <= n; i++) {
        if (vetor[i].id == 0 && vetor[i].id_assunto == 0 && vetor[i].ano_eleicao == 0) continue; // Ignora registros inválidos
        fprintf(arquivo_crescente, "%d,%s,%s,%s,%d,%d\n",vetor[i].id, vetor[i].numero, vetor[i].data, vetor[i].classe,vetor[i].id_assunto, vetor[i].ano_eleicao);
    }

    fclose(arquivo_crescente);
}

// Função para ordenar processos por data em ordem decrescente
void OrdenarProcessosPorData(Processo *vetor, int n) {
    int i, j;
    Processo chave;
    FILE *arquivo_decrescente = fopen("processo_043_202409032338 - DECRESCENTE por DATA.csv", "w+");

    // Algoritmo de ordenação por inserção (Insertion Sort)
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        while (j >= 0 && strcmp(vetor[j].data, chave.data) < 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }

    // Escreve o cabeçalho no arquivo
    fprintf(arquivo_decrescente, "ID,Numero,Data,Classe,Assunto,Ano Eleicao\n");

    // Salva os dados ordenados no arquivo
    for (int i = 0; i <= n; i++) {
        if (vetor[i].id == 0 && vetor[i].id_assunto == 0 && vetor[i].ano_eleicao == 0) continue; // Ignora registros inválidos
        fprintf(arquivo_decrescente, "%d,%s,%s,%s,%d,%d\n",vetor[i].id, vetor[i].numero, vetor[i].data, vetor[i].classe,vetor[i].id_assunto, vetor[i].ano_eleicao);
    }

    fclose(arquivo_decrescente);
}

// Função para contar processos de uma classe específica
void ContarProcessosPorClasse(Processo *vetor, int n, const char *classe_alvo) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(vetor[i].classe, classe_alvo) == 0) {
            contador++;
        }
    }
    printf("\nTotal de processos com id_classe = %s: %d\n", classe_alvo, contador);
}

// Função para contar o número de assuntos distintos
void ContarAssuntosDistintos(Processo *vetor, int n, int capacidade) {
    int distintos[capacidade];
    int total = 0;

    for (int i = 0; i < n; i++) {
        if (!ExisteNoVetor(distintos, total, vetor[i].id_assunto)) {
            distintos[total++] = vetor[i].id_assunto;
        }
    }

    printf("\nTotal de id_assuntos distintos: %d\n", total);
}

// Função para listar processos que possuem múltiplos assuntos
void ListarProcessosComMultiplosAssuntos(const char *caminho_csv_original) {
    FILE *arquivo = fopen(caminho_csv_original, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para multiplos assuntos");
        return;
    }

    char linha[512];
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    printf("\nProcessos com mais de um id_assunto:\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *ptr_inicio = strchr(linha, '{');
        char *ptr_fim = strchr(linha, '}');

        // Verifica se há múltiplos assuntos no formato {assunto1, assunto2}
        if (ptr_inicio && ptr_fim && (ptr_fim - ptr_inicio) > 1) {
            char conteudo[100];
            strncpy(conteudo, ptr_inicio + 1, ptr_fim - ptr_inicio - 1);
            conteudo[ptr_fim - ptr_inicio - 1] = '\0';

            if (strchr(conteudo, ',')) { // Verifica se há vírgula (indicando múltiplos assuntos)
                printf("%s", linha);
            }
        }
    }

    fclose(arquivo);
}

// Função para calcular o número de dias que cada processo está em tramitação
void CalcularDiasTramitando(Processo *vetor, int n) {
    printf("\nDias de tramitacao de cada processo:\n");

    for (int i = 0; i < n; i++) {
        struct tm data_processo = {0};
        sscanf(vetor[i].data, "%d-%d-%d %d:%d:%d",&data_processo.tm_year, &data_processo.tm_mon, &data_processo.tm_mday,&data_processo.tm_hour, &data_processo.tm_min, &data_processo.tm_sec);

        data_processo.tm_year -= 1900; // Ajusta ano
        data_processo.tm_mon -= 1;    // Ajusta mês

        time_t t_processo = mktime(&data_processo);
        time_t t_atual = time(NULL);

        // Calcula a diferença em segundos e converte para dias
        double segundos = difftime(t_atual, t_processo);
        int dias = (int)(segundos / (60 * 60 * 24));

        printf("Processo ID \"%d\" esta em tramitacao ha %d dias.\n", vetor[i].id, dias);
    }
}
