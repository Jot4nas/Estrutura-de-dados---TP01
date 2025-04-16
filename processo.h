#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct {
    int id;
    char numero[50];
    char data[50];
    char classe[50];
    int id_assunto;
    int ano_eleicao;
} Processo;

void OrdenarProcessosPorId(Processo *vetor, int n);
void OrdenarProcessosPorData(Processo *vetor, int n);
void ContarProcessosPorClasse(Processo *vetor, int n, const char *classe_alvo);
void ContarAssuntosDistintos(Processo *vetor, int n, int capacidade);
void ListarProcessosComMultiplosAssuntos(const char *caminho_csv_original);
void CalcularDiasTramitando(Processo *vetor, int n);

#endif