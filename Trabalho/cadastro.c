#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "cadastro.h"
Cliente Pessoas[100]; int ContPessoas = 0 ;
Cliente Empresas[100];  int ContEmpresas = 0;


void InserirCliente(int Codigo, char Nome[], char Telefone[]){
    Pessoas[ContPessoas].Codigo = Codigo;
    strcpy(Pessoas[ContPessoas].Nome, Nome);
    strcpy(Pessoas[ContPessoas].Telefone, Telefone);
    ContPessoas++;
}

void InserirEmpresa(int Codigo, char Nome[], char Telefone[]){
    Empresas[ContEmpresas].Codigo = Codigo;
    strcpy(Empresas[ContEmpresas].Nome, Nome);
    strcpy(Empresas[ContEmpresas].Telefone, Telefone);
    ContEmpresas++;
}


Cliente DigitarCliente(Tema t){
    Cliente C;
    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                       Cadastro de Cliente                       ");
    Gotoxy(22,  7); printf("C%cdigo:....................................................................", 162);
    Gotoxy(22,  11);printf("Nome:......................................................................"); 
    Gotoxy(22, 15); printf("Telefone:..................................................................."); 
    Gotoxy(35,  7); scanf("%d", &C.Codigo) ; Gotoxy(35, 11); scanf(" %[^\n]", C.Nome); Gotoxy(35, 15); scanf(" %[^\n]", C.Telefone);
    return C;
}

void ListarClientes(Cliente PouE[], int Quantidade, Tema t){
    Cores(t.fundo,t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    
    Gotoxy(27,2); printf("                              Lista                             ");
    for(int i = 0; i < Quantidade; i++){
        Gotoxy(24, 7 + i);
        printf("%8d %-42s %-14s", PouE[i].Codigo,
              PouE[i].Nome, PouE[i].Telefone);
    }               
    Gotoxy(24,  5); printf("C%cdigo   Nome                                       Telefone        \n", 162);
    Gotoxy(24, 6); printf("-------- ------------------------------------------ -------------- \n");
    Gotoxy(24, 21); printf("                            %d Cadastros                                   \n", Quantidade);

                    
}


void PesquisarCliente(Cliente PouE[], int Quantidade, Tema t){
    int i, Codigo;
    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                              Pesquisa                          ");
    Gotoxy(46,  7); printf("Digite o C%cdigo: ", 162); Gotoxy(63, 7); scanf("%d", &Codigo);
    for(int i = 0; i < Quantidade; i++){
        if(Codigo == PouE[i].Codigo){
            Gotoxy(24, 8); printf("C%cdigo   Nome                                       Telefone        \n", 162);
            Gotoxy(24, 9); printf("-------- ------------------------------------------ -------------- \n");
             Gotoxy(24, 10);
            printf("%8d %-42s %-14s", PouE[i].Codigo,
                 PouE[i].Nome, PouE[i].Telefone);
            Gotoxy(39, 19);
            system("pause");
            return;
        }
    }               
    Caixa(44, 14 , 30 , 1, 1);
    Gotoxy(46, 15);
    printf("   Cliente n%co Cadastrado   \n", 198);
    Gotoxy(39, 19);
    system("pause");
}

void AtivarCliente(Tema t){
    int Opcao;
    int x[] = {36,56,82};
    int y[] = {24,24,24};
    char sla[][20] = {"Novo", "Pesquisar", "Sair"};
    do{
        system("cls");
        ListarClientes(Pessoas, ContPessoas, t);
        Cores(t.fundo, t.letra); Caixa(20, 23 , 80, 1, 0); 
        Opcao = Menu(x, y, sla, 3, t);
        if(Opcao == 0)
            Pessoas[ContPessoas++] = DigitarCliente(t);
        if(Opcao == 1)
            PesquisarCliente(Pessoas, ContPessoas, t);
    } while(Opcao != 2);
}

void AtivarCliente2(Tema t){
    int Opcao;
    int x[] = {36,56,82};
    int y[] = {24,24,24};
    char sla[][20] = {"Novo", "Pesquisar", "Sair"};
    do{
        system("cls");
        ListarClientes(Empresas, ContEmpresas, t);
        Cores(t.fundo , t.letra); Caixa(20, 23 , 80, 1, 0); 
        Opcao = Menu(x, y, sla, 3, t);
        if(Opcao == 0)
            Empresas[ContEmpresas++] = DigitarCliente(t);
        if(Opcao == 1)
            PesquisarCliente(Empresas, ContEmpresas, t);
    } while(Opcao != 2);
}


