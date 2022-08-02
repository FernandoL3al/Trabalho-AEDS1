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
#include "cadastro.h"
#include "interface.h"


//                          CRIACAO PONTEIROS DE ARQUIVO
//=====================================================================================================
FILE *arq_tema;
FILE *arq_empresa;
FILE *arq_pessoa;


//                                  MAIN
//=====================================================================================================
int main(){

    //                     LEITURA DO ARQUIVO TEMAS
    //==================================================================
    Tema Temas[11];
    TemaLoad(arq_tema, Temas);

    //                     MENUS
    //==================================================================
    int Opcao, Opcao1;

    //                    DEFAULT TEMA
    //==================================================================
    Tema z = Temas[2];

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
    fclose(arq_empresa); fclose(arq_pessoa);


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
        int x[] = {34, 49, 64, 79};
        int y[] = {4, 4, 4, 4};
        char Opcoes[][20] = {"Cliente", "Vagas", "Temas", "Sair"};

        //           COORD/OPC  MENU CLIENTE
        //=======================================================
        int x1[] = {25, 25};
        int y1[] = {6, 7};
        char OpcoesCad[][20] = {"Pessoa", "Empresa"};

        //           COORD/OPC   MENU VAGAS
        //=======================================================
        int x2[] = {};
        int y2[] = {};

        //           COORD/OPC   MENU TEMAS
        //=======================================================
        int xcor[] = {70,70,70,70,70,70,70,70,70};
        int ycor[] = {6,7,8,9,10,11,12,13,14};
        char OpCores[][20] = {"Night Mode","Bulbasaur", "Squirtle",
                              "Charmander", "Ekans", "Pikachu",
                               "Lapras", "Chansey", "Matrix"};


        Opcao = Menu(x, y, Opcoes, 4, z);

        //                    CADASTRO
        //=======================================================
        if(Opcao == 0){
             Caixa(24, 5, 15, 2, 1);
             Opcao1 = Menu(x1, y1, OpcoesCad, 2, z);
             if(Opcao1 == 0) AtivarCliente(z, arq_pessoa, "pessoas.txt");
             if(Opcao1 == 1) AtivarCliente(z, arq_empresa, "empresas.txt");
             
        }

        //                    VAGAS
        //=======================================================
        if(Opcao == 1) {
             Caixa(24, 5, 20, 2, 1);
             //Opcao1 = Menu();
             if(Opcao1 == 0){};
             if(Opcao1 == 1){};
        }

        //                    TEMAS
        //=======================================================
        if(Opcao == 2){
            Caixa(69, 5, 10, 9, 1);
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
    system("cls");


    //                   MENSAGEM FINAL
    //==================================================================
    Cores(z.letra, z.fundo);
    printf("\n\t\t\t  Unimontes - Montes Claros - Sistemas de Inform%c%co - Primeiro Per%codo  \n\t\t\t\t\t\t  Trabalho de AEDS 1  \n\t\t\t\t\t  Tema : Sistema de Ag%cncia de Empregos  \n\t\t\t\t\t\t  Professor : Heveraldo  \n\n\t\t\t\t\t  Alunos : Luis Fernando e Arthur  \n\t\t\t\t\t\t  Programa : LFA jobs v1.0  \n\n\t\t\t\t  Data de In%ccio : 25/06/2022    T%crmino : ?? / ?? / ????  \n\n", 135, 198, 161,136,161,130);
    Cores(z.fundo, z.letra);
    printf("\tN%cs, Fernando e Arthur, agradecemos a voc%c por utilizar nosso software , e pedimos que em caso de qualquer bug   entrem em contato com a gente.\n\n\t\t\t\t\t\tVolte sempre  :)\n\n\t\t\t\t", 162, 136);
    system("pause");
    
    //                 RETORNO AO PADRAO DO TERMINAL
    //==================================================================
    Cores(0,15);
    system("cls");
    return 0;
}
