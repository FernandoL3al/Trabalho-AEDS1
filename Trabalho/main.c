/*
Compilaçao manual:
gcc main.c interface.c cadastro.c funcionario.c produto.c venda.c -o T.exe

Unimontes - Montes Claros - Sistemas de Informação - Primeiro Período
Trabalho de AEDS 1
Tema : Sistema de Agência de Empregos
Professor : Heveraldo

Alunos : Luis Fernando e Arthur
Programa : LFA jobs v1.0

Data de Início : 25/06/2022    Término : ??/??/????


*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"
#include "interface.h"


FILE *arq_tema;

int main()
{   
    //Leitura do arquivo de temas;
    
    Tema Temas[11];
    arq_tema = fopen("temas.txt", "rb");
    ///*
    if(arq_tema == NULL) {                          //backup temas.txt
        arq_tema = fopen("temas.txt", "wb"); 
        Tema Temas1[] = {{ .nome = "Night Mode", .letra = 8, .fundo = 0},
                    { .nome = "Bulbasaur", .letra = 0 , .fundo = 2},
                    { .nome = "Squirtle", .letra = 0 , .fundo = 3},
                    { .nome = "Charmander", .letra = 0 , .fundo = 4},
                    { .nome = "Ekans", .letra = 0 , .fundo = 5},
                    { .nome = "Pikachu", .letra = 0 , .fundo = 6},
                    { .nome = "Lapras", .letra = 0 , .fundo = 11},
                    { .nome = "Chansey", .letra = 0 , .fundo = 12},
                    { .nome = "Matrix", .letra = 10 , .fundo = 0},
                    { .nome = "Bozo", .letra = 6, .fundo = 2},
                    { .nome = "Molusco", .letra = 15, .fundo = 4}};
        fwrite(Temas1, 11*sizeof(Tema),1,arq_tema);
        fclose(arq_tema);
        exit(1);
    }
    //*/
    for(int b = 0 ; b < 11; b++){
        fread(&Temas[b], sizeof(Tema), 1, arq_tema);
    }
    fclose(arq_tema);

    //Menus
    int Opcao, Opcao1;
    //Default Tema
    Tema z = Temas[2];



    // inserindo dados
    InserirCliente(100, "Joao", "234234-245");
    InserirCliente(101, "Jose", "56756-43950");
    InserirCliente(13, "Lulosvaldo", "131313-1313");
    InserirCliente(102, "Maria", "3453-3585");
    InserirCliente(103, "Barbara", "0899-4456");
    InserirCliente(22, "Jao Bozonaro", "222222-222");
    InserirCliente(104, "Luiza", "12223-34985");

    InserirEmpresa(002, "Yourbank", "1414989375");
    InserirEmpresa(023, "Microloft", "1374-75701");
    InserirEmpresa(013, "Akazon", "153764-356");
    InserirEmpresa(233, "Kabaum", "53056-9436");
    InserirEmpresa(453, "Groogue", "1958-544");

    do{
        system("cls");

        //Inicio tela principal
        if(strcmp(z.nome, Temas[9].nome) == 0) Inicio(z, 1);
        else if(strcmp(z.nome, Temas[10].nome) == 0) Inicio(z, 2);
        else Inicio(z, 0);

        // Menu Principal
        int x[] = {34, 49, 64, 79};
        int y[] = {4, 4, 4, 4};
        char Opcoes[][20] = {"Cliente", "Vagas", "Temas", "Sair"};

        //Menu Cliente
        int x1[] = {25, 25};
        int y1[] = {6, 7};
        char OpcoesCad[][20] = {"Pessoa", "Empresa"};

        int x2[] = {};
        int y2[] = {};

        int Of[] = {20, 20};
        int Of1[] = {9, 10};
        char OpcoesRotinas[][20] = {"Vendas", ""};

        //Menu Temas
        int xcor[] = {70,70,70,70,70,70,70,70,70};
        int ycor[] = {6,7,8,9,10,11,12,13,14};
        char OpCores[][20] = {"Night Mode","Bulbasaur", "Squirtle",
                              "Charmander", "Ekans", "Pikachu",
                               "Lapras", "Chansey", "Matrix"};


        Opcao = Menu(x, y, Opcoes, 4, z);

        // Cadastro
        if(Opcao == 0){
             Caixa(24, 5, 15, 2, 1);
             Opcao1 = Menu(x1, y1, OpcoesCad, 2, z);
             if(Opcao1 == 0) AtivarCliente(z);
             if(Opcao1 == 1) AtivarCliente2(z);
        }

        // Vagas
        if(Opcao == 1) {
             Caixa(24, 5, 20, 2, 1);
             //Opcao1 = Menu();
             if(Opcao1 == 0);
             if(Opcao1 == 1);
        }

        // Temas
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
    system("cls");
    
    // Mensagem de final de programa
    Cores(z.letra, z.fundo);
    printf("\n\t\t\t  Unimontes - Montes Claros - Sistemas de Inform%c%co - Primeiro Per%codo  \n\t\t\t\t\t\t  Trabalho de AEDS 1  \n\t\t\t\t\t  Tema : Sistema de Ag%cncia de Empregos  \n\t\t\t\t\t\t  Professor : Heveraldo  \n\n\t\t\t\t\t  Alunos : Luis Fernando e Arthur  \n\t\t\t\t\t\t  Programa : LFA jobs v1.0  \n\n\t\t\t\t  Data de In%ccio : 25/06/2022    T%crmino : ?? / ?? / ????  \n\n", 135, 198, 161,136,161,130);
    Cores(z.fundo, z.letra);
    printf("\tN%cs, Fernando e Arthur, agradecemos a voc%c por utilizar nosso software , e pedimos que em caso de qualquer bug   entrem em contato com a gente.\n\n\t\t\t\t\t\tVolte sempre  :)\n\n\t\t\t\t", 162, 136);
    system("pause");
    
    //Retorno as cores padroes do terminal;
    Cores(0,15);
    system("cls");
    return 0;
}
