#ifndef _ARVOREKD_H
#define _ARVOREKD_H
#include "ArvoreBinaria.h"
//Modulo responsavel pela manipulacao das arvores Kd's e pela realizacao das consultas envolvendo as arvores

typedef void* ArvoreKD;//void pointer
typedef void* NohKD;//void pointer

//Funcao nao recebe nada como parametro
//Aloca memoria pra uma arvore e cria a mesma
//Funcao retorna uma arvore vazia!
ArvoreKD CreateTreeKD();

//Funcao recebe a arvore, um id, coordenadas x e y, raio, largura, altura e as cores de preenchimento e borda
//Aloca memoria pra um noh da arvore e insere na arvore de acordo com a coordenada x e y interlcando entre as comparacoes
//Funcao nao retorna nada!
void InsereKD(ArvoreKD t,char Id[70],double x,double y,double raio,double largu,double altu,char CorPren[30],char CorBord[30]);

//Funcao recebe um noh
//Imprime na tela recursivamente a arvore inteira e as informacoes contidas em cada noh
//Funcao nao retorna nada!
void ImprimeKD(NohKD nod);

//Funcao recebe um noh
//Percorre a arvore recursivamente liberando a memoria alocada dos nohs
//Funcao nao retorna nada!
void LiberaKD(NohKD nod);

//Funcao recebe a arvore
//Funcao retorna a raiz da arvore!
NohKD GetFirstKD(ArvoreKD arv);

//Funcao recebe a arvore e as coordenadas x,y
//Percorre a arvore em busca do noh que contem as coordenadas x,y iguais as passadas como parametro
//Funcao retorna o noh que contem a coordenada x,y! Se x e y nao for encontrado retorna NULL!
NohKD GetNodeKD(ArvoreKD arv,double x,double y);

//Funcao recebe um noh, um id, ponteiro pra x,y, largura e altura
//Percorre a arvore recursivamente buscando o noh que contem o id igual ao passado como parametro
//Se esse noh eh encontrado o conteudo dos ponteiros eh alterado pro conteudo de cada campo respectivo do noh
//Funcao nao retorna nada!
void GetNodeID(NohKD nod,char id[70],double *x,double *y,double *w,double *h);

//Funcao recebe a arvore e o noh que sera removido
//Analisa a situacao do noh e realiza a remocao do mesmo
//Funcao nao retorna nada! Caso o noh passado seja NULL a funcao informa que nao houve remocao e retorna NULL!
void RemoveNohKd(ArvoreKD arv,NohKD nod);

//Funcao recebe a arvore, um noh, um inteiro tipo(0 - 1) e o nome do arquivo .svg
//Percorre a arvore recursivamente buscando os nohs marcados pra remocao
//Funcao nao retorna nada!
void PercorreKD(ArvoreKD arv,NohKD nod,int tipo,char svg[],char txt[]);

//Funcao recebe a arvore
//Verifica se a arvore esta vazia ou nao
//Funcao retorna 1 caso a arvore esteja vazia ou retorna 0 caso contrario
int EstaVazia(ArvoreKD t);

//====================================Funcoes-Qry====================================//
//Funcao recebe um noh, e ponteiros pra x,y, x2,y2
//Percorre a arvore recursivamente buscando os menores valores para x e y e os maiores para x2 e y2
//Se esses valores sao encontrados o conteudo dos ponteiros eh alterado pro conteudo de cada campo respectivo do noh
//Funcao nao retorna nada!
void CoordenadasBounding(NohKD nod,double *x,double *y,double *x2,double *y2);

//Funcao recebe a arvore e um noh, coordenadas x,y,x2,y2, um id, nome do arquivo .txt e um inteiro first(0 ou 1)
//Quando first==0 busca o retangulo com id informado e obtem os valores de x,y, largura e altura do retangulo
//Depois percorre a arvore recursivamente verificando quais retangulos estao inteiramente contidos no retangulo ID
//Os retangulos que estiverem contidos sao marcados para remocao posterior, e seu id eh informado na saida TXT
//Funcao nao retorna nada!
void dr(ArvoreKD t,NohKD nod,double x,double y, double x2, double y2,char Ide[70],char txt[],int first);

//Funcao recebe a arvore e um noh, coordenadas X e Y, nome do arquivo .txt
//Percorre a arvore recursivamente analisando quais retangulos tem o ponto X e Y informado como ponto interno
//Os retangulos que tiverem o ponto como interno sao marcados pra remocao posterior, e seu id eh informado na saida TXT
//Funcao nao retorna nada!
void Dpi(NohKD Node,double X, double Y,char txt[]);

//Funcao recebe um noh, coordenadas x e y, ponteiro para uma coordenada Xnovo,Ynovo e a menor distancia
//Percorre a arvore recursivamente analisando qual retangulo se encontra mais perto das coordenadas x e y
//Quando um retangulo de menor distancia eh encontrado o conteudo dos ponteiros sao alterados de acordo com o retangulo
//Funcao nao retorna nada!
void ProcuraMenorDist(NohKD nod,double x,double y,double *Xnovo,double *Ynovo,double *MenorDist);

//Funcao recebe um noh para os circulos e um noh para os retangulos, coordenadas de um circulo x,y e seu raio e o nome do .svg
//Percorre recursivamente a arvore dos circulos, verificando quais circulos estao dentro no circulo passado
//Os circulos que estiverem dentro, tem sua coordenada alterada pra dentro do retangulo mais proximo
//No svg eh criado uma linha do circulo ate seu retangulo mais proximo, tambem cria-se a animacao do circulo indo ate o retangulo
//Funcao nao retorna nada!
void Fg(NohKD Nod1,NohKD Nod2,double xcirc,double ycirc,double raioCirculo,char svg[]);

//Funcao recebe a arvore, um noh, nome do arquivo .txt e o nome do arquivo .svg 
//Percorre recursivamente a arvore analisando quais nohs contem o campo morteEminente = 1
//Quando encontrado, eh reportado no txt o id do circulo, no svg eh criado um circulo preto com uma cruz no ponto x,y do circulo, e o circulo eh removido
//Funcao nao retorna nada!
void t30(ArvoreKD arv,NohKD Node,char txt[],char svg[]);

//Funcao recebe um noh para os circulos e um noh para os retangulos, um inteiro tipo(0 - 1) e o nome do arquivo .txt
//Percorre recursivamente a arvore dos retangulos, reporta o id do retangulo caso tipo seja 0
//Para cada retangulo eh chamado a funcao AnalisaPessoas que reporta o id dos circulos contidos no retangulo atual
//Funcao nao retorna nada!
void AnalisaEdificios(NohKD node1,NohKD node2,char txt[],int tipo);

//Funcao recebe um noh para os circulos e um noh para os retangulos, coordenadas x,y,xR,yR e altura, um inteiro tipo(0 - 1) e o nome do arquivo .txt
//Percorre recursivamente a arvore dos circulos, reporta o id dos circulos caso tipo seja 0, que estiverem dentro do retangulo informado no parametro
//Quando encontrado um circulo interno ao retangulo eh incrementado o campo->quantidade do noh do retangulo
//Funcao nao retorna nada!
void AnalisaPessoas(NohKD nod,NohKD node2,double x,double y,double xR,double yR,double altura,char txt[],int tipo);

//Funcao recebe um noh, nome do arquivo .svg,um inteiro fg e um inteiro tipo(0 e 1)
//Percorre a arvore recursivamente imprimindo no svg a sua informacao, se tipo = 0 e fg=0 sao printados os retangulos, senao sao printados circulos
//Funcao nao retorna nada!
void SvgFinalKD(NohKD nod,char nomeSvg[],int tipo,int fg);

//Funcao recebe um noh, ponteiro inteiro quantidade, ponteiro double radiacao, double radiometeoro e um inteiro tipo(1 e 2)
//Percorre a arvore recursivamente, calculando a radiacao dos circulos caso tipo=2 ou calcula a radiacao atual caso tipo=1
//Funcao nao retorna nada!
void CalculaRadiacao(NohKD nod,int *Quantidade,double *Radiacao,double RadioMeteoro,int tipo);

//Funcao recebe um noh e um double radiacao
//Percorre a arvore recursivamente, zerando o campo quantidade dos nohs e incrementa o campo radiacao com a radiacao passada
//Funcao nao retorna nada!
void InicializaVar(NohKD nod,double radio);

//Funcao recebe um noh, ponteiro int Qtd e coordenadas double x,y
//Percorre a arvore recursivamente, verficando se o ponto x,y eh interno aos retangulos dos nohs
//Funcao nao retorna nada!
void VerificaPonto(NohKD nod,int *Qtd,double x,double y);

//Funcao recebe a arvore binaria e um noh da arvoreKD
//Percorre a arvore recursivamente, dividindo os retangulos em 4 segmentos e inserindo os segmentos na arvore binaria
//Funcao nao retorna nada!
void DivideRetangulos(Arvore Bina,NohKD nod);

//Funcao recebe a arvore binaria, um noh da arvoreKD, double x,y, radiacaototal, ponteiro pra double e um inteiro tipo(0-1)
//Percorre a arvore recursivamente, tipo=0 verifica se o circulo pertence aos poligonos de sombra, entao eh calculado a radiacao
//Tipo=1 verifica se o ponto x,y informado eh interno de algum poligono e calcula a radiacao
//Funcao nao retorna nada!
void RadiacaoX_Y(Arvore Binaria,NohKD nod,double x,double y,double RadioTotal,double *radiacao,int tipo);

#endif
