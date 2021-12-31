#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dinamica.h"
#include "saidasTxt.h"
#include "svg.h"

typedef struct N{ //Onde guarda infos como, cor borda, preenchimento...
    char IdRect[70];
    char CorPrenche[30];
    char CorBord[30];
    double PontoX;
    double PontoY;
    double Largura;
    double Altura;

    struct N *ant;
    struct N *prox;
}no;

typedef struct L{
    no *primeiro; //primeiro elemento da list
    no *ultimo;   //ultimo elemento da list
}list;

Lista Create()//Aloca uma list
{
    list* lista = (list*) malloc(sizeof(list));//alloca, cria variavel e faz cast de list* lista
    //lista do tipo [primeiro][ultimo] 
    lista->primeiro= NULL;
    lista->ultimo= NULL;

    return lista;//retorna uma lista sem no interno
}

void insert(Lista l, char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura)//info é o que passa pra inserir na lista e l eh uma lista!
{
    no* node = (no*) malloc(sizeof(no));//faz cast de node com no e eh alocado struct do tipo no-node tem [*ant][informacao][*prox]
    list* lista = (list*) l;//cast de list com l, cria variavel lista do tipo [primeiro][ultimo]

    strcpy(node->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
    strcpy(node->CorPrenche,Prenche);
    strcpy(node->CorBord,Borda);
  
    node->PontoX= PontoX;
    node->PontoY= PontoY;
    node->Largura= Largura;
    node->Altura= Altura;

    if(lista->primeiro==NULL)//Verifica se ja existe um no da lista, se for null vai ser criado o primeiro no
    {
        node->ant=NULL;//o campo [ant] do primeiro no recebe NULL pois eh o primeiro no da lista
        
        lista->primeiro=node;
        //lista eh do tipo [primeiro][ultimo] que apontam para o primeiro no e o ultimo no da lista
        
    }else//se ja existe um no
        {
            lista->ultimo->prox= node;//vai armazenar no campo [prox] do ultimo no o endereco para o no atual
            node->ant =lista->ultimo;//vai armazenar no campo[ant]do no atual o endereco para o no anterior
        }
    node->prox=NULL;//vai armazenar no campo [proximo]do no atual o NULL
    lista->ultimo=node;//o [ultimo] de lista recebe o endereco do no atual criado
}

void print(Lista l)
{
    list* lista = (list*) l;//Cast da variavel lista com list*
    no* node= lista->primeiro;//struct node recebe endereco para o primeiro no da lista
    
    int i=0;
    while(node!=NULL)//enquanto nao chega no ultimo no vai imprimindo
    {
        printf("\n[%d] ID: %s",i,node->IdRect);
        printf("PontoX= %lf, PontoY= %lf, Larg= %lf, Alt= %lf",node->PontoX,node->PontoY,node->Largura,node->Altura);
        printf("CorPrenchi-> %s e CorBorda-> %s",node->CorPrenche,node->CorBord);
        node= node->prox;//percorre todos os nos da lista
        i++;
    }
}

void RemoveElemento(Lista l, char id[])
{
    list *lista = (list *) l;//faz cast de l com a struct de list e nomeia l de lista
    no *node = lista->primeiro;//criado um node do tipo no, que aponta pro primeiro elemento da lista
    no *aux;

    while((strcmp(node->IdRect,id)!=0)&&(node!=NULL))//Quando encontrar o elemento vai parar no noh em que o elemento se encontra
    {
        if(node->ant!=NULL)
            aux=node;//aux recebe noh anterior

        node = node->prox;// atribui a node o proximo noh
    }

    if(strcmp(node->IdRect,id)!=0)//id nao existe na lista
        return;

    if(lista->primeiro == node)//elemento eh o primeiro da lista eh o primeiro noh da lista tratamento diferente
    {
        
        if(node->prox == NULL)//indica que esse eh o unico noh da lista
        {
            lista->primeiro=NULL;
            lista->ultimo=NULL;
        
            free(node);
            return;
        }
        aux=node->prox;//aux eh o segundo elemento da lista
        aux->ant=NULL;
        lista->primeiro=aux;//Primeiro elemento da lista vai apontar para o proximo
    
        free(node);
        return;
    }

    if(lista->ultimo == node)//elemento eh o ultimo da lista
    {
        //eh o primeiro noh da lista tratamento diferente
        aux=node->ant;//aux eh o noh anterior
        aux->prox=NULL;
        lista->ultimo=aux;//Ultimo elemento da lista vai apontar para o anterior
        
        free(node);
        return;
    }

    if(strcmp(node->IdRect,id)==0)
    {
        aux->prox=node->prox;//Campo proximo do noh anterior vai receber o proximo noh do atual
        node->prox->ant=aux;//Campo anterior do proximo noh vai receber o noh aux
        free(node);
        return;
    }
    return;
}

void liberalist(Lista l)
{
    list *lista = (list *) l;//faz cast de l com a struct de list
    no *node = lista->primeiro;//criado um node do tipo no, que aponta pro primeiro elemento da lista
    no *aux;//criado um aux do tipo no

    while(node != NULL)
    {
        aux = node;//atribui a aux o valor de node atual
        node = node->prox;// atribui a node o proximo noh

        free(aux);//free no noh atual de aux
    }
    free(node);
    free(lista);//libera a malloc da lista
}

void InsereAfter(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i)
{
    list *lista = (list *) L;//faz cast de l com a struct de list e nomeia l de lista
    no *node=lista->primeiro;
    int x=0;

    if(i<0)
    {
        printf("\nPosicao inexistente!");
        return;
    }

    while ((x<i)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }

    no* aux= (no*) malloc(sizeof(no));
    strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
    strcpy(aux->CorPrenche,Prenche);
    strcpy(aux->CorBord,Borda);

    aux->PontoX= PontoX;
    aux->PontoY= PontoY;
    aux->Largura= Largura;
    aux->Altura= Altura;//aux eh o novo q sera inserido
    aux->prox=node->prox;//prox de aux recebe o endereco do proximo do noh
    node->prox=aux;
    aux->ant=node;
    if(node == lista->ultimo)//se i for a ultima posicao da lista
        lista->ultimo=aux;

}

void InsereBefore(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i)
{
    list *lista = (list *) L;//faz cast de l com a struct de list e nomeia l de lista
    no *node=lista->primeiro;
    int x=0;

    if(i<0)
    {
        printf("\nPosicao inexistente!");
        return;
    }
    while ((x<i)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }

    if(node==lista->primeiro)//caso queira inserir antes do primeiro elemento
    {
        no* aux= (no*) malloc(sizeof(no));
        strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
        strcpy(aux->CorPrenche,Prenche);
        strcpy(aux->CorBord,Borda);

        aux->PontoX= PontoX;
        aux->PontoY= PontoY;
        aux->Largura= Largura;
        aux->Altura= Altura;//aux eh o novo q sera inserido
        aux->ant=node->ant;
        node->ant=aux;
        aux->prox=node;
        lista->primeiro=aux;
        
        return;
    }

    if(node==lista->ultimo)//caso queira inserir antes do primeiro elemento
    {
        no* aux= (no*) malloc(sizeof(no));
        strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
        strcpy(aux->CorPrenche,Prenche);
        strcpy(aux->CorBord,Borda);

        aux->PontoX= PontoX;
        aux->PontoY= PontoY;
        aux->Largura= Largura;
        aux->Altura= Altura;//aux eh o novo q sera inserido
        aux->prox=node;//prox de aux recebe o endereco do noh atual
        aux->ant=node->ant;
        node->ant->prox=aux;
        node->ant=aux;
        
        return;
    }    
    no* aux= (no*) malloc(sizeof(no));
    strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
    strcpy(aux->CorPrenche,Prenche);
    strcpy(aux->CorBord,Borda);

    aux->PontoX= PontoX;
    aux->PontoY= PontoY;
    aux->Largura= Largura;
    aux->Altura= Altura;//aux eh o novo q sera inserido
    //Trocas
    aux->prox=node;//prox de aux recebe o endereco do noh atual
    aux->ant=node->ant;
    node->ant->prox=aux;
    node->ant=aux;
}

No GetLast(Lista L)
{
    list *lista = (list *) L;

    return lista->ultimo;
}

No GetFirst(Lista L)
{
    list *lista = (list *) L;

    return lista->primeiro;
}

No GetNext(Lista L,int pos)
{
    list *lista = (list *) L;
    no* node= lista->primeiro;

    int x=0;
    if(lista->primeiro==NULL)
        return NULL;

    while((x<pos)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }
    return node->prox;
}

No GetPrevious(Lista L, int pos)
{
    list *lista = (list *) L;
    no* node= lista->primeiro;
    if(node==NULL)//lista vazia
        return NULL;

    int x=0;
    while((x<pos)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }
    return node->ant;
}

No GetElemento(Lista L,char IdRect[70])//Util
{
    list *lista = (list *) L;
    no* node= lista->primeiro;

    if(node==NULL)//lista vazia
        return NULL;

    while((strcmp(node->IdRect,IdRect)!=0)&&(node!=NULL))
        node=node->prox;
    
    if(strcmp(node->IdRect,IdRect)!=0)
        return NULL;

    return node;
}

void Qsort(Lista L)
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    no *node2=NULL;
    double aux;

    if(node==NULL)
        return;

    while (node->prox!=NULL)
    {
        node2=node->prox;
        while (node2->prox!=NULL)
        {
            if(node->PontoX < node2->PontoX)
            {
                aux=node->PontoY;
                node->PontoY=node2->PontoY;
                node2->PontoY=aux;

                aux=node->PontoY;
                node->PontoY=node2->PontoY;
                node2->PontoY=aux;

                aux=node->Largura;
                node->Largura=node2->Largura;
                node2->Largura=aux;
            }
            node2=node2->prox;
        }
        node=node->prox;
    }
}

//============FuncoesDeConsulta============
void SvgQry(Lista L, char nomeSvG[])//Funcao que gera o svg final, pos consultas!
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    while(node!=NULL)
    {
        CriaPontinho(node->PontoX,node->PontoY,node->Largura,node->CorBord,node->CorPrenche,nomeSvG);
        TextoSvg(node->PontoX,node->PontoY,"#",nomeSvG);
        node=node->prox;
    }
}