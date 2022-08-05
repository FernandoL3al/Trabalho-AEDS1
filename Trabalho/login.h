#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED


//                      TIPO STRUCT LOGIN
//===============================================================
typedef struct{
    char nome[51];
    char senha[31];
}Login;


//                        FUNCOES LOGIN
//===============================================================
Login GetLogin(char vetor[]);

void Autenticacao();


//                     UTILIDADES
//================================================================
//void Obliterator(char *end_arquivo, char *pattern);

#endif // LOGIN_H_INCLUDED