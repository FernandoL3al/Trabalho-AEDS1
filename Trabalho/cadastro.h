#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED
#include "interface.h"

typedef struct{
    int Codigo;
    char Nome[51];
    char Telefone[21];
} Cliente; // tamanho de Cliente 76 bytes



Cliente DigitarCliente(Tema t);
void ListarClientes(Cliente PouE[], int Quantidade, Tema t);
void PesquisarCliente(Cliente PouE[], int Quantidade, Tema t);

void AtivarCliente(Tema t,Cliente Bdados[], int Contador, FILE *arquivo);

void CarregarCliente(Cliente Bdados[], Cliente Bdados2[], int *Contador, int *Contador2, FILE *arq_empresa, FILE *arq_pessoa);

void Leitura(FILE *arquivo, Cliente vetor[], char *end_arquivo);

void Escrita(FILE *arquivo, Cliente vetor[]);

void Carregar(Cliente vetor[], int *Contador, FILE *arquivo);

void Default(FILE *arquivo, int escolha);

#endif // CADASTRO_H_INCLUDED