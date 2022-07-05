#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "funcionario.h"

Funcionario Funcionarios[100];
int ContFuncionarios;

void InserirFuncionario(int Registro, char Nome[], char Cargo[]){
    Funcionarios[ContFuncionarios].Registro = Registro;
    strcpy(Funcionarios[ContFuncionarios].Nome, Nome);
    strcpy(Funcionarios[ContFuncionarios].Cargo, Cargo);
    ContFuncionarios++;
}

void ListarFuncionarios(Funcionario Funcionarios[], int Quantidade){
    int i;
    system("cls");
    printf("Lista de Clientes\n");
    printf("=======================================================================\n\n");
    printf("Registro Nome                                   Cargo                    \n");
    printf("-------- -------------------------------------- -------------------------\n");
    for(i = 0; i < Quantidade; i++){
        printf("%6d %-38s %-14s \n", Funcionarios[i].Registro,
              Funcionarios[i].Nome, Funcionarios[i].Cargo);
    }
    printf("=======================================================================\n\n");
    printf("%d Funcionarios Cadastrados\n", Quantidade);
    system("pause");
}

void AtivarFuncionario(){
    system("cls");
    ListarFuncionarios(Funcionarios, ContFuncionarios);
}

int CarregarFuncionarios(char Texto[][20]){
    int i;
    for(i = 0; i < ContFuncionarios; i++){
        strcpy(Texto[i], Funcionarios[i].Nome);
    }
    return ContFuncionarios;
}

