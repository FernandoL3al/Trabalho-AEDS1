/*
*
*                           Compilaçao manual:
*           gcc main.c interface.c cadastro.c funcionario.c produto.c venda.c -o T.exe
*
*           Unimontes - Montes Claros - Sistemas de Informação - Primeiro Período
*           Trabalho de AEDS 1
*           Tema : Sistema de Agência de Empregos
*           Professor : Heveraldo
*
*           Alunos : Luis Fernando e Arthur
*           Programa : LFA jobs v1.0
*
*           Data de Início : 25/06/2022    Término : ??/??/????
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "login.h"
#include "cadastro.h"
#include "interface.h"
#include "vagas.h"


//                          CRIACAO PONTEIROS DE ARQUIVO
//=====================================================================================================
FILE *arq_tema;
FILE *arq_empresa;
FILE *arq_pessoa;
FILE *arq_vaga;


//                                  MAIN
//=====================================================================================================
int main(){

    //                     LEITURA DO ARQUIVO TEMAS
    //==================================================================
    Tema Temas[12];
    TemaLoad(arq_tema, Temas);

    //                     MENUS
    //==================================================================
    int Opcao, Opcao1;

    //                    DEFAULT TEMA
    //==================================================================
    Tema z = Temas[0];

    //                 LER/CRIAR ARQUIVOS
    //==================================================================
    arq_empresa = fopen("empresas.txt", "rb+");
    if(arq_empresa == NULL){
        Default(arq_empresa, 1);
        arq_empresa = fopen("empresas.txt", "rb+");
    }
    arq_pessoa = fopen("pessoas.txt", "rb+");
    if(arq_pessoa == NULL){
        Default(arq_pessoa, 2);
        arq_pessoa = fopen("pessoas.txt", "rb+");
    }
    arq_vaga = fopen("vagas.txt", "rb+");
    if(arq_vaga == NULL){
        DefaultVaga(arq_vaga);
        arq_vaga = fopen("vagas.txt", "rb+");
    }
    fclose(arq_empresa); fclose(arq_pessoa); fclose(arq_vaga); 


    //                   LOOP PROGRAMA
    //==================================================================
    do{

        system("cls");
       
        //                  INICIO TELA PRINCIPAL
        //=======================================================
        if(strcmp(z.nome, Temas[9].nome) == 0) Inicio(z, 1);
        else if(strcmp(z.nome, Temas[10].nome) == 0) Inicio(z, 2);
        else Inicio(z, 0);

        //           COORD/OPC   MENU PRINCIPAL
        //=======================================================
        int x[] = {29, 45, 61, 76};
        int y[] = {4, 4, 4, 4};
        char Opcoes[][30] = {"    Cliente      ", "      Vagas      ", "     Temas      ", "       Sair        "};

        //           COORD/OPC  MENU CLIENTE
        //=======================================================
        int x1[] = {34, 34};
        int y1[] = {6, 7};
        char OpcoesCad[][30] = {"Pessoa", "Empresa"};

        //           COORD/OPC   MENU VAGAS
        //=======================================================
        int x2[] = {49, 49};
        int y2[] = {6, 7};
        char OpcoesVagas[][30] = {"Pessoa", "Empresa"};

        //           COORD/OPC   MENU TEMAS
        //=======================================================
        int xcor[] = {64,64,64,64,64,64,64,64,64};
        int ycor[] = {6,7,8,9,10,11,12,13,14};
        char OpCores[][30] = {"Night Mode","Bulbasaur", "Squirtle",
                              "Charmander", "Ekans", "Pikachu",
                               "Lapras", "Chansey", "Matrix"};


        Opcao = Menu(x, y, Opcoes, 4, z);

        //                    CADASTRO
        //=======================================================
        if(Opcao == 0){
             Caixa(33, 5, 10, 2, 1);
             Opcao1 = Menu(x1, y1, OpcoesCad, 2, z);
             if(Opcao1 == 0) AtivarCliente(z, arq_pessoa, "pessoas.txt");
             if(Opcao1 == 1) AtivarCliente(z, arq_empresa, "empresas.txt");
             
        }

        //                    VAGAS
        //=======================================================
        if(Opcao == 1) {
             Caixa(48, 5, 10, 2, 1);
             Opcao1 = Menu(x2, y2, OpcoesVagas, 2, z);
             if(Opcao1 == 0) AtivarVaga(arq_vaga, z, 1, "vagas.txt");
             if(Opcao1 == 1) AtivarVaga(arq_vaga, z, 2, "vagas.txt");
        }

        //                    TEMAS
        //=======================================================
        if(Opcao == 2){
            Caixa(63, 5, 10, 9, 1);
            Opcao1 = Menu(xcor, ycor, OpCores, 9, z);
            if(Opcao1 != -1)
                z = Temas[Opcao1];
            if(Opcao1 == 9){
                z = Temas[EseG(z)];
            }
        }
    } while (Opcao != 3);

    fclose(arq_empresa); //precaucao
    fclose(arq_pessoa);


    //                   MENSAGEM FINAL
    //==================================================================
    TelaFinal(z);
    

    //                 RETORNO AO PADRAO DO TERMINAL
    //==================================================================
   Cores(0,15);
   system("cls");
   return 0;
}