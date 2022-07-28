#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED
#include "interface.h"

typedef struct{
    int Codigo;
    char Nome[51];
    char Telefone[21];
} Cliente;


Cliente DigitarCliente(Tema t);
void ListarClientes(Cliente PouE[], int Quantidade, Tema t);
void PesquisarCliente(Cliente PouE[], int Quantidade, Tema t);

void AtivarCliente(Tema t);
void AtivarCliente2(Tema t);


void InserirCliente(int Codigo, char Nome[], char Telefone[]);
void InserirEmpresa(int Codigo, char Nome[], char Telefone[]);


#endif // CADASTRO_H_INCLUDED