#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "Dinamica.h"
#include "svg.h"
#include "saidasTxt.h"
#include "ArvoreKD.h"

char *Tratamento(char arq[])
{
    char *auxiliar = strrchr(arq,'/');//procura pela primeira ocorrencia da / e retorna a string posterior a /
    if (auxiliar == NULL) // se eh nulo nao foi encontrada nenhuma /
    {
        return strtok(arq,".");//se encontro retorna a string posterior a / formatada, ou seja sem a extensao
    }
    return strtok(&auxiliar[1],".");//caso nao tenha /, retornara a string atenrior ao "."
}

int main(int argc, char* argv[])
{
    char* diretorioEntrada=NULL;
    char* geo=NULL;
    char* qry=NULL;
    char* diretorioSaida=NULL;
    char* SvgConsulta=NULL;
    char* TXT=NULL;
    int Consulta=0;
    int nx=0;

    int i=1;
    while(i < argc)
    {
        if(strcmp("-e",argv[i])==0)//se as string são iguais retorna 0, depois do -e vem o path caso exista
        {
            i++;
            diretorioEntrada= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(diretorioEntrada, "%s", argv[i]); //Sprintf copia o valor de argv para diretorioEntrada
    
        }else if(strcmp("-f", argv[i]) == 0)
            {
                ++i; //A proxima string vai ser o nome do arquivo .geo:
                geo= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
                sprintf(geo, "%s", argv[i]);//Copia o nome do arq .geo pra geo

            }else if(strcmp("-q", argv[i]) == 0)
                {
                    ++i;  //A proxima string vai ser o nome do arquivo .qry:
                    Consulta=1;//Indica que vai haver consultas
                    qry= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
                    sprintf(qry, "%s", argv[i]);//Copia o nome do arq qry para variavel qry


                }else if(strcmp("-o", argv[i]) == 0)
                    {
                        ++i;  //A proxima string vai ser o nome do diretorio de arquivos de saida:
                        diretorioSaida= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
                        sprintf(diretorioSaida, "%s", argv[i]);//copia pra diretorio saida o diretorio de saida

                    }

        i++;
    }
    Lista ListaDinamica= Create();
    ArvoreKD arvore1= CreateTreeKD();//arvore pros retangulos
    ArvoreKD arvore2= CreateTreeKD();//arvore pros circulos

    if(diretorioSaida==NULL)//caso nao seja informado diretorio de saida programa eh encerrado
    {
        printf("\nErro! Diretorio de saida nao foi informado!");
        return 0;
    }

    if(geo==NULL)//caso nao seja informado um arquivo geo programa eh encerrado
    {
        printf("\nErro! Arquivo .geo nao foi informado!");
        return 0;
    }

    LeituraGeo(arvore1,arvore2,diretorioEntrada,geo,diretorioSaida,&nx);
    if(Consulta==1)
    {
        char* QRYSemExtensao=NULL;
        char* aux=NULL;//Variavel temporaria pra ser passado pro nome do arquivo txt o nome de qry sem a extensao .qry
        aux= (char *) malloc((strlen(qry)+1)*sizeof(char));
        
        strcpy(aux,qry);//copiado pra variavel aux o nome passado apos o -q
        QRYSemExtensao= Tratamento(aux);//qry sem extensao recebera so o nome do qry
    
        TXT= (char *) malloc((strlen(QRYSemExtensao)+strlen(geo)+strlen(diretorioSaida)+7) * sizeof(char));
        sprintf(TXT, "%s/%s-%s.txt",diretorioSaida,geo,QRYSemExtensao);//Concantena nome do arquivo txt de saida
        
        SvgConsulta= (char *) malloc((strlen(QRYSemExtensao)+strlen(geo)+strlen(diretorioSaida)+7) * sizeof(char));//7 pra caber o / e o .svg/0
        sprintf(SvgConsulta, "%s/%s-%s.svg",diretorioSaida,geo,QRYSemExtensao);//Concantena nome do arquivo svg de saida

        CriaArquivo(TXT);
        iniciaSvg(SvgConsulta);//vai iniciar o svg final com as consultas

        LeituraQry(arvore1,arvore2,ListaDinamica,diretorioEntrada,qry,diretorioSaida,TXT,SvgConsulta);
        free(aux);//free da variavel temporaria

        finalizaSvg(SvgConsulta);//finaliza o svg final
        free(qry);
        free(TXT);
        free(SvgConsulta);
    }//free das variaveis!
    NohKD node;

    node=GetFirstKD(arvore1);
    LiberaKD(node);
    free(arvore1);

    node=GetFirstKD(arvore2);
    LiberaKD(node);
    free(arvore2);
    printf("\nArvoresKD Liberadas!");

    free(geo);
    free(diretorioEntrada);
    free(diretorioSaida);
    liberalist(ListaDinamica);
    printf("\nMemoria Liberada e Programa Finalizado!");
    return 0;
}