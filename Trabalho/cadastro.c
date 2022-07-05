#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "cadastro.h"

Cliente Clientes[100];
int ContClientes = 0 , z = 3;

void InserirCliente(int Codigo, char Nome[], char Telefone[], double Limite){
    Clientes[ContClientes].Codigo = Codigo;
    strcpy(Clientes[ContClientes].Nome, Nome);
    strcpy(Clientes[ContClientes].Telefone, Telefone);
    Clientes[ContClientes].Limite = Limite;
    ContClientes++;
}

void MostrarTelaCliente(int z){

    Cores(MenuCor(z),BLACK);
    Caixa(21, 6, 75, 12, 0);
    LinCol(22,  7); printf("============================= Cadastro de Clientes ========================");
    LinCol(22,  8); printf("             Codigo:   ");
    LinCol(22,  9); printf("             Nome:     ");
    LinCol(22, 10); printf("             Telefone: ");
    LinCol(22, 11); printf("             Limite:   ");
    LinCol(22, 12); printf("===========================================================================");
}
Cliente DigitarCliente(int z){
    Cliente C;
    Cores(MenuCor(z),BLACK);
    Caixa(21, 6, 75, 12, 0);
    LinCol(22,  7); printf("============================= Cadastro de Clientes ========================");
    LinCol(22,  8); printf("             Codigo:   ");LinCol(46,  8); scanf("%d", &C.Codigo);
    LinCol(22,  9); printf("             Nome:     ");LinCol(46,  9); scanf(" %[^\n]", C.Nome);
    LinCol(22, 10); printf("             Telefone: ");LinCol(46, 10); scanf(" %[^\n]", C.Telefone);
    LinCol(22, 11); printf("             Limite:   ");LinCol(46, 11); scanf("%lf", &C.Limite);
    LinCol(22, 12); printf("===========================================================================");
    return C;
}

void MostrarCliente(Cliente C, int z){
    Cores(MenuCor(z),BLACK);
    Caixa(21, 6, 75, 12, 0);
    LinCol(22,  7); printf("%d", C.Codigo);
    LinCol(22,  9); printf("%s", C.Nome);
    LinCol(22, 11); printf("%s", C.Telefone);
    LinCol(22, 13); printf("%.2lf", C.Limite);
}
void LimparCliente(int z){
    Cores(MenuCor(z),BLACK);
    Caixa(21, 6, 75, 12, 0);
    LinCol(22,  7); printf("%*s", 10, " ");
    LinCol(22,  9); printf("%*s", 60, " ");
    LinCol(22, 11); printf("%*s", 40, " ");
    LinCol(22, 13); printf("%*s", 20, " ");
}
void ListarClientes(Cliente Clientes[], int Quantidade, int z){
    Cores(MenuCor(z),BLACK);
    Caixa(21, 6, 75, 12, 0);
    int i;
    system("cls");
    printf("Lista de Clientes\n");
    printf("============================================================================");

    printf("============================================================================\n\n");
    printf("Codigo Nome                                   Telefone       Limite\n");
    printf("------ -------------------------------------- -------------- ----------\n");
    for(i = 0; i < Quantidade; i++){
        printf("%6d %-38s %-14s %10.2lf\n", Clientes[i].Codigo,
              Clientes[i].Nome, Clientes[i].Telefone,
              Clientes[i].Limite);
    }
    printf("============================================================================\n\n");
    printf("%d Clientes Cadastrados\n", Quantidade);
    system("pause");
}
void PesquisarCliente(Cliente Clientes[], int Quantidade){
    Cores(MenuCor(z),BLACK);
    Caixa(21, 6, 75, 12, 0);
    int i, Codigo;
    LinCol(22,  7); scanf("%d", &Codigo);
    for(i = 0; i < Quantidade; i++){
        if(Clientes[i].Codigo == Codigo){
            MostrarCliente(Clientes[i], z);
            LinCol(10, 19);
            system("pause");
            return;
        }
    }
    LinCol(22, 15);
    printf("Cliente nao Cadastrado                 \n");
    system("pause");
}

void AtivarCliente(int z){
    int Opcao;
    do{
        system("cls");
        MostrarTelaCliente(z);
        LinCol(22,18);
        printf("1- Novo, 2- Pesquisar, ");
        printf("3- Listar, 0- Sair :        ");
        LinCol(70, 18);
        scanf("%d", &Opcao);
        LimparCliente(z);
        if(Opcao == 1)
            Clientes[ContClientes++] = DigitarCliente(z);
        if(Opcao == 2)
            PesquisarCliente(Clientes, ContClientes);
        if(Opcao == 3)
            ListarClientes(Clientes, ContClientes, z);
    } while(Opcao != 0);
}

int CarregarClientes(char Texto[][20]){
    int i;
    for(i = 0; i < ContClientes; i++){
        strcpy(Texto[i], Clientes[i].Nome);
    }
    return ContClientes;
}
