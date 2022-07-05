#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "interface.h"


int fundo = BLACK;

void LinCol(int linha, int coluna){
    COORD c;
    c.X = linha; c.Y = coluna;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Caixa(int x, int y, int largura, int altura, int tipo){
    int i, j;
    unsigned char C[][6] = {{218, 196, 191, 179, 192, 217},
                            {201, 205, 187, 186, 200, 188}};
    LinCol(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][1]);
    printf("%c", C[tipo][2]);
    for(j = 0; j < altura; j++){
        LinCol(x, y + j + 1); printf("%c", C[tipo][3]);
        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][3]);
    }
    LinCol(x, y + j + 1); printf("%c", C[tipo][4]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][1]);
    printf("%c", C[tipo][5]);
}

void Cores(int letras, int fundo){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + (fundo << 4));
}

int MenuCor(int z){
    int cores[16] = {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
       LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
       LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE};

    return cores[z];
}

int Menu(int x[], int y[], char Opcoes[][20], int n, int cor){
    int i, Opcao = 0, tecla;
    TipoCursor(0);
    Cores(fundo, MenuCor(cor));
    for(i = 0; i < n; i++){
        LinCol(x[i], y[i]); printf("%s", Opcoes[i]);
    }
    do{
        Cores(MenuCor(cor), fundo);
        LinCol(x[Opcao], y[Opcao]); printf("%s", Opcoes[Opcao]);
        tecla = GetTecla();
        Cores(fundo, MenuCor(cor));
        LinCol(x[Opcao], y[Opcao]); printf("%s", Opcoes[Opcao]);
        if(tecla == TEC_ESQ) Opcao--;
        if(tecla == TEC_DIR) Opcao++;
        if(tecla == TEC_CIMA) Opcao--;
        if(tecla == TEC_BAIXO) Opcao++;
        if(tecla == TEC_ENTER){
                TipoCursor(1);
                return Opcao;
        }
        if(Opcao < 0) Opcao = n -1;
        if(Opcao >= n) Opcao = 0;
    }while(tecla != TEC_ESC);
    TipoCursor(1);
    return -1;
}

int GetTecla(){
    int ch;
    ch = getch();
    if(ch == 224){
        ch = getch() + 1000;
    }
    return ch;
}

void TipoCursor(int cursor){
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    BOOL result;
    CURSOR.dwSize = 1;
    if(cursor == 0)
        CURSOR.bVisible = FALSE;
    else
        CURSOR.bVisible = TRUE;
    result = SetConsoleCursorInfo(myconsole, &CURSOR);
}

void Inicio(int z){

    int cdf = MenuCor(z);

    Cores(fundo, cdf); Caixa(0, 0, 118, 28, 1);
    Cores(fundo, cdf); Caixa(3, 2, 112, 24, 1 );
    Cores(fundo, cdf); Caixa(24, 1, 68, 1, 0);
    Cores(fundo, cdf);
    LinCol(32, 2);
    Cores(cdf, fundo);
    printf("             Sistema Comercial Hevera's              ");
    Cores(fundo, cdf);

    Caixa(10, 8, 98, 8, 1); Cores(cdf, fundo); Caixa(12, 9, 94, 6, 0); Cores(cdf,fundo); Caixa(14, 11,90, 2,0);
    Cores(fundo, cdf); 
    Caixa(19, 5 , 79, 14, 1);
    Caixa(21, 6, 75, 12, 0);
    Cores(cdf/*YELLOW*/, fundo);
    LinCol(22, 7); printf("UUUUUUUUUUUUUUUUU   / 00           00000111    0       \\  UUUUUUUUUUUUUUUUU"); Cores(cdf/*LIGHT_RED*/, fundo);
    LinCol(22, 8); printf("     uuuuuuuuuu     | 001        000001000    111      |    uuuuuuuuuu     "); Cores(cdf/*RED*/, fundo);
    LinCol(22, 9); printf(" *    UUUUUUUUU     | 010        001         100 00    |    UUUUUUUUU    * "); Cores(cdf/*LIGHT_MAGENTA*/, fundo);
    LinCol(22,10); printf("~~  *   uuuuuuuu    | 011        000001010  100   01   |   uuuuuuuu   *  ~~"); Cores(cdf/*MAGENTA*/, fundo);
    LinCol(22,11); printf("~~~~  *     UUUUUU  | 100        011       0000010010  | UUUUUU     *  ~~~~"); Cores(cdf/*BLUE*/, fundo);
    LinCol(22,12); printf("~~~~~~~~~~ *   uuuuu| 000000101  100      100      011 |uuuuu  *  ~~~~~~~~~"); Cores(cdf/*LIGHT_BLUE*/, fundo);
    LinCol(22,13); printf("~~~~~~~~~~~~~~  *   u 0000000110 101     100        100u   *  ~~~~~~~~~~~~~"); Cores(cdf/*CYAN*/, fundo);
    LinCol(22,14); printf("~~~~~~~~~~~~~~~~~~~ |     jj   oooo   bbbbb   ssssss   | ~~~~~~~~~~~~~~~~~~"); Cores(cdf/*LIGHT_CYAN*/, fundo);
    LinCol(22,15); printf("------------------- |     jj ooo  ooo bb  bb sss       | ------------------"); Cores(cdf/*GREEN*/, fundo);
    LinCol(22,16); printf("------------------- |     jj oo    oo bbbbb    sssss   | ------------------"); Cores(cdf/*LIGHT_GREEN*/, fundo);
    LinCol(22,17); printf("------------------- | jj  jj ooo  ooo bb  bb      sss  | ------------------"); Cores(cdf/*YELLOW*/, fundo);
    LinCol(22,18); printf("--------------------\\  jjjj    oooo   bbbbb   ssssss   /-------------------"); Cores(cdf/*WHITE*/, fundo);
    Cores(fundo, cdf);
    LinCol(42,22); printf("---- TRABALHO AEDS 1o PERIODO ----");

    Cores(fundo, cdf);
    Caixa(24, 24, 68, 1, 0);
    Cores(cdf, fundo);
    LinCol(34, 25); printf("               Fernando Leal & Arthur              ");
    Cores(cdf, fundo);
    LinCol(90, 28); printf("     copyright 2022     ");
    
}

void Terminal(){
    system("mode con:cols=150 lines=50");   /* tamanho do console */
    int x,y;
    HWND cW = GetConsoleWindow();
    x = GetSystemMetrics(SM_CXSCREEN);   /* quantidade de pixel por linhas da tela   */
    y = GetSystemMetrics(SM_CYSCREEN);   /* quantidade de pixel por coluna da tela  */
    printf("Resolucao   %d   X    %d\n\n",x,y);
	SetWindowPos( cW, 0, x/40, y/15, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
	getch();
}
