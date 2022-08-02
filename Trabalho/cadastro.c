#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "cadastro.h"


//                          DIGITAR HVRS(EDITED)
//=====================================================================================================
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


//                          LISTAR HVRS(EDITED)
//=====================================================================================================
void ListarClientes(Cliente vetor[], int Quantidade, Tema t){
    Cores(t.fundo,t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    
    Gotoxy(27,2); printf("                              Lista                             ");
    for(int i = 0; i < Quantidade; i++){
        Gotoxy(24, 7 + i);
        printf("%8d %-42s %-14s", vetor[i].Codigo,
              vetor[i].Nome, vetor[i].Telefone);
    }               
    Gotoxy(24,  5); printf("C%cdigo   Nome                                       Telefone        \n", 162);
    Gotoxy(24, 6); printf("-------- ------------------------------------------ -------------- \n");
    Gotoxy(24, 21); printf("                            %d Cadastros                                   \n", Quantidade);

                    
}

//                          PESQUISAR HVRS(EDITED, TEMAS)
//=====================================================================================================
void PesquisarCliente(Cliente vetor[], int Quantidade, Tema t){
    int i, Codigo;
    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                              Pesquisa                          ");
    Gotoxy(46,  7); printf("Digite o C%cdigo: ", 162); Gotoxy(63, 7); scanf("%d", &Codigo);
    for(i = 0; i < Quantidade; i++){
        if(Codigo == vetor[i].Codigo){
            Gotoxy(24, 8); printf("C%cdigo   Nome                                       Telefone        \n", 162);
            Gotoxy(24, 9); printf("-------- ------------------------------------------ -------------- \n");
             Gotoxy(24, 10);
            printf("%8d %-42s %-14s", vetor[i].Codigo,
                 vetor[i].Nome, vetor[i].Telefone);
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


//                          ATIVAR CLIENTE HVRS(EDITED, TEMAS)
//=====================================================================================================
void AtivarCliente(Tema t,FILE *arquivo, char *end_arquivo){
    int Opcao;
    int x[] = {36,56,82};
    int y[] = {24,24,24};
    char sla[][20] = {"Novo", "Pesquisar", "Sair"};

    Cliente a, vetor[50]; int Contador = 0;
    arquivo = fopen(end_arquivo,"ab+");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&vetor[Contador], sizeof(Cliente), 1, arquivo)){
        Contador++;
    }
    fclose(arquivo);
    do{
        
        system("cls");
        ListarClientes(vetor, Contador, t);
        Cores(t.fundo, t.letra); Caixa(20, 23 , 80, 1, 0); 
        Opcao = Menu(x, y, sla, 3, t);
        if(Opcao == 0){
            arquivo = fopen(end_arquivo, "ab+");
            a = DigitarCliente(t);
            vetor[Contador++] = a;
            fwrite(&a, sizeof(Cliente), 1, arquivo);
            fclose(arquivo);
        }
        if(Opcao == 1)
            PesquisarCliente(vetor, Contador, t);
    } while(Opcao != 2);    
}


//                          LEITURA 
//=====================================================================================================
void Leitura(FILE *arquivo, Cliente vetor[], char *end_arquivo){
    arquivo = fopen(end_arquivo, "rb+");
    int i = 0;
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&vetor[i], sizeof(Cliente), 1, arquivo)){
        i++;
    }
}


//                          ESCRITA
//=====================================================================================================
void Escrita(FILE *arquivo, Cliente vetor[]){
    fseek(arquivo, 0, SEEK_END);
    fwrite(vetor, sizeof(Cliente), 1, arquivo);
}


//                          CRIACAO DE ARQUIVOS DE DADOS INICIAIS
//=====================================================================================================
void Default(FILE *arquivo, int escolha){
    if(escolha == 1){
        arquivo = fopen("empresas.txt", "wb");
        Cliente defaul[] = {{ .Codigo = 002, .Nome = "Yourbank", .Telefone = "1414989375" },
                            { .Codigo = 023, .Nome = "Microloft", .Telefone = "1374-75701" },
                            { .Codigo = 013, .Nome = "Akazon", .Telefone = "153764-356" },
                            { .Codigo = 233, .Nome = "Kabaum", .Telefone = "53056-9436" },
                            { .Codigo = 453, .Nome = "Groogue", .Telefone = "1958-544" }};
        fseek(arquivo, 0, SEEK_SET);
        fwrite(defaul, sizeof(Cliente), 5, arquivo);
    }
    if (escolha == 2){
        arquivo = fopen("pessoas.txt", "wb");
        Cliente defaul2[] = {{ .Codigo = 100, .Nome = "Joao", .Telefone = "234234-245" },
                            { .Codigo = 101, .Nome = "Jose", .Telefone = "56756-43950" },
                            { .Codigo = 13, .Nome = "Lulosvaldo", .Telefone = "131313-1313" },
                            { .Codigo = 102, .Nome = "Maria", .Telefone = "3453-3585" },
                            { .Codigo = 103, .Nome = "Barbara", .Telefone = "0899-4456" },
                            { .Codigo = 22, .Nome = "Jao Bozonaro", .Telefone = "222222-222" },
                            { .Codigo = 104, .Nome = "Luiza", .Telefone = "12223-34985" }};
        fseek(arquivo, 0, SEEK_SET);
        fwrite(defaul2, sizeof(Cliente), 7, arquivo);
    }
    fclose(arquivo);
    
}


//                          CARREGADOR
//=====================================================================================================
void Carregar(Cliente vetor[], int *Contador, FILE *arquivo){
    int i = 0;
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&vetor[i], sizeof(Cliente), 1, arquivo)){
        i++;
        *Contador += 1; // alterando o valor do endereco apontado
    }
    fclose(arquivo);
}
