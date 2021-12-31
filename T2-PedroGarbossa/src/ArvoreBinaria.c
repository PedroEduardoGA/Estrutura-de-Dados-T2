#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ArvoreBinaria.h"
#include "Extras.h"
#include "svg.h"

typedef struct N{
    double x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
    char CorLinha[30];
    double radio;

    struct N *Pai;
    struct N *Filho_esq;
    struct N *Filho_dir;
}no;

typedef struct T{
    no *Raiz; //primeiro elemento da arvore
}tree;

Arvore CreateTree()//Aloca uma arvore
{
    tree* arvore = (tree*) malloc(sizeof(tree));//alloca, cria variavel e faz cast de tree* com arvore
    arvore->Raiz=NULL;

    return arvore;//retorna uma arvore sem raiz
}

void Insere(Arvore t,double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,double radio,char Cor[30])
{
    no* node = (no*) malloc(sizeof(no));
    tree* arvore = (tree*) t;
    int inserido=0;
    no* aux;
    
    strcpy(node->CorLinha,Cor);
    node->x1=x1;
    node->y1=y1;
    node->x2=x2;
    node->y2=y2;
    node->x3=x3;
    node->y3=y3;
    node->x4=x4;
    node->y4=y4;
    node->radio=radio;
    //x,y -> x3,y3 forma o segmento superior horizontal; x,y -> x4,y4 forma o segmento esquerdo vertical
    //x3,y3 -> x2,y2 forma o segmento direito vertical; x4,y4 -> x2,y2 forma o segmento inferior horizontal

    node->Filho_dir=NULL;
    node->Filho_esq=NULL;
    if(arvore->Raiz == NULL)//eh inserido a raiz
    {
        node->Pai=NULL;
        arvore->Raiz=node;
        return;
    }else
        aux=arvore->Raiz;

    while ((aux!=NULL)&&(inserido!=1))
    {
        if(x1 <= aux->x1)//vai pra esquerda por ser menor
        {
            if(aux->Filho_esq==NULL)
            {
                aux->Filho_esq=node;
                node->Pai=aux;
                inserido=1;
                break;
            }else
                aux=aux->Filho_esq;
        }

        if(x1 > aux->x1)//vai pra direita por ser maior
        {
            if(aux->Filho_dir==NULL)
            {
                aux->Filho_dir=node;
                node->Pai=aux;
                inserido=1;
                break;
            }else
                aux=aux->Filho_dir;
        }
    }
}

void Imprime(Noh nod)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        
        Imprime(node->Filho_esq);
        printf("x1: %lf e y1: %lf -",node->x1,node->y1);
        Imprime(node->Filho_dir);
    }
}

void Libera(Noh nod)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        Libera(node->Filho_dir);
        Libera(node->Filho_esq);
        free(node);
    }
}

Noh GetFirstTree(Arvore arv)
{
    tree* arvore = (tree*) arv;
    return arvore->Raiz;
}

Noh GetNodeTree(Arvore arv,double x1)
{
    tree* arvore = (tree*) arv;
    no* aux;
    aux=arvore->Raiz;

    if(aux==NULL)
        return NULL;

    while ((aux!=NULL)&&(aux->x1!=x1))
    {
        if(x1 < aux->x1)
            aux=aux->Filho_esq;
        else
            aux=aux->Filho_dir;
    }

    if(aux->x1 == x1)
        return aux;
    else 
        return NULL;
}

int ExisteValor(Arvore arv,double x1)
{
    tree* arvore = (tree*) arv;
    no* aux;
    aux=arvore->Raiz;
    while ((aux!=NULL)&&(aux->x1!=x1))
    {
        if(x1 < aux->x1)
            aux=aux->Filho_esq;
        else
            aux=aux->Filho_dir;
    }
    if(aux==NULL)
        return 0;

    if(aux->x1 == x1)
        return 1;
    else
        return 0;   
}

Noh MaiorMenor(Noh Node,int i)
{
    no* node = (no*) Node;
    if(i==0)//0 pq o noh passado eh o filho esquerda
    {
        while (node->Filho_dir!=NULL)
            node=node->Filho_dir;//retorna o maior valor da sub arvore esquerda
    }else
        {
            while (node->Filho_esq!=NULL)
            node=node->Filho_esq;
        }

    return node;
}

void RemoveNoh(Arvore arv,double x1)
{
    tree* arvore = (tree*) arv;
    no* aux1;
    no* node;
    no* aux2;

    if(ExisteValor(arvore,x1)==0)
    {
        printf("\n%lf Nao existe na arvore, logo nao pode ser removido!",x1);
        return;
    }

    aux1=arvore->Raiz;
    node=GetNodeTree(arvore,x1);
    if((node->Filho_esq == NULL)&&(node->Filho_dir == NULL))//Se o noh for uma folha
    {
        if(node==arvore->Raiz)
            arvore->Raiz=NULL;
        else
            {
                aux2=node->Pai;
                if(aux2->Filho_dir==node)
                    aux2->Filho_dir=NULL;
                else
                    aux2->Filho_esq=NULL; 
            }
        free(node);
        return;
    }

    if((node->Filho_esq == NULL)||(node->Filho_dir == NULL))//o noh possui so um filho
    {
        if(node==arvore->Raiz)//elemento que sera removido eh a raiz da arvore
        {
            if(node->Filho_esq==NULL)
            {
                aux1=node->Filho_dir;
                arvore->Raiz=aux1;
                aux1->Pai=NULL;

                free(node);
            }else
                {
                    aux1=node->Filho_esq;
                    arvore->Raiz=aux1;
                    aux1->Pai=NULL;

                    free(node);
                }
            
            return;
        }
        aux1=node->Pai;
        if(node->Filho_esq == NULL)
            aux2= node->Filho_dir;
        else
            aux2= node->Filho_esq;

        if(aux1->Filho_dir==node)
            aux1->Filho_dir=aux2;
        else
            aux1->Filho_esq=aux2;

        aux2->Pai=aux1;
        free(node);
        return;
    }

    no* anterior;
    if((node->Filho_esq != NULL)&&(node->Filho_dir != NULL))//o noh possui os 2 filhos
    {
        if(node==aux1)//o elemento removido eh a raiz da arvore
        {
            aux2=MaiorMenor(node->Filho_esq,0);//aux 2 vai receber o noh com maior valor encontrado na arvore esquerda
            anterior=aux2->Pai;
            if(aux2->Filho_esq!=NULL)
                anterior->Filho_dir=aux2->Filho_esq;
            else
                anterior->Filho_dir=NULL;
            
            aux1=node->Filho_esq;
            aux1->Pai=aux2;
            aux1=node->Filho_dir;
            aux1->Pai=aux2;
            aux2->Filho_dir=node->Filho_dir;//noh que vai no lugar do node recebe filho direito da raiz
            aux2->Filho_esq=node->Filho_esq;
            aux2->Pai=NULL;
            arvore->Raiz=aux2;
    
            free(node);
            return;
        }

        aux2=MaiorMenor(node->Filho_esq,0);//aux 2 vai receber o noh com maior valor encontrado na arvore esquerda
        anterior=aux2->Pai;
        if((aux2->Filho_esq==NULL)&&(aux2->Filho_dir==NULL))//se o noh que vai no lugar do removido nao possui filhos
        {
            anterior->Filho_dir=NULL;
            aux2->Filho_dir=node->Filho_dir;
            aux2->Filho_esq=node->Filho_esq;
            aux1=node->Pai;
            if(aux1->Filho_dir==node)
                aux1->Filho_dir=aux2;
            else
                aux1->Filho_esq=aux2;

            aux2->Pai=aux1;
            free(node);
            return;
        }

        if(anterior==node)
        {
            anterior=node->Pai;
            aux2->Filho_dir=node->Filho_dir;
            aux2->Pai=anterior;

            if(anterior->Filho_dir==node)
                anterior->Filho_dir=aux2;
            else
                anterior->Filho_esq=aux2;

            free(node);
            return;
        }
        if(aux2->Filho_esq!=NULL)
            anterior->Filho_dir=aux2->Filho_esq;
        else
            anterior->Filho_dir=NULL;
            
        aux1=node->Filho_esq;
        aux1->Pai=aux2;//filho esquerdo do node vai receber o aux2 como pai
        aux1=node->Filho_dir;
        aux1->Pai=aux2;//filho direito do node vai receber o aux2 como pai
        aux2->Filho_dir=node->Filho_dir;//noh que vai no lugar do node recebe filho direito da raiz
        aux2->Filho_esq=node->Filho_esq;
        anterior=node->Pai;//anterior eh o noh pai do node q sera removido
        
        if(anterior->Filho_esq==node)
            anterior->Filho_esq=aux2;
        else
            anterior->Filho_esq=aux1;
        
        aux2->Pai=anterior;
        free(node);
    }
}

//=================================================QRY==================================================================
void CriaPoligonos(Arvore arv1,Arvore arv2,double x,double y,double X,double Y,double X2,double Y2,double Radio)
{
    //funcao vai chamar funcao que percorre recursivamente arvore dos segmentos criando o poligono pra cada segmento de acordo com x,y da bomba
    no* node1;
    node1=GetFirstTree(arv1);//node recebe o primeiro noh da arvore dos segmentos
    AnalisaSegmentos(arv2,node1,x,y,X,Y,X2,Y2,Radio);

}

void AnalisaSegmentos(Arvore arv2,Noh nod,double x,double y,double X,double Y,double X2,double Y2,double radio)
{
    no* node = (no*) nod;
    int Right=0,left=0,up=0,down=0,feito=0;//valores que serao usados pra saber onde o segmento esta em relacao a bomba
    double variacaoX,variacaoY,radiacao;
    double x1,y1,x2,y2,x3,y3,x4,y4;//coordenadas a serem usadas pra insercao do poligono na arvore
    char *Cor;

    if(node == NULL)
        return;

    if(node != NULL)
    {
        //analise de cada noh contendo 4 segmentos
        if(node->x1 < x)
            left=1;//segmento esta a esquerda da bomba
        else
            Right=1;//segmento esta a direita da bomba

        if(node->y1 < y)
            up=1;//segmento esta acima da bomba
        else
            down=1;//segmento esta abaixo da bomba
        
        if(down==1)//verifica se a bomba nao esta no meio do segmento
        {
            if(node->x1 < x && node->x3 > x)//a bomba esta no meio do segmento
            {
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada

                variacaoX=node->x1-x;
                x1=node->x1;
                y1=node->y1;
                x2=node->x1+variacaoX;
                y2=Y2;
                variacaoX=node->x3-x;
                x3=node->x3+variacaoX;
                y3=Y2;
                x4=node->x3;
                y4=node->y3;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;//foi criado o poligono pros segmentos do retangulo atual
            }

            if(left==1 && feito==0)//segmento esta a esquerda e abaixo da bomba
            {
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada

                variacaoX=node->x1-x;
                x1=node->x1;
                y1=node->y1;
                x2=node->x1+variacaoX;
                y2=Y2;
                variacaoX=node->x2-x;
                x3=node->x2+variacaoX;
                y3=Y2;
                x4=node->x2;
                y4=node->y2;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;
            }

            if(Right==1 && feito==0)//segmento esta a direta e abaixo da bomba
            {
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada

                variacaoX=node->x4-x;
                x1=node->x4;
                y1=node->y4;
                x2=node->x4+variacaoX;
                y2=Y2;
                variacaoX=node->x3-x;
                x3=node->x3+variacaoX;
                y3=Y2;
                x4=node->x3;
                y4=node->y3;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;
            }
        }

        if(up == 1 && feito==0)
        {
            if(node->x1 < x && node->x3 > x)//a bomba esta no meio do segmento
            {
                //reducao=0.2;//reducao de 20%
                //reducao=reducao*radio;
                //radiacao=reducao;
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada

                variacaoX=node->x1-x;
                x1=node->x1;
                y1=node->y1;
                x2=node->x1+variacaoX;
                y2=Y;
                variacaoX=node->x3-x;
                x3=node->x3+variacaoX;
                y3=Y;
                x4=node->x3;
                y4=node->y3;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;//foi criado o poligono pros segmentos do retangulo atual
            }
        }

        if(left==1 && feito==0)//segmento esta a cima e a esquerda da bomba
        {
            if(node->y1 < y && node->y2 > y)//bomba esta no meio do segmento vertical
            {
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada

                variacaoY=node->y1-y;
                x1=node->x3;
                y1=node->y3;
                x2=X;
                y2=node->y3+variacaoY;
                variacaoY=node->y2-y;
                x3=X;
                y3=node->y2+variacaoY;
                x4=node->x2;
                y4=node->y2;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;
            }

            if(feito==0)//segmento esta a esquerda e acima da bomba
            {
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada
                
                variacaoX=node->x2-x;
                x1=node->x3;
                y1=node->y3;
                x2=node->x3+variacaoX;
                y2=Y;
                variacaoX=node->x4-x;
                x3=node->x4+variacaoX;
                y3=Y;
                x4=node->x4;
                y4=node->y4;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;
            }
        }

        if(Right==1 && feito==0)
        {
            if(node->y1 < y && node->y4 > y)//bomba esta no meio do segmento vertical
            {
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada

                variacaoY=node->y1-y;
                x1=node->x1;
                y1=node->y1;
                x2=X2;
                y2=node->y4+variacaoY;
                variacaoY=node->y4-y;
                x3=X2;
                y3=node->y4+variacaoY;
                x4=node->x4;
                y4=node->y4;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;
            }

            if(feito==0)//segmento esta a direita e acima da bomba
            {
                radiacao=0.8*radio;
                Cor=CodigoExposicao(radiacao);//atribui a cor de acordo com a radiacao encontrada

                variacaoX=node->x1-x;
                x1=node->x1;
                y1=node->y1;
                x2=node->x1+variacaoX;
                y2=Y;
                variacaoX=node->x2-x;
                x3=node->x2+variacaoX;
                y3=Y;
                x4=node->x2;
                y4=node->y2;
                //ordem
                Insere(arv2,x1,y1,x2,y2,x3,y3,x4,y4,radiacao,Cor);//eh inserido o poligono na arvore dos poligonos
                feito=1;
            }
        }
        //chamada recursiva pra fzr o mesmo procedimento pra todos segmentos da arvore
        AnalisaSegmentos(arv2,node->Filho_esq,x,y,X,Y,X2,Y2,radio);
        AnalisaSegmentos(arv2,node->Filho_dir,x,y,X,Y,X2,Y2,radio);
    }
}

void PercorreBinaria(Noh nod,char svg[])
{
    no* node = (no*) nod;

    if(node == NULL)
        return;

    if(node != NULL)
    {   
        CriaPoligono(node->x1,node->y1,node->x2,node->y2,node->x3,node->y3,node->x4,node->y4,node->CorLinha,svg);
        
        PercorreBinaria(node->Filho_esq,svg);
        PercorreBinaria(node->Filho_dir,svg);    
    }
}

void Poligonos(Noh nod,double x,double y,double *Radiacao)//percorre arvore dos poligonos verificando se x,y eh interno
{
    no* node = (no*) nod;
    double PolyY[4],PolyX[4];

    if(node!=NULL)
    {
        //fazer verificar se o ponto x,y pertence ao poligono atual, se pertencer radicao = radicao - node->radiacao
        PolyX[0]=node->x1;
        PolyY[0]=node->y1;
        PolyX[1]=node->x2;
        PolyY[1]=node->y2;
        PolyX[2]=node->x3;
        PolyY[2]=node->y3;
        PolyX[3]=node->x4;
        PolyY[3]=node->y4;

        bool Sim= PontoInPoligono(PolyX,PolyY,4,x,y);
        
        if(Sim == true)
            *Radiacao= node->radio;//node radio eh a radiacao do poligono

        //recursividade
        Poligonos(node->Filho_esq,x,y,Radiacao);
        Poligonos(node->Filho_dir,x,y,Radiacao);
    }
}

bool PontoInPoligono(double PolyX[],double PolyY[],int Cantos,double x,double y)//verifica se o ponto x,y passado pertence ao poligono
{
    int i,j=Cantos-1;
    bool Pertence= false;

    for(i=0; i<Cantos; i++)
    {
        if(((PolyY[i] < y && PolyY[j] >= y)||(PolyY[j] < y && PolyY[i] >= y))&&(PolyX[i] <= x || PolyX[j] <= x))
        {
            if(PolyX[i]+(y-PolyY[i])/(PolyY[j]-PolyY[i])*(PolyX[j]-PolyX[i])<x)
                Pertence= !Pertence;
        }
        j=i;
    }

    return Pertence;
}