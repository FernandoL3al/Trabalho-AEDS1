#include <stdio.h>

//                   COMPILA E INICIA O PROGRAMA
//=======================================================================
int main(){
    system("gcc main.c interface.c cadastro.c vagas.c login.c -o T.exe");
    printf("PRESSIONE 'ENTER' PARA INICIAR O PROGRAMA: ");
    if(getch() == 13) system("T.exe");
    return 0;
}