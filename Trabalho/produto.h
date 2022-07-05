#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

typedef struct {
    int Codigo;
    char Descricao[51];
    int Saldo;
    double PrecoVenda;
} Produto;

void MostrarTelaProduto();   //  Protótipo ou assinatura função
Produto DigitarProduto();
void MostrarProduto(Produto P);
void LimparProduto();
void ListarProdutos(Produto Produtos[], int Quantidade);
void PesquisarProduto(Produto Produtos[], int Quantidade);
void AtivarProduto();

#endif // PRODUTO_H_INCLUDED
