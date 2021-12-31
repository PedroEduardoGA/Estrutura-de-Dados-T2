#include <stdio.h>
#include "saidasTxt.h"

void CriaArquivo(char arquivo[])
{
    FILE *arq;
    
    arq = fopen(arquivo, "w");
    if (arq == NULL){ 
        printf("Nao foi possivel Criar o Txt!");
        return;
    }
    fprintf(arq, "Pedro Eduardo Garbossa, Saida TXT:\n");
    
    fclose(arq);
}

void IdInexiste(char arquivo[],char IDE[],char TipoConsulta[])
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    
    fprintf(arq, "%s:\nRetangulo com ID:%s Nao Encontrado!\n",TipoConsulta,IDE);
    
    fclose(arq);
}

void RemoveuRetan(char arquivo[],char IDE[],char Tipo[])//Da funcao DR, reporta id dos retangulos removidos!
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
    if (arq == NULL)
    {
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    
    fprintf(arq, "%s:\nRetanguloID:%s removido!\n",Tipo,IDE);
    
    fclose(arq);
}

void SaidaIm(char arquivo[],char IDE[],char Consulta[],int Tipo)
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
    if (arq == NULL)
    {
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    if(Tipo==0)//se a pessoa ta com morte iminente eh passado 0 como tipo, se a pessoa morreu eh passado 1
        fprintf(arq, "\n%s:\nPessoa com ID:%s com morte iminente!",Consulta,IDE);
    else
        fprintf(arq, "\n%s:\nPessoa com ID:%s morreu instantaneamente!",Consulta,IDE);
    
    fclose(arq);
}

void SaidaNve(char arquivo[],double x,double y,double nivel)
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
    if (arq == NULL)
    {
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    fprintf(arq,"\nNivel de exposicao no ponto x: %lf y: %lf = %lf mSv",x,y,nivel);
    
    fclose(arq);
}

void FgRetan(char arquivo[],char Id[])
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
    if (arq == NULL)
    {
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    fprintf(arq,"\nEdficio ID: %s Contem:",Id);
    
    fclose(arq);
}

void FgCirculo(char arquivo[],char Id[])
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
    if (arq == NULL)
    {
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    fprintf(arq,"\no Id: %s Abrigado.",Id);
    
    fclose(arq);
}