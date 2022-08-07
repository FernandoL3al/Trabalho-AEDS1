#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "interface.h"
#include "cadastro.h"
#include "vagas.h"



//                OBLITERADOR DE VAGAS
//========================================================================
void ObliteratorVagas(char *end_arquivo, char *pattern){   //realmente exclui registro
    Vaga item;
    char new_name[30];
    FILE *arquivo = fopen(end_arquivo, "rb");
    FILE *arquivo_copia = fopen("temp2.txt", "wb");
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&item, sizeof(item), 1, arquivo)){
        if(strcmp(item.Empresa, pattern) == 0) continue;
        fwrite(&item, sizeof(item), 1, arquivo_copia);
    }
    fclose(arquivo); fclose(arquivo_copia);
    strcpy(new_name, end_arquivo);
    remove(end_arquivo);
    rename("temp2.txt", new_name);
}


//                          CRIACAO DE ARQUIVOS DE DADOS INICIAIS
//=====================================================================================================
void DefaultVaga(FILE *arquivo){
    arquivo = fopen("vagas.txt", "wb");
    Vaga defaul[] = {{.Empresa = "Microloft", .Area = "TI", .NomeVaga = "Suporte Tecnico S.O.", .Salario = 1500.00, .Disponivel = 1},
                    {.Empresa = "Kabaum", .Area = "Vendas", .NomeVaga = "Vendedor Online", .Salario = 1900.00, .Disponivel = 1},
                    {.Empresa = "Groogue", .Area = "TI", .NomeVaga = "Desenvolvedor C", .Salario = 400.00, .Disponivel = 1}};
    fseek(arquivo, 0, SEEK_SET);
    fwrite(defaul, sizeof(Vaga), 3, arquivo);
    fclose(arquivo);
}


//                           COMPARA SE EMPRESA EXISTE
//=======================================================================================================
int CompareDados(char *nome, char *end_arquivo, Tema t, FILE *arquivo2){// preciso compara empresas pra so deixar criar vaga se ja tiver cad de empresa
    FILE *arquivo = fopen(end_arquivo, "rb"); int Aut; 
    Cliente Receptor;
    fseek(arquivo, 0, SEEK_SET);
    while(fread(&Receptor, sizeof(Cliente), 1, arquivo)){
        if(strcmp(Receptor.Nome, nome) == 0){
            fclose(arquivo);
            Caixa(16,5,85,15,1);
            Aut = Autenticacao(Receptor, arquivo2, t);
            if(Aut == 1) ReprintTela();
            else return 0;
            return 1;
        }
    }
    if(strcmp(Receptor.Nome, nome)!= 0){
        printf("Empresa sem cadastro!");
        Sleep(1000);
        fclose(arquivo);
        //system("pause");
        return 0;
    }
}


//                               REPRINT TELA CADASTRO
//==================================================================================================
void ReprintTela(){
    Caixa(20,9,77,12,1);
    Gotoxy(22,  11);printf("Vaga:......................................................................"); 
    Gotoxy(22, 15); printf("Area:......................................................................"); 
    Gotoxy(22, 19); printf("Salario:..................................................................."); 
}


//                          DIGITAR VAGA
//=====================================================================================================
void CriarVaga(Tema t, Vaga *C, FILE *arquivo, FILE *arquivo2){
    //Vaga C;
    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                       Cadastro de Vaga                          ");
    Gotoxy(22,  7); printf("Empresa:...................................................................");
    Gotoxy(22,  11);printf("Vaga:......................................................................"); 
    Gotoxy(22, 15); printf("Area:......................................................................"); 
    Gotoxy(22, 19); printf("Salario:..................................................................."); 
    Gotoxy(35,  7); scanf(" %[^\n]", C->Empresa);

    Gotoxy(35, 11); 
    if(CompareDados(C->Empresa, "empresas.txt", t, arquivo2) == 1){
        Gotoxy(35, 11); scanf(" %[^\n]", C->NomeVaga); 
        Gotoxy(35, 15); scanf(" %[^\n]", C->Area); 
        Gotoxy(35, 19); scanf("%lf", &C->Salario);
        C->Disponivel = 1;
    }
    else fclose(arquivo);
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
        if(reg.Disponivel == 1){
            Gotoxy(27, 7 + Quantidade);
            printf("%-29s %-24s %-10.2lf", reg.NomeVaga,
                                reg.Empresa, reg.Salario);
            Quantidade++;

        }
    }               
    Gotoxy(27,  5); printf("Vaga                          Empresa                  Salario     \n");
    Gotoxy(27, 6);  printf("----------------------------- ------------------------ ----------  \n");
    Gotoxy(27, 21); printf("                              %d Vagas                             \n", Quantidade);
    fclose(arquivo);                    
}


//                          PESQUISAR VAGAS
//=====================================================================================================
void PesquisarVaga(Tema t, char *end_arquivo, char *end_arquivo2){
    FILE *arquivo = fopen(end_arquivo, "rb+");
    FILE *arquivo_Cliente = fopen(end_arquivo2, "rb");
    char Empresa[51]; Vaga a; Cliente b;

    int x[] = {37,52,67}, y[] = {14,14,14}; char opcoes[][30] = {"     Alterar     ", "     Excluir      ", "       Sair        "}; int menu; //vars Menu de alterar

    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    
    Gotoxy(27,2); printf("                              Pesquisa                           ");
    Gotoxy(46,  7); printf("    Digite a Empresa:    "); Gotoxy(67, 7); scanf(" %[^\n]", Empresa);
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
            //                   CHECA AUTENTICIDADE
            //==========================================================
            while(fread(&b, sizeof(Cliente), 1, arquivo_Cliente)){
                //             ALTERAR
                //=========================================
                if(menu == 0){         //alterar
                    CriarVaga(t, &a, arquivo, arquivo_Cliente);
                    fseek(arquivo, -sizeof(Vaga), SEEK_CUR);
                    fwrite(&a, sizeof(Vaga), 1, arquivo);
                    fclose(arquivo);
                }
                //             EXCLUIR
                //=========================================
                if(menu == 1){         //excluir
                    if(Autenticacao(b, arquivo_Cliente, t) == 1){ /// AO EXCLUIR , REMOVE TODAS AS VAGAS DE UMA MESMA EMPRESA
                        fclose(arquivo);                           // FUTURAMENTE ALGO A RESOLVER
                        ObliteratorVagas(end_arquivo, Empresa);
                        //fclose(arquivo);
                        return;
                    }
                }
                if(menu != 2){
                    Gotoxy(39, 19);
                    //system("pause");
                    Sleep(1000);
                    return;
                }
            }
            fclose(arquivo_Cliente);
        }
    }               
    Caixa(44, 14 , 30 , 1, 1);
    Gotoxy(46, 15);
    printf("   Empresa n%co encontrada   \n", 198);
    Gotoxy(39, 19);
    //system("pause");
    Sleep(1000);
}


//                                 APLICAR-SE A VAGA
//=======================================================================================================
void AplicarVaga(Tema t){

    int x[] = {40,64}, y[] = {14,14}; 
    char opcoes[][30] = {"        sim        ", "       Sair        "}; 
    int menu;

    FILE *arquivo = fopen("vagas.txt", "rb+");
    FILE *arquivo_Cliente = fopen("pessoas.txt", "rb");
    char vaga[51], nome[51]; 
    Vaga a; 
    Cliente b;

    Cores(t.fundo, t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);

    
    Gotoxy(27,2); printf("                        Aplicar-se a Vaga                        ");
    Gotoxy(36, 7); printf("Digite o nome da vaga: "); scanf(" %[^\n]", vaga);
    while(fread(&a, sizeof(Vaga), 1, arquivo)){
        if((strcmp(vaga, a.NomeVaga) == 0) && (a.Disponivel == 1)){
            Gotoxy(27,  8); printf("Vaga                          Empresa                  Salario     \n");
            Gotoxy(27, 9);  printf("----------------------------- ------------------------ ----------  \n");
            Gotoxy(27, 10);
            printf("%-29s %-24s %-10.2lf", a.NomeVaga,
                              a.Empresa, a.Salario);
            Gotoxy(43, 12); Cores(t.fundo, t.letra); printf("    Deseja aplicar-se a esta vaga?   ");
            Caixa(36,13,49,1,1);
            menu = Menu(x, y, opcoes, 2, t);
            do{
                //            SIM
                //=========================================
                if(menu == 0){     
                    Caixa(36,13,49,1,1);
                    Gotoxy(37, 14); Cores(t.fundo, t.letra); printf("Digite seu nome cadastrado: "); scanf(" %[^\n]", nome);
                    while(fread(&b, sizeof(Cliente), 1, arquivo_Cliente)){
                        if(strcmp(nome, b.Nome) == 0){
                            if(Autenticacao(b, arquivo_Cliente, t) == 1){
                                a.Disponivel = 0;
                                strcpy(a.linked, nome);
                                fseek(arquivo, -sizeof(Vaga), SEEK_CUR);
                                fwrite(&a, sizeof(Vaga), 1, arquivo);
                                fclose(arquivo);
                            }
                        }
                    }
                    fclose(arquivo_Cliente);
                    return;
                }
                //             SAIR
                //=========================================
            }while(menu != 1);  
            fclose(arquivo_Cliente);
            return;
        }
    }               
    Caixa(44, 14 , 30 , 1, 1);
    Gotoxy(46, 15);
    printf("    Vaga n%co encontrada     \n", 198);
    Sleep(1000);
}


//                                       RELATORIO 
//=================================================================================================================
void Relatorio(Tema t){
    int Quantidade = 0;
    Vaga a;
    FILE *arquivo = fopen("vagas.txt", "rb");
    Cores(t.fundo,t.letra); Caixa(0, 0, 118, 28, 1);
    Cores(t.letra, t.fundo); Caixa(3, 2, 112, 24, 1 );
    Cores(t.fundo, t.letra); Caixa(24, 1, 70, 1, 0);
    Cores(t.letra, t.fundo);
    Gotoxy(27,2); printf("                     Vagas Requisitadas                          ");

    fseek(arquivo, 0, SEEK_SET);
    while(fread(&a, sizeof(Vaga), 1, arquivo)){
        if(a.Disponivel == 0){
            Gotoxy(20, 7 + Quantidade);
            printf("%-29s %-24s %-32s", a.NomeVaga, a.Empresa, a.linked);
            Quantidade++;
        }
    }
    Gotoxy(20,  5); printf("Vaga                          Empresa                  Candidato(a)     \n");
    Gotoxy(20, 6);  printf("----------------------------- ------------------------ --------------------------------  \n");
    Gotoxy(20, 21); printf("                        %d Vagas com candidato                          \n", Quantidade);
    Gotoxy(40, 24); system("pause");
    fclose(arquivo);                  
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

    do{
        system("cls");
        ListarVaga(end_arquivo, t);
        Cores(t.fundo, t.letra); Caixa(20, 23 , 80, 1, 0);  

        if(escolha == 1){
            Opcao = Menu(x1, y1, sla2, 2, t);
            ///FUNCAO PRA PESSOA APLICAR A VAGA
            if(Opcao == 0) AplicarVaga(t);
            if(Opcao == 1) Opcao = 2;
        }
        if(escolha == 2){
            Opcao = Menu(x, y, sla, 3, t);
            if(Opcao == 0){        //Novo
                FILE *arquivo_Cliente = fopen("empresas.txt" ,"rb");
                Vaga n;
                arquivo = fopen(end_arquivo, "ab");
                CriarVaga(t, &n, arquivo, arquivo_Cliente);

                fwrite(&n, sizeof(Vaga), 1, arquivo);
                fclose(arquivo);
                fclose(arquivo_Cliente);
            }
            if(Opcao == 1){    //Pesquisar
                PesquisarVaga(t, end_arquivo, "empresas.txt");
            }
        }
    } while(Opcao != 2);
}