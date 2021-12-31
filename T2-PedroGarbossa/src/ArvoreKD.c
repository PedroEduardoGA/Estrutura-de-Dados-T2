#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ArvoreKD.h"
#include "svg.h"
#include "saidasTxt.h"
#include "Extras.h"


typedef struct N{ //Onde guarda infos como, cor borda, preenchimento...
    double x,y,r,w,h,radiacao;
    char Ide[70];
    char CorPrenche[30];
    char CorBorda[30];
    int morteEminente;
    int Quantidade;

    struct N *Pai;
    struct N *Filho_esq;
    struct N *Filho_dir;
}no;

typedef struct T{
    no *Raiz; //primeiro elemento da list
}tree;

ArvoreKD CreateTreeKD()//Aloca uma tree
{
    tree* arvore = (tree*) malloc(sizeof(tree));
    arvore->Raiz=NULL;

    return arvore;//retorna uma arvore sem raiz
}

void InsereKD(ArvoreKD t,char Id[70],double x,double y,double raio,double largu,double altu,char CorPren[30],char CorBord[30])
{
    no* node = (no*) malloc(sizeof(no));
    tree* arvore = (tree*) t;
    int inserido=0,i=0;
    no* aux;
    
    node->x=x;
    node->y=y;
    node->w=largu;
    node->h=altu;
    node->r=raio;
    node->radiacao=0.0;
    node->morteEminente=0;//se for pra 1 a pessoa morrera dentro de 30 minutos
    node->Quantidade=0;
    strcpy(node->Ide,Id);
    strcpy(node->CorBorda,CorBord);
    strcpy(node->CorPrenche,CorPren);

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
        if(((i % 2)==0)||(i==0))
        {
            if(x < aux->x)//vai pra esquerda por ser menor
            {
                if(aux->Filho_esq==NULL)
                {
                    aux->Filho_esq=node;
                    node->Pai=aux;
                    inserido=1;
                    break;
                }else
                    aux=aux->Filho_esq;
            }else
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
        }else   
            {
                if(y < aux->y)//vai pra esquerda por ser menor
                {
                    if(aux->Filho_esq==NULL)
                    {
                        aux->Filho_esq=node;
                        node->Pai=aux;
                        inserido=1;
                        break;
                    }else
                        aux=aux->Filho_esq;
                }else//vai pra direita por ser maior
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
        i++;
    }
}

void ImprimeKD(NohKD nod)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        ImprimeKD(node->Filho_esq);
        printf("[Id]= %s x-%lf & y-%lf r= %lf <->",node->Ide,node->x,node->y,node->r);
        ImprimeKD(node->Filho_dir);
    }
}

void LiberaKD(NohKD nod)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        LiberaKD(node->Filho_dir);
        LiberaKD(node->Filho_esq);
        free(node);
    }
}

NohKD GetFirstKD(ArvoreKD arv)
{
    tree* arvore = (tree*) arv;
    return arvore->Raiz;
}

NohKD GetNodeKD(ArvoreKD arv,double x,double y)
{
    tree* arvore = (tree*) arv;
    no* aux;
    int i=0;
    aux=arvore->Raiz;

    if(aux==NULL)
        return NULL;

    while ((aux!=NULL)&&(aux->x!=x)&&(aux->y!=y))
    {
        if((i % 2)==0)
        {
            if(x < aux->x)
                aux=aux->Filho_esq;
            else
                aux=aux->Filho_dir;  
        }else
            {
                if(y < aux->y)
                    aux=aux->Filho_esq;
                else
                    aux=aux->Filho_dir;
            }
        i++;
    }
    if(aux==NULL)
        return NULL;
    
    if((aux->x==x)&&(aux->y==y))
        return aux;
    else 
        return NULL;
}

void GetNodeID(NohKD nod,char id[70],double *x,double *y,double *w,double *h)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        
        GetNodeID(node->Filho_esq,id,x,y,w,h);
        if(strcmp(node->Ide,id)==0)
        {
            *x=node->x;
            *y=node->y;
            *w=node->w;
            *h=node->h;
        }
        GetNodeID(node->Filho_dir,id,x,y,w,h);
    }
}

void RemoveNohKd(ArvoreKD arv,NohKD nod)
{
    tree* arvore = (tree*) arv;
    no* node = (no*) nod;
    no* aux1;
    no* aux2;

    if(node==NULL)
    {
        printf("\nElemento inexistente na arvore!");
        return;
    }

    aux1=arvore->Raiz;
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

    if((node->Filho_esq != NULL)&&(node->Filho_dir != NULL))
    {
        no* anterior;
        anterior=node->Pai;
        if(anterior->Filho_dir==node)
            anterior->Filho_dir=node;
        else
            anterior->Filho_esq=node;

        aux1=node;
        aux1->morteEminente=2;
        return;
        free(node);
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
}

void PercorreKD(ArvoreKD arv,NohKD nod,int tipo,char svg[],char txt[])
{
    tree* arvore = (tree*) arv;
    no* node = (no*) nod;
    no* aux1;
    no* aux2;

    if(node!=NULL)
    {
        if(tipo==0)//serve pra percorrer a arvore pra ver quais elementos tem que ser removidos
        {
            aux1=node->Filho_esq;
            aux2=node->Filho_dir;
            PercorreKD(arvore,aux1,tipo,svg,txt);
    
            if(node->morteEminente==1)
                RemoveNohKd(arvore,node);
        
            PercorreKD(arvore,aux2,tipo,svg,txt);
        }

        if(tipo==1)//percorre a arvore atribuindo  a cor dos circulos
        {
            char *Cor;
            aux1=node->Filho_esq;
            aux2=node->Filho_dir;
            PercorreKD(arvore,aux1,tipo,svg,txt);//recursividade

            if(node->morteEminente!=2)
            {
                Cor=CodigoExposicao(node->radiacao);
                strcpy(node->CorBorda,Cor);//o circulo recebe a cor de acordo com sua radiacao
                strcpy(node->CorPrenche,Cor);
            
                if((node->morteEminente==0)&&(node->radiacao>1000)&&(node->radiacao <= 8000))
                {
                    SaidaIm(txt,node->Ide,"Im",0);//saida txt dizendo que o id tem morte eminente
                    node->morteEminente=1;
                }
            
                if((node->radiacao > 8000)&&(node->morteEminente!=2))//pessoa com radiacao superior a 8000 mSv morre instanteamente
                {
                    SaidaIm(txt,node->Ide,"Im",1);//saida txt dizendo que o id teve morte instantanea
                    CriaCirculoRIP(node->x,node->y,node->r,svg);
                    RemoveNohKd(arvore,node);
                    //node->morteEminente=2;
                }   
            }
             
            PercorreKD(arvore,aux2,tipo,svg,txt);//recursividade
        }
    }
    
}

//==========================FuncoesConsulta================================
void CoordenadasBounding(NohKD nod,double *x,double *y,double *x2,double *y2)//Funcao retorna os menores valores x e y e os maiores de x2 y2
{
    no* node = (no*) nod;
    double x2noh,y2noh;
    if(node!=NULL)
    {
        CoordenadasBounding(node->Filho_esq,x,y,x2,y2);
        
        x2noh=node->x+node->w;
        y2noh=node->y+node->h;
        if(node->x < *x)
            *x=node->x;

        if(node->y < *y)
            *y=node->y;

        if(x2noh > *x2)
            *x2=x2noh;

        if(y2noh > *y2)
            *y2=y2noh;

        CoordenadasBounding(node->Filho_dir,x,y,x2,y2);
    }
}

int EstaVazia(ArvoreKD t)
{
    tree* arvore = (tree*) t;
    if(arvore->Raiz == NULL)
        return 1;
    else
        return 0;
}

void dr(ArvoreKD t,NohKD nod,double x,double y, double x2, double y2,char Ide[70],char txt[],int first)
{
    tree* arvore = (tree*) t;
    no* node = (no*) nod;
    double w,h,Xr2=0,Yr2=0;

    if(first==0)
    {
        x=0;
        y=0;
        w=0;
        h=0;
        x2=0;
        y2=0;

        GetNodeID(arvore->Raiz,Ide,&x,&y,&w,&h);

        x2= x+w;//Vai calcular o x2 do retangulo passado como parametro
        y2= y+h;//Vai calcular o y2 do retangulo passado como parametro
        if((x==0)&&(y==0)&&(x2==0)&&(y2==0))
        {
            IdInexiste(txt,Ide,"dr");
            return;
        }
        node=arvore->Raiz;
    }
    
    if(node!=NULL)
    {
        Xr2=node->x+node->w;
        Yr2=node->y+node->h;
        if((node->x >= x)&&(Xr2 < x2)&&(node->y >= y)&&(Yr2 < y2))//Se verdade esta inteiramente dentro do retangulo passado
        {
            //Achou um inteiramente dentro do retangulo passado
            RemoveuRetan(txt,node->Ide,"dr");
            node->morteEminente=1;        
        }
        dr(arvore,node->Filho_esq,x,y,x2,y2,Ide,txt,1);
        dr(arvore,node->Filho_dir,x,y,x2,y2,Ide,txt,1);
    }
}

void Fg(NohKD Nod1,NohKD Nod2,double xcirc,double ycirc,double raioCirculo,char svg[])
{
    no* node1= (no*) Nod1;
    no* node2= (no*) Nod2;

    double distancia,Raiz,menorDist,Pot1,Pot2,CentroX,CentroY;

    if(node2==NULL)
    {
        printf("\nArvore Retangulos vazias!");
        return;
    }

    if(node1!=NULL)//percorrendo a arvore dos circulos
    {
        Pot1=node1->x - xcirc;//x da pessoa - x do circulo
        Pot2=node1->y - ycirc;//y da pessoa - y do circulo
        Pot1=Pot1*Pot1;
        Pot2=Pot2*Pot2;
        Raiz=Pot1+Pot2;
        distancia=sqrt(Raiz);

        if(distancia <= raioCirculo)//se for maior quer dizer que a pessoa nao esta dentro do circulo informado
        {
            CentroX=node2->x+(node2->w/2.0);
            CentroY=node2->y+(node2->h/2.0);

            Pot1=node1->x - CentroX;
            Pot2=node1->y - CentroY;
            Pot1=Pot1*Pot1;
            Pot2=Pot2*Pot2;
            Raiz=Pot1+Pot2;
            menorDist=sqrt(Raiz);//calcula a distancia da pessoa ate o primeiro retangulo da arvore
            CriaPontinho(node1->x,node1->y,node1->r,"lightgrey","lightgrey",svg);//cria um circulo cinza claro na posicao da pessoa

            ProcuraMenorDist(node2,node1->x,node1->y,&CentroX,&CentroY,&menorDist);//centro x/y sera x e y do lugar q a pessoa vai
            LinhaTracejada(node1->x,node1->y,CentroX,CentroY,"darkgrey",svg);//cria linha tracejada da pessoa até onde ela vai

            Animacao(node1->x,CentroX,node1->y,CentroY,node1->r,node1->CorPrenche,node1->CorBorda,svg);
            node1->x=CentroX;
            node1->y=CentroY;
        }
        Fg(node1->Filho_esq,node2,xcirc,ycirc,raioCirculo,svg);
        Fg(node1->Filho_dir,node2,xcirc,ycirc,raioCirculo,svg);
    }
}

void ProcuraMenorDist(NohKD nod,double x,double y,double *Xnovo,double *Ynovo,double *MenorDist)
{
    no* node= (no*) nod;
    double Pot1,Pot2,Raiz,distancia,CentroX,CentroY;

    if(node!=NULL)
    {
        CentroX=node->x+(node->w/2.0);
        CentroY=node->y+(node->h/2.0);

        Pot1=x - CentroX;
        Pot2=y - CentroY;
        Pot1=Pot1*Pot1;
        Pot2=Pot2*Pot2;
        Raiz=Pot1+Pot2;
        distancia=sqrt(Raiz);

        if(distancia < *MenorDist)
        {
            *MenorDist=distancia;
            *Xnovo=CentroX;//nova coordenada do x pra qual a pessoa vai
            *Ynovo=CentroY;//nova coordenada do y pra qual a pessoa vai
        }

        ProcuraMenorDist(node->Filho_esq,x,y,Xnovo,Ynovo,MenorDist);
        ProcuraMenorDist(node->Filho_dir,x,y,Xnovo,Ynovo,MenorDist);
    }

}

void Dpi(NohKD Node,double X, double Y,char txt[])
{
    no* node= (no*) Node;
    double Xr,Wr,Yr,Hr;//x,y,w,h dos retangulos analisados

    if(node!=NULL)
    {   
        Xr=node->x;
        Yr=node->y;
        Wr=node->w;
        Hr=node->h;
        if((X>Xr)&&(X< Xr+Wr)&&(Y> Yr)&&(Y< Yr+Hr))//Se verdade ponto X e Y sao internos do retangulo
        {
            //Achou um retangulo que tem X e Y passados como ponto interno!
            RemoveuRetan(txt,node->Ide,"dpi");
            node->morteEminente=1;//1 pois esse retangulo sera removido       
        }
        
        Dpi(node->Filho_esq,X,Y,txt);
        Dpi(node->Filho_dir,X,Y,txt);
    }
}

void SvgFinalKD(NohKD nod,char nomeSvg[],int tipo,int fg)
{
    no* node = (no*) nod;
    char Qtd[6];
    
    if(tipo==0)//printa no svg os retangulos existentes na arovre
    {
        if(node!=NULL)
        {
            if(node->morteEminente!=2)
            {
                if(fg==0)
                    criaRetangulo(node->w,node->h,node->x,node->y,node->CorBorda,node->CorPrenche,nomeSvg);
                
                if(fg==1)//se houve consulta fg eh printado a quantidade de pessoas no edificio
                {
                    if(node->Quantidade>0)//so printa a quantidade no svg se tiver alguem abrigado
                    {
                        sprintf(Qtd,"%d",node->Quantidade);
                        TextoSvg(node->x+0.2,node->y+0.1,Qtd,nomeSvg);    
                    } 
                }
            }
            SvgFinalKD(node->Filho_esq,nomeSvg,tipo,fg);
            SvgFinalKD(node->Filho_dir,nomeSvg,tipo,fg);
        }
        //Vai ter entrado aqui se for pra printar retangulos
    }

    if(tipo==1)
    {//printa no svg os circulos existentes na arovre
        if(node!=NULL)
        {
            if(node->morteEminente!=2)
                CriaPontinho(node->x,node->y,node->r,node->CorBorda,node->CorPrenche,nomeSvg);
                
            SvgFinalKD(node->Filho_esq,nomeSvg,tipo,fg);        
            SvgFinalKD(node->Filho_dir,nomeSvg,tipo,fg); 
        }
        
    }
}

void t30(ArvoreKD arv,NohKD Node,char txt[],char svg[])
{
    tree* arvore = (tree*) arv;
    no* node= (no*) Node;
    no* aux1;
    no* aux2;

    if(node!=NULL)
    {   
        aux1=node->Filho_esq;
        aux2=node->Filho_dir;
        
        t30(arvore,aux1,txt,svg);
        
        if(node->morteEminente==1)//remover circulo da arvore
        {
            SaidaIm(txt,node->Ide,"t30",1);//saida txt
            CriaCirculoRIP(node->x,node->y,node->r,svg);//cria circulo preto com cruz branca no svg
            RemoveNohKd(arvore,node);
            //node->morteEminente=2;
        }
        
        t30(arvore,aux2,txt,svg);
    }
}

void AnalisaEdificios(NohKD node1,NohKD node2,char txt[],int tipo)//percorre os retangulos analisando quantas pessoas estao abrigadas
{
    no* nodeCirc= (no*) node1;
    no* nodeRetan= (no*) node2;
    double xR,yR,xR2,yR2;

    if(nodeRetan != NULL)
    {  
        xR=nodeRetan->x;
        yR=nodeRetan->y;
        xR2=nodeRetan->x+nodeRetan->w;
        yR2=nodeRetan->y+nodeRetan->h;
        if(tipo==0)
            FgRetan(txt,nodeRetan->Ide);//saida txt informando id do retangulo
        
        AnalisaPessoas(nodeCirc,nodeRetan,xR,yR,xR2,yR2,nodeRetan->h,txt,tipo);

        AnalisaEdificios(nodeCirc,nodeRetan->Filho_esq,txt,tipo);
        AnalisaEdificios(nodeCirc,nodeRetan->Filho_dir,txt,tipo);
    }

}

void AnalisaPessoas(NohKD nod,NohKD node2,double x,double y,double xR,double yR,double altura,char txt[],int tipo)
{
    no* node= (no*) nod;//circulos
    no* nodeRet= (no*) node2;//retangulos
    double xC,yC,raio;

    if(node != NULL)
    {
        xC=node->x;
        yC=node->y;
        raio=node->r;
        if((xC > x)&&(yC > y)&&(xC < xR)&&(yC < yR)&&(raio<altura))// se isso eh vdd o circulo esta dentro do retangulo
        {
            if(tipo==0)//se o tipo eh 0 eh pq tem q ser printado no txt
                FgCirculo(txt,node->Ide);//saida txt com id do circulo

            node->Quantidade+=1;//incrementa a quantidade de retangulos em que o circulo esta dentro
            nodeRet->Quantidade+=1;
        }

        AnalisaPessoas(node->Filho_esq,nodeRet,x,y,xR,yR,altura,txt,tipo);
        AnalisaPessoas(node->Filho_dir,nodeRet,x,y,xR,yR,altura,txt,tipo);
    }
}

void CalculaRadiacao(NohKD nod,int *Quantidade,double *Radiacao,double RadioMeteoro,int tipo)
{
    no* node= (no*) nod;
    double reducao;

    if(node!=NULL)
    {
        if(tipo==2)
        {
            reducao=*Quantidade*0.2;//multiplica quantidade de paredes pela reducao dos 20%
            reducao=reducao*RadioMeteoro;
            node->radiacao=node->radiacao+(RadioMeteoro-reducao); 
        }
        CalculaRadiacao(node->Filho_esq,Quantidade,Radiacao,RadioMeteoro,tipo);
        CalculaRadiacao(node->Filho_dir,Quantidade,Radiacao,RadioMeteoro,tipo);
    }

    if(tipo==1)//serve pra quando a consulta for nve
    {
        reducao=*Quantidade * 0.2;
        reducao=reducao*RadioMeteoro;
        *Radiacao=RadioMeteoro-reducao;
    }
}

void InicializaVar(NohKD nod,double radio)
{
    no* node= (no*) nod;

    if(node!=NULL)
    {
        node->Quantidade=0;
        node->radiacao=node->radiacao+radio;

        InicializaVar(node->Filho_esq,radio);
        InicializaVar(node->Filho_dir,radio);
    }    
}

void VerificaPonto(NohKD nod,int *Qtd,double x,double y)
{
    no* node= (no*) nod;
    double Xr,Yr,Wr,Hr;

    if(node!=NULL)
    {

        Xr=node->x;
        Yr=node->y;
        Wr=node->w;
        Hr=node->h;
        if((x>Xr)&&(x< Xr+Wr)&&(y> Yr)&&(y< Yr+Hr))//Se verdade ponto X e Y sao internos do retangulo
            *Qtd=*Qtd+1;    
        
        VerificaPonto(node->Filho_esq,Qtd,x,y);
        VerificaPonto(node->Filho_dir,Qtd,x,y);
    }
}

void DivideRetangulos(Arvore Bina,NohKD nod)
{
    no* node= (no*) nod;
    double x2,y2,x3,y3,x4,y4;
    
    if(node!=NULL)
    {
        //divisao do retangulo em 4 segmentos
        x2=node->x+node->w;
        y2=node->y+node->h;

        x3=x2;
        y3=node->y;

        x4=node->x;
        y4=y2;
        //x,y -> x3,y3 forma o segmento superior horizontal; x,y -> x4,y4 forma o segmento esquerdo vertical
        //x3,y3 -> x2,y2 forma o segmento direito vertical; x4,y4 -> x2,y2 forma o segmento inferior horizontal
        Insere(Bina,node->x,node->y,x2,y2,x3,y3,x4,y4,0,node->CorBorda);//as coordenadas dos segmentos sao inseridas na arvore binaria

        DivideRetangulos(Bina,node->Filho_esq);
        DivideRetangulos(Bina,node->Filho_dir);
    }
}

void RadiacaoX_Y(Arvore Binaria,NohKD nod,double x,double y,double RadioTotal,double *radiacao,int tipo)
{
    no* node= (no*) nod;
    double reducao;

    if(node!=NULL)
    {    
        Noh RaizBina=GetFirstTree(Binaria);
        
        if(node->morteEminente!=2)
        {
            reducao=node->radiacao;
            Poligonos(RaizBina,node->x,node->y,&reducao);
            node->radiacao=reducao;

            if((node->morteEminente==0)&&(node->radiacao>1000)&&(node->radiacao <= 8000))
                node->morteEminente=1;
         
        }
        RadiacaoX_Y(Binaria,node->Filho_esq,x,y,RadioTotal,radiacao,tipo);
        RadiacaoX_Y(Binaria,node->Filho_dir,x,y,RadioTotal,radiacao,tipo);
    }

    if(node==NULL && tipo==1)//consulta nve
    {
        Noh RaizBina=GetFirstTree(Binaria);
        reducao=RadioTotal;
        Poligonos(RaizBina,x,y,&reducao);
        *radiacao=reducao;
    }
}