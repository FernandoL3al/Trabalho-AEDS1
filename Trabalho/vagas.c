#include <stdio.h>
#include <windows.h>
//#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "vagas.h"
#include "cadastro.h"
//#include "login.h"



//                OBLITERADOR DE VAGAS
//========================================================================
void ObliteratorVagas(char *end_arquivo, char *pattern){   //realmente exclui registro
    Vaga item;
    char new_name[30];
    FILE *arquivo = fopen(end_arquivo, "rb");
    FILE *arquivo_copia = fopen("temp.txt", "wb");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&item, sizeof(item), 1, arquivo)){
        if(strcmp(item.Empresa, pattern) == 0) continue;
        fwrite(&item, sizeof(item), 1, arquivo_copia);
    }
    fclose(arquivo); fclose(arquivo_copia);
    strcpy(new_name, end_arquivo);
    remove(end_arquivo);
    rename("temp.txt", new_name);
}


//                           COMPARA SE EMPRESA EXISTE
//=======================================================================================================
int CompareDados(char *nome, char *end_arquivo, Tema t){// preciso compara empresas pra so deixar criar vaga se ja tiver cad de empresa
    FILE *arquivo = fopen(end_arquivo, "rb");
    Cliente Receptor;
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&Receptor, sizeof(Cliente), 1, arquivo)){
        if(strcmp(Receptor.Nome, nome) != 0){
            printf("Empresa sem cadastro!");
            return 0;
        }
        else Autenticacao(Receptor, arquivo, t);
    }
    fclose(arquivo);
}



//                          CRIACAO DE ARQUIVOS DE DADOS INICIAIS
//=====================================================================================================
void DefaultVaga(FILE *arquivo){
    arquivo = fopen("vagas.txt", "wb");
    Vaga defaul[] = {{.Empresa = "Microloft", .Area = "TI", .NomeVaga = "Suporte Tecnico S.O.", .Salario = 1500.00},
                    {.Empresa = "Kabaum", .Area = "Vendas", .NomeVaga = "Vendedor Online", .Salario = 1900.00},
                    {.Empresa = "Groggue", .Area = "TI", .NomeVaga = "Desenvolvedor C", .Salario = 400.00}};
    fseek(arquivo, 0, SEEK_SET);
    fwrite(defaul, sizeof(Vaga), 3, arquivo);
    fclose(arquivo);
}


//                          DIGITAR VAGA
//=====================================================================================================
Vaga CriarVaga(Tema t){
    Vaga C;
    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                       Cadastro de Vaga                          ");
    Gotoxy(22,  7); printf("Empresa:...................................................................");
    Gotoxy(22,  11);printf("Vaga:......................................................................"); 
    Gotoxy(22, 15); printf("Area:......................................................................"); 
    Gotoxy(22, 19); printf("Salario:..................................................................."); 
    Gotoxy(35,  7); scanf(" %[^\n]", C.Empresa);

    Gotoxy(35, 11); 
    if(CompareDados(C.Empresa, "empresas.txt", t) == 0){
        strcpy(C.Empresa, "Vazio"); strcpy(C.NomeVaga, "Vazio"); strcpy(C.Area, "Vazio"); C.Salario = 00.00;
        ObliteratorVagas("vagas.txt", "Vazio");
        return C; 
    }
    Gotoxy(35, 11); scanf(" %[^\n]", C.NomeVaga); 
    Gotoxy(35, 15); scanf(" %[^\n]", C.Area); 
    Gotoxy(35, 19); scanf("%lf", &C.Salario);
    return C;
}


//                          LISTAR VAGAS
//=====================================================================================================
void ListarVaga(char *end_arquivo, Tema t){
    FILE *arquivo = fopen(end_arquivo, "rb");
    int Quantidade = 0;
    Vaga reg;
    Cores(t.fundo,t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                              Vagas                              ");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&reg, sizeof(Vaga), 1, arquivo)){
        Gotoxy(27, 7 + Quantidade);
        printf("%-29s %-24s %-10.2lf", reg.NomeVaga,
              reg.Empresa, reg.Salario);
        Quantidade++;
    }               
    Gotoxy(27,  5); printf("Vaga                          Empresa                  Salario     \n");
    Gotoxy(27, 6);  printf("----------------------------- ------------------------ ----------  \n");
    Gotoxy(27, 21); printf("                              %d Vagas                             \n", Quantidade);
    fclose(arquivo);                    
}


//                          PESQUISAR VAGAS
//=====================================================================================================
void PesquisarVaga(Tema t, char *end_arquivo){
    FILE *arquivo = fopen(end_arquivo, "rb+");
    char Empresa[30]; Vaga a;

    int x[] = {37,52,67}, y[] = {14,14,14}; char opcoes[][30] = {"     Alterar     ", "     Excluir      ", "       Sair        "}; int menu; //vars Menu de alterar

    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    
    Gotoxy(27,2); printf("                              Pesquisa                           ");
    Gotoxy(46,  7); printf("    Digite a Empresa:    "); Gotoxy(67, 7); scanf("%s", Empresa);
    while(fread(&a, sizeof(Vaga), 1, arquivo)){
        if(strcmp(Empresa, a.Empresa) == 0){
            Gotoxy(27,  8); printf("Vaga                          Empresa                  Salario     \n");
            Gotoxy(27, 9);  printf("----------------------------- ------------------------ ----------  \n");
            Gotoxy(27, 10);
            printf("%-29s %-24s %-10.2lf", a.NomeVaga,
              a.Empresa, a.Salario);
            Gotoxy(43, 12); Cores(t.fundo, t.letra); printf(" Deseja excluir ou alterar registro? ");
            Caixa(36,13,49,1,1);
            menu = Menu(x, y, opcoes, 3, t);
            //             ALTERAR
            //=========================================
            if(menu == 0){         //alterar
                a = CriarVaga(t);
                fseek(arquivo, -sizeof(Vaga), SEEK_CUR);
                fwrite(&a, sizeof(Vaga), 1, arquivo);
                fclose(arquivo);
            }
            //             EXCLUIR
            //=========================================
            if(menu == 1){         //excluir
                fclose(arquivo);
                ObliteratorVagas(end_arquivo, Empresa);
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
    printf("   Empresa n%co encontrada   \n", 198);
    Gotoxy(39, 19);
    system("pause");
}


//                          ATIVAR VAGA
//=====================================================================================================
void AtivarVaga(FILE *arquivo, Tema t, int escolha, char *end_arquivo){
    int Opcao;
    
    int x[] = {31,52,71};
    int y[] = {24,24,24};
    char sla[][30] = {"  Cadastrar Vaga   " , "      Alterar      ", "       Sair        "};
    int x1[] = {37,71};
    int y1[] = {24,24};
    char sla2[][30] = {" Aplicar-se a Vaga ", "       Sair        "};

    Vaga a; 
    do{
        system("cls");
        ListarVaga(end_arquivo, t);
        Cores(t.fundo, t.letra); Caixa(20, 23 , 80, 1, 0); 
        
        if(escolha == 1){
            Opcao = Menu(x1, y1, sla2, 2, t);
            (Opcao == 0) ;//AplicarVaga();
            if(Opcao == 1) Opcao = 2;
            ///FUNCAO PRA PESSOA APLICAR A VAGA
        }
        if(escolha == 2){
            Opcao = Menu(x, y, sla, 3, t);
            if(Opcao == 0){        //Novo
                arquivo = fopen(end_arquivo, "ab");
                a = CriarVaga(t);
                fwrite(&a, sizeof(Vaga), 1, arquivo);
                fclose(arquivo);
            }
            if(Opcao == 1){    //Pesquisar
                PesquisarVaga(t, end_arquivo);
            }
        }
    } while(Opcao != 2);
}