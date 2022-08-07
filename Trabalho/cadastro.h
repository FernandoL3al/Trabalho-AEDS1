#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED
#include "interface.h"



//                          TIPO STRUCT CLIENTE
//=====================================================================================================
typedef struct{
    int Codigo;
    char Nome[51];
    char Telefone[21];
    char Senha[31];
} Cliente; 


//                          HVRS FUNCTIONS
//=====================================================================================================
Cliente DigitarCliente(Tema t, FILE *arquivo);

void ListarClientes(char *end_arquivo, Tema t);

void PesquisarCliente(Tema t, char *end_arquivo);


void AtivarCliente(Tema t,FILE *arquivo, char *end_arqivo);


//                OBLITERADOR DE REGISTROS
//========================================================================
void ObliteratorCliente(char *end_arquivo, int pattern);


//                       FUNCOES DE SEGURANCA
//======================================================================================

void GetLogin(Cliente *C, FILE *arquivo, Tema t);

int Autenticacao(Cliente z, FILE *arquivo, Tema t);

#endif // CADASTRO_H_INCLUDED