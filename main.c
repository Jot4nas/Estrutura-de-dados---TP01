#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"
#include "processo.c"
#define ARQUIVO ("../processo_043_202409032338.csv") // Arquivo, coloque o caminho correto do arquivo CSV aqui

int main() {
    FILE *arquivo = fopen(ARQUIVO, "r"); // Abre o arquivo CSV para leitura, Talvez seja necessário ajustar o caminho do arquivo
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Processo p; // Processo temporário para leitura
    Processo *processos = NULL; // Ponteiro para armazenar os processos lidos
    processos = malloc(sizeof(Processo)); // Aloca memória para o primeiro processo

    int contarProcessos = 0;
    int capacidade = 0;
    char linha[512];

    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (contarProcessos >= capacidade) {
            if (capacidade == 0) {
                capacidade = 10;
            } else {
                capacidade *= 2;
            }

            Processo *temp = realloc(processos, capacidade * sizeof(Processo));
            if (temp == NULL) {
                perror("Erro ao alocar memória");
                free(processos);
                fclose(arquivo);
                return 1;
            }
            processos = temp;
        }

        int campos_lidos = sscanf(linha, "%d,\"%[^\"]\",%[^,],%[^,],{%d},%d", &p.id, p.numero, p.data, p.classe, &p.id_assunto, &p.ano_eleicao); // Lê os campos do CSV, formato: id, numero, data, classe, {id_assunto}, ano_eleicao

        if (campos_lidos != 6) {
            campos_lidos = sscanf(linha, "%d,\"%[^\"]\",%[^,],\"%[^\"]\",{%d},%d", &p.id, p.numero, p.data, p.classe, &p.id_assunto, &p.ano_eleicao);

            processos[contarProcessos] = p; // Salva o processo no vetor
        }

        if (campos_lidos == 6) {
            processos[contarProcessos] = p; // Salva o processo no vetor
        } 
        contarProcessos++;
    }

    OrdenarProcessosPorId(processos, contarProcessos);
    OrdenarProcessosPorData(processos, contarProcessos);
    ContarProcessosPorClasse(processos, contarProcessos, "{12377}");
    ContarAssuntosDistintos(processos, contarProcessos, capacidade);
    ListarProcessosComMultiplosAssuntos(ARQUIVO);
    CalcularDiasTramitando(processos, contarProcessos);

    free(processos); // Libera memória alocada
    fclose(arquivo); // Fecha o arquivo

    printf("\nQuantidade de Processos lidos: %d\n", contarProcessos + 1);

    printf("\n");
    return 0;
}
