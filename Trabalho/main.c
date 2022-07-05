/*

gcc main.c interface.c cadastro.c funcionario.c produto.c venda.c -o T.exe

*/


#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "interface.h"
#include "funcionario.h"
#include "produto.h"
#include "venda.h"


int main()
{
    int Opcao, Opcao1, z = 3;
    //Terminal();

    // inserindo dados
    InserirCliente(100, "Joao", "234234", 2000);
    InserirCliente(101, "Jose", "56756", 2500);
    InserirCliente(102, "Maria", "3453", 1000);
    InserirCliente(103, "Barbara", "089956", 500);
    InserirCliente(104, "Luiza", "12223", 3000);

    InserirFuncionario(001, "Fernando", "Desenvolvedor");
    InserirFuncionario(002, "Arthur", "Desenvolvedor");
    
    do{
        system("cls");
        
        Inicio(z);
        int xcor[] = {70,70,70,70,70,70,70,70,70,70,70,70,70};
        int ycor[] = {6,7,8,9,10,11,12,13,14,15,16,17,18};
        char OpCores[][20] = {"Azul", "Verde", "Ciano", "Vermelho", "Roxo", "Amarelo",
       "Branco", "Cinza", "Azul Claro", "Vede Claro", "Ciano Claro",
       "Rosa", "Lilaz"};
        
        int x[] = {25, 40, 55, 70, 85};
        int y[] = {4, 4, 4, 4, 4};
        char Opcoes[][20] = {"Cadastros", "Rotinas", "Consultas", "Tema", "Sair"};

        int x1[] = {10, 10, 10, 10};
        int y1[] = {6, 7, 8, 9};
        char Opcoes1[][20] = {"Clientes", "Fornecedores", "Produtos", "Funcionarios"};

        int xRotinas[] = {25, 25};
        int yRotinas[] = {6, 7};
        char OpcoesFuncionarios[][20] = {"Listar Funcionarios"};

        int Of[] = {20};
        int Of1[] = {9}; 
        char OpcoesRotinas[][20] = {"Vendas", "Compras"};

        Opcao = Menu(x, y, Opcoes, 5, z);

        if(Opcao == 0){
             Caixa(9, 5, 20, 4, 1);
             Opcao1 = Menu(x1, y1, Opcoes1, 4, z);
             if(Opcao1 == 0) AtivarCliente(z);
             if(Opcao1 == 2) AtivarProduto();
             if(Opcao1 == 3){
                Menu(Of, Of1, OpcoesFuncionarios, 1, z);
                AtivarFuncionario();
             }
        }
        if(Opcao == 1) {
             Caixa(24, 5, 20, 2, 1);
             Opcao1 = Menu(xRotinas, yRotinas, OpcoesRotinas, 2, z);
             if(Opcao1 == 0); AtivarVenda(z);
             if(Opcao1 == 1); AtivarProduto();
        }
        if(Opcao == 3){
            Caixa(69, 5, 15, 13, 1);
            Opcao1 = Menu(xcor, ycor, OpCores, 13, z);
            z = MenuCor(Opcao1+1);
        }
    } while (Opcao != 4);
    system("cls");
    return 0;
}