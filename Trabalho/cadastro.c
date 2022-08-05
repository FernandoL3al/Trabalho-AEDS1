#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "cadastro.h"
#include "login.h"


//                OBLITERADOR DE REGISTROS
//========================================================================
void ObliteratorCliente(char *end_arquivo, int pattern){   //realmente exclui registro
    Cliente item;
    char new_name[30];
    FILE *arquivo = fopen(end_arquivo, "rb");
    FILE *arquivo_copia = fopen("temp.txt", "wb");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&item, sizeof(item), 1, arquivo)){
        if(item.Codigo == pattern) continue;
        fwrite(&item, sizeof(item), 1, arquivo_copia);
    }
    fclose(arquivo); fclose(arquivo_copia);
    strcpy(new_name, end_arquivo);
    remove(end_arquivo);
    rename("temp.txt", new_name);
}


//                          DIGITAR HVRS(EDITED)
//=====================================================================================================
Cliente DigitarCliente(Tema t, Login *a){
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
    Gotoxy(35, 7); *a = GetLogin(C.Nome);
    return C;
}


//                          LISTAR HVRS(EDITED)
//=====================================================================================================
void ListarClientes(char *end_arquivo, Tema t){
    FILE *arquivo = fopen(end_arquivo, "rb");
    int Quantidade = 0;
    Cliente reg;
    Cores(t.fundo,t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                              Lista                              ");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&reg, sizeof(Cliente), 1, arquivo)){
        Gotoxy(27, 7 + Quantidade);
        printf("%8d %-42s %-14s", reg.Codigo,
              reg.Nome, reg.Telefone);
        Quantidade++;
    }
    Gotoxy(27,  5); printf("C%cdigo   Nome                                       Telefone        \n", 162);
    Gotoxy(27, 6); printf("-------- ------------------------------------------ -------------- \n");
    Gotoxy(27, 21); printf("                            %d Cadastros                                   \n", Quantidade);
    fclose(arquivo);                    
}


//                          PESQUISAR HVRS(EDITED, TEMAS)
//=====================================================================================================
void PesquisarCliente(Tema t, char *end_arquivo){
    FILE *arquivo = fopen(end_arquivo, "rb+");
    int Codigo; Cliente a; Login login;

    int x[] = {37,52,67}, y[] = {14,14,14}; char opcoes[][20] = {"     Alterar     ", "     Excluir      ", "       Sair        "}; int menu; //vars Menu de alterar

    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    
    Gotoxy(27,2); printf("                              Pesquisa                           ");
    Gotoxy(46,  7); printf("    Digite o C%cdigo: ", 162); Gotoxy(67, 7); scanf("%d", &Codigo);
    while(fread(&a, sizeof(Cliente), 1, arquivo)){
        if(Codigo == a.Codigo){
            Gotoxy(27, 8); printf("C%cdigo   Nome                                       Telefone        \n", 162);
            Gotoxy(27, 9); printf("-------- ------------------------------------------ -------------- \n");
            Gotoxy(27, 10);
            printf("%8d %-42s %-14s", a.Codigo,
                 a.Nome, a.Telefone);
            Gotoxy(43, 12); Cores(t.fundo, t.letra); printf(" Deseja excluir ou alterar registro? ");
            Caixa(36,13,49,1,1);
            menu = Menu(x, y, opcoes, 3, t);
            //             ALTERAR
            //=========================================
            if(menu == 0){         //alterar
                a = DigitarCliente(t, &login);
                fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
                fwrite(&a, sizeof(Cliente), 1, arquivo);
                fclose(arquivo);
                return;
            }
            //             EXCLUIR
            //=========================================
            if(menu == 1){         //excluir
                fclose(arquivo);
                ObliteratorCliente(end_arquivo, Codigo);
                return;
            }
            if(menu != 2){
                Gotoxy(39, 19);
                system("pause");
                return;
            }
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
    int Opcao; Login login;
    int x[] = {32,53,71};
    int y[] = {24,24,24};
    char sla[][20] = {"      Novo      ", "   Pesquisar   ", "       Sair        "};
    Cliente a; //vetor[50]; int Contador = 0;

    //arquivo = fopen(end_arquivo,"rb+");
    //fseek(arquivo, 0, SEEK_SET);
    //while(fread(&vetor[Contador], sizeof(Cliente), 1, arquivo)){
    //    Contador++;
    //}
    //fclose;
    do{
        system("cls");
        ListarClientes(end_arquivo, t);
        Cores(t.fundo, t.letra); Caixa(20, 23 , 80, 1, 0); 
        Opcao = Menu(x, y, sla, 3, t);
        if(Opcao == 0){        //Novo
            arquivo = fopen(end_arquivo,"ab");
            a = DigitarCliente(t, &login);
            fwrite(&a, sizeof(Cliente), 1, arquivo);
            fclose(arquivo);
        }
        if(Opcao == 1){    //Pesquisar
            PesquisarCliente( t, end_arquivo);
        }
    } while(Opcao != 2);
}

//                          CRIACAO DE ARQUIVOS DE DADOS INICIAIS
//=====================================================================================================
void Default(FILE *arquivo, int escolha){
    if(escolha == 1){
        arquivo = fopen("empresas.txt", "wb");
        Cliente defaul[] = {{ .Codigo = 023, .Nome = "Microloft", .Telefone = "1374-75701" },
                            { .Codigo = 233, .Nome = "Kabaum", .Telefone = "53056-9436" },
                            { .Codigo = 453, .Nome = "Groogue", .Telefone = "1958-544" }};
        fseek(arquivo, 0, SEEK_SET);
        fwrite(defaul, sizeof(Cliente), 3, arquivo);
    }
    if (escolha == 2){
        arquivo = fopen("pessoas.txt", "wb");
        Cliente defaul2[] = {{ .Codigo = 103, .Nome = "Barbara", .Telefone = "0899-4456" },
                            { .Codigo = 13, .Nome = "Lulosvaldo", .Telefone = "131313-1313" },
                            { .Codigo = 22, .Nome = "Jao Bozonaro", .Telefone = "222222-222" }};
        fseek(arquivo, 0, SEEK_SET);
        fwrite(defaul2, sizeof(Cliente), 3, arquivo);
    }
    fclose(arquivo);
}