#include <stdio.h>
// compila e inicia o programa
int main(){
    system("gcc main.c interface.c cadastro.c funcionario.c produto.c venda.c -o T.exe");
    printf("DIGITE 's' PARA INICIAR O PROGRAMA: ");
    if(getch() == 's') system("T.exe");
    return 0;
}