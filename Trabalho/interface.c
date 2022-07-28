#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "interface.h"


void Gotoxy(int linha, int coluna){
    COORD c;
    c.X = linha; c.Y = coluna;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Caixa(int x, int y, int largura, int altura, int tipo){
    int i, j;
    unsigned char C[][6] = {{218, 196, 191, 179, 192, 217},
                            {201, 205, 187, 186, 200, 188}};
    Gotoxy(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][1]);
    printf("%c", C[tipo][2]);
    for(j = 0; j < altura; j++){
        Gotoxy(x, y + j + 1); printf("%c", C[tipo][3]);
        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][3]);
    }
    Gotoxy(x, y + j + 1); printf("%c", C[tipo][4]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][1]);
    printf("%c", C[tipo][5]);
}

void Cores(int fundo, int letras){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + (fundo << 4));
}


int Menu(int x[], int y[], char Opcoes[][20], int n, Tema t){
    int i, Opcao = 0, tecla;
    TipoCursor(0);
    Cores(t.fundo, t.letra);
    for(i = 0; i < n; i++){
        Gotoxy(x[i], y[i]); printf("%s", Opcoes[i]);
    }
    do{
        Cores(t.letra, t.fundo);
        Gotoxy(x[Opcao], y[Opcao]); printf("%s", Opcoes[Opcao]);
        tecla = GetTecla();
        Cores(t.fundo, t.letra);
        Gotoxy(x[Opcao], y[Opcao]); printf("%s", Opcoes[Opcao]);
        if(tecla == TEC_ESQ) Opcao--;
        if(tecla == TEC_DIR) Opcao++;
        if(tecla == TEC_CIMA) Opcao--;
        if(tecla == TEC_BAIXO) Opcao++;

        if(n == 9 && tecla == TEC_EASTER_G) return 9; // my secret button
        
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


 int EseG(Tema t){ //Easter Egg
        char code; int i, j;
        Caixa(19, 5 , 79, 14, 1);
        Cores(15, 0);
        for(i = 6; i < 20; i++){
            for(j = 20; j < 98; j++ ){
                Gotoxy(j, i); printf("?");
            }
        }
        Caixa(57, 11, 2, 1, 1); Gotoxy(58, 12); scanf("%c", &code);
        if(code == 'B') return 9;
        else if(code == 'L')  return 10;
        else {
            Cores(0, 15);
            Caixa(19, 5 , 79, 14, 1);
            Caixa(44, 11, 27, 1, 1);
            Gotoxy(45, 12); printf("Nada de Easter Egg pra voc%c", 136);
            Gotoxy(34, 28); system("pause");
            return 2;
        }
}

/* funcao com defeito ainda
char En_DecriptarSTR(char string[101], int opcao){ //Encriptar/Decriptar String
    int i;
    char cripted[101];
    if(opcao == 1){
        for(i = 0; i < strlen(string); i++){
            cripted[i] = string[i] + 3;
        }

    }
    if(opcao == 2){
        for(i = 0; i < strlen(string); i++){
            cripted[i] = string[i] - 3;
        }
    }
    return cripted;
}

*/







































































void Inicio(Tema t, int num){

    int cdf = t.letra;
    int fundo = t.fundo;

    Cores(fundo, cdf); Caixa(0, 0, 118, 28, 1);
    Cores(fundo, cdf); Caixa(3, 2, 112, 24, 1 );
    Cores(fundo, cdf); Caixa(24, 1, 68, 1, 0);
    Cores(fundo, cdf);
    Gotoxy(32, 2);
    Cores(cdf, fundo);
    printf("                       LFA jobs                      ");
    Cores(fundo, cdf);

    Caixa(10, 8, 98, 8, 1); Cores(cdf, fundo); Caixa(12, 9, 94, 6, 0); Cores(cdf,fundo); Caixa(14, 11,90, 2,0);
    Cores(fundo, cdf); 
    Caixa(19, 5 , 79, 14, 1);
    Caixa(21, 6, 75, 12, 0);
    Cores(cdf/*YELLOW*/, fundo);

    if(num == 0){
        Gotoxy(22, 7); printf("UUUUUUUUUUUUUUUUU   / 00           00000111    0       \\  UUUUUUUUUUUUUUUUU"); Cores(cdf/*LIGHT_RED*/, fundo);
        Gotoxy(22, 8); printf("     uuuuuuuuuu     | 001        000001000    111      |    uuuuuuuuuu     "); Cores(cdf/*RED*/, fundo);
        Gotoxy(22, 9); printf(" *    UUUUUUUUU     | 010        001         100 00    |    UUUUUUUUU    * "); Cores(cdf/*LIGHT_MAGENTA*/, fundo);
        Gotoxy(22,10); printf("~~  *   uuuuuuuu    | 011        000001010  100   01   |   uuuuuuuu   *  ~~"); Cores(cdf/*MAGENTA*/, fundo);
        Gotoxy(22,11); printf("~~~~  *     UUUUUU  | 100        011       0000010010  | UUUUUU     *  ~~~~"); Cores(cdf/*BLUE*/, fundo);
        Gotoxy(22,12); printf("~~~~~~~~~~ *   uuuuu| 000000101  100      100      011 |uuuuu  *  ~~~~~~~~~"); Cores(cdf/*LIGHT_BLUE*/, fundo);
        Gotoxy(22,13); printf("~~~~~~~~~~~~~~  *   u 0000000110 101     100        100u   *  ~~~~~~~~~~~~~"); Cores(cdf/*CYAN*/, fundo);
        Gotoxy(22,14); printf("~~~~~~~~~~~~~~~~~~~ |     jj   oooo   bbbbb   ssssss   | ~~~~~~~~~~~~~~~~~~"); Cores(cdf/*LIGHT_CYAN*/, fundo);
        Gotoxy(22,15); printf("------------------- |     jj ooo  ooo bb  bb sss       | ------------------"); Cores(cdf/*GREEN*/, fundo);
        Gotoxy(22,16); printf("------------------- |     jj oo    oo bbbbb    sssss   | ------------------"); Cores(cdf/*LIGHT_GREEN*/, fundo);
        Gotoxy(22,17); printf("------------------- | jj  jj ooo  ooo bb  bb      sss  | ------------------"); Cores(cdf/*YELLOW*/, fundo);
        Gotoxy(22,18); printf("--------------------\\  jjjj    oooo   bbbbb   ssssss   /-------------------"); Cores(cdf/*WHITE*/, fundo);
    }
    if(num == 1){
        Gotoxy(22, 7); printf("                              2222222222222222                             "); Cores(cdf/*LIGHT_RED*/, fundo);
        Gotoxy(22, 8); printf("                        222222                222222                       "); Cores(cdf/*RED*/, fundo);
        Gotoxy(22, 9); printf("                   2222222                       2222222                   "); Cores(cdf/*LIGHT_MAGENTA*/, fundo);
        Gotoxy(22,10); printf("               222222222                           222222222               "); Cores(cdf/*MAGENTA*/, fundo);
        Gotoxy(22,11); printf("          222222222222     22222222222222222222      222222222222          "); Cores(cdf/*BLUE*/, fundo);
        Gotoxy(22,12); printf("      2222222222222222222222222222222222222222222222 2222222222222222      "); Cores(cdf/*LIGHT_BLUE*/, fundo);
        Gotoxy(22,13); printf("   22222222222222222222222222               2222222222222222222222222222   "); Cores(cdf/*CYAN*/, fundo);
        Gotoxy(22,14); printf("      222222222222222                                2222222222222222      "); Cores(cdf/*LIGHT_CYAN*/, fundo);
        Gotoxy(22,15); printf("          2222222222222                              2222222222222         "); Cores(cdf/*GREEN*/, fundo);
        Gotoxy(22,16); printf("                 22222222                          222222222222            "); Cores(cdf/*LIGHT_GREEN*/, fundo);
        Gotoxy(22,17); printf("                        22222                   2222222                    "); Cores(cdf/*YELLOW*/, fundo);
        Gotoxy(22,18); printf("                             2222222222222222222                           "); Cores(cdf/*WHITE*/, fundo);

        Gotoxy(4, 28); printf("     Meus parab%cns , voc%c encontrou nosso easter egg!!! ...     ", 130, 136);
    }
    if(num == 2){
        Gotoxy(22, 7); printf("                                    131313                                 "); Cores(cdf/*LIGHT_RED*/, fundo);
        Gotoxy(22, 8); printf("                                   13131313                                "); Cores(cdf/*RED*/, fundo);
        Gotoxy(22, 9); printf("                                  3131313131                               "); Cores(cdf/*LIGHT_MAGENTA*/, fundo);
        Gotoxy(22,10); printf("             13131313131313131313131313131313131313131313131313            "); Cores(cdf/*MAGENTA*/, fundo);
        Gotoxy(22,11); printf("                  1313131313         313          1313131313               "); Cores(cdf/*BLUE*/, fundo);
        Gotoxy(22,12); printf("                      131313 31313131 1313131 1313131313                   "); Cores(cdf/*LIGHT_BLUE*/, fundo);
        Gotoxy(22,13); printf("                          13 31313131 1313131 131313                       "); Cores(cdf/*CYAN*/, fundo);
        Gotoxy(22,14); printf("                          13        131313131 131313                       "); Cores(cdf/*LIGHT_CYAN*/, fundo);
        Gotoxy(22,15); printf("                        1313 3131313131313131 13131313                     "); Cores(cdf/*GREEN*/, fundo);
        Gotoxy(22,16); printf("                      313131 1313131313131333 3131313131                   "); Cores(cdf/*LIGHT_GREEN*/, fundo);
        Gotoxy(22,17); printf("                    131313131313              131313131313                 "); Cores(cdf/*YELLOW*/, fundo);
        Gotoxy(22,18); printf("                  13131313                         131313131               "); Cores(cdf/*WHITE*/, fundo);
    
        Gotoxy(4, 28); printf("     Meus parab%cns , voc%c encontrou nosso easter egg!!! ...     ", 130, 136);
    }
    Cores(fundo, cdf);
    Gotoxy(42,22); printf("---- TRABALHO AEDS 1%c PER%cODO ----", 248, 214);

    Cores(fundo, cdf);
    Caixa(24, 24, 68, 1, 0);
    Cores(cdf, fundo);
    Gotoxy(34, 25); printf("               Fernando Leal & Arthur              ");
    Cores(cdf, fundo);
    Gotoxy(90, 28); printf("   copyright %c LFA 2022   ", 184);
    
}












