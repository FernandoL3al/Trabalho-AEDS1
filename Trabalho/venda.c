#include <stdio.h>
#include <stdlib.h>
#include "venda.h"
#include "cadastro.h"
#include "interface.h"

Venda Vendas[100];
int ContVendas = 0;

void MostrarTelaVenda(){
    Caixa(10, 7, 50, 11, 1);
    LinCol(12,  9); printf("    Numero: ");
    LinCol(35,  9); printf("Data Venda: ");
    LinCol(12, 11); printf("   Cliente: ");
    LinCol(12, 13); printf("   Produto: ");
    LinCol(12, 15); printf("    Quant.: ");
    LinCol(35, 15); printf("     Preco: ");
}
Venda DigitarVenda(int z){
    Venda V;
    int x[] = {25, 25, 25, 25, 25};
    int y[] = {12, 13, 14, 15, 16};
    char Opcoes[100][20];
    int n, Opcao;
    LinCol(24,  9); scanf("%d", &V.Numero);
    LinCol(47,  9); scanf(" %[^\n]", V.DataVenda);
    //gotoxy(24, 11); scanf("%d", &V.CodCliente);
    n = CarregarClientes(Opcoes);
    Caixa(24, 11, 20, 5, 0);
    Opcao = Menu(x, y, Opcoes, n, z);
    V.CodCliente = Opcao;
    MostrarTelaVenda();
    MostrarVenda(V);
    LinCol(24, 13); scanf("%d", &V.CodProduto);
    LinCol(24, 15); scanf("%d", &V.Quantidade);
    LinCol(47, 15); scanf("%lf", &V.PrecoUnitario);
    return V;
}
void MostrarVenda(Venda V){
    LinCol(24,  9); printf("%d", V.Numero);
    LinCol(47,  9); printf("%s", V.DataVenda);
    LinCol(24, 11); printf("%d", V.CodCliente);
    LinCol(24, 13); printf("%d", V.CodProduto);
    LinCol(24, 15); printf("%d", V.Quantidade);
    LinCol(47, 15); printf("%.2lf", V.PrecoUnitario);
}
void LimparVenda(){
    LinCol(24,  9); printf("%*s", 10, " ");
    LinCol(47,  9); printf("%*s", 10, " ");
    LinCol(24, 11); printf("%*s", 10, " ");
    LinCol(24, 13); printf("%*s", 10, " ");
    LinCol(24, 15); printf("%*s", 10, " ");
    LinCol(47, 15); printf("%*s", 10, " ");
}
void ListarVendas(Venda PVendas[], int Quantidade){
}
void PesquisarVenda(Venda Vendas[], int Quantidade){
}

void AtivarVenda(int z){
    int Opcao;
    do{
        //system("cls");
        MostrarTelaVenda();
        int x[] = {17, 25, 38, 48};
        int y[] = {18, 18, 18, 18};
        char Opcoes[][20] = {"Novo", "Pesquisar", "Listar", "Sair"};
        Opcao = Menu(x, y, Opcoes, 4, z);
        LimparVenda();
        if(Opcao == 0)
            Vendas[ContVendas++] = DigitarVenda(z);
        if(Opcao == 1)
            PesquisarVenda(Vendas, ContVendas);
        if(Opcao == 2)
            ListarVendas(Vendas, ContVendas);
    } while(Opcao != 3);
}
