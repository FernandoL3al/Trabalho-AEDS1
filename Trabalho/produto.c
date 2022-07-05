#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include "interface.h"

Produto Produtos[100];
int ContProdutos = 0;

void MostrarTelaProduto(){
    LinCol(10,  2); printf("============== Cadastro de Produtos ==============");
    LinCol(10,  6); printf("        Codigo: ");
    LinCol(10,  8); printf("     Descricao: ");
    LinCol(10, 10); printf("         Saldo: ");
    LinCol(10, 12); printf("Preco de Venda: ");
    LinCol(10, 18); printf("=================================================");
}
Produto DigitarProduto(){
    Produto P;
    LinCol(26,  6); scanf("%d", &P.Codigo);
    LinCol(26,  8); scanf(" %[^\n]", P.Descricao);
    LinCol(26, 10); scanf("%d", &P.Saldo);
    LinCol(26, 12); scanf("%lf", &P.PrecoVenda);
    return P;
}
void MostrarProduto(Produto P){
    LinCol(26,  6); printf("%d", P.Codigo);
    LinCol(26,  8); printf("%s", P.Descricao);
    LinCol(26, 10); printf("%d", P.Saldo);
    LinCol(26, 12); printf("%.2lf", P.PrecoVenda);
}
void LimparProduto(){
    LinCol(26,  6); printf("%*s", 10, " ");
    LinCol(26,  8); printf("%*s", 60, " ");
    LinCol(26, 10); printf("%*s", 20, " ");
    LinCol(26, 12); printf("%*s", 20, " ");
}
void ListarProdutos(Produto Produtos[], int Quantidade){
}
void PesquisarProduto(Produto Produtos[], int Quantidade){
}

void AtivarProduto(){
    int Opcao;
    do{
        system("cls");
        MostrarTelaProduto();
        LinCol(10, 19);
        printf("1- Novo, 2- Pesquisar, ");
        printf("3- Listar, 0- Sair :        ");
        LinCol(54, 19);
        scanf("%d", &Opcao);
        LimparProduto();
        if(Opcao == 1)
            Produtos[ContProdutos++] = DigitarProduto();
        if(Opcao == 2)
            PesquisarProduto(Produtos, ContProdutos);
        if(Opcao == 3)
            ListarProdutos(Produtos, ContProdutos);
    } while(Opcao != 0);
}
