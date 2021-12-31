#ifndef _ARVOREBINARIA_H
#define _ARVOREBINARIA_H
#include <stdbool.h>
//Modulo responsavel pela manipulacao da Arvore Binaria

typedef void* Arvore;
typedef void* Noh;

//Funcao nao recebe nada como parametro
//Aloca memoria pra uma arvore e cria a mesma
//Funcao retorna uma arvore vazia!
Arvore CreateTree();

//Funcao recebe a arvore, 4 coordenadas x e y, um double radiacao e a cor
//Aloca memoria pra um noh da arvore e insere na arvore de acordo com a coordenada x1
//Funcao nao retorna nada!
void Insere(Arvore t,double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,double radio,char Cor[30]);

//Funcao recebe um noh
//Imprime na tela recursivamente a arvore inteira e as informacoes contidas em cada noh
//Funcao nao retorna nada!
void Imprime(Noh nod);

//Funcao recebe um noh
//Percorre a arvore recursivamente liberando a memoria alocada dos nohs
//Funcao nao retorna nada!
void Libera(Noh nod);

//Funcao recebe a arvore
//Funcao retorna a raiz da arvore!
Noh GetFirstTree(Arvore arv);

//Funcao recebe a arvore e a coordenada x1
//Percorre a arvore em busca do noh que contem a coordenada x1
//Funcao retorna o noh que contem a coordenada x1 igual a coordenada passada como parametro! Se x1 nao for encontrado retorna NULL!
Noh GetNodeTree(Arvore arv,double x1);

//Funcao recebe a arvore e a coordenada x1
//Percorre a arvore em busca do noh que contem a coordenada x1
//Funcao retorna 1 se o noh com a coordenada foi encontrado, retorna 0 se nao foi encontrado!
int ExisteValor(Arvore arv,double x1);

//Funcao recebe a arvore e a coordenada x1
//Percorre a arvore em busca do noh que contem a coordenada x1 e o remove se o mesmo existir
//Funcao nao retorna nada!
void RemoveNoh(Arvore arv,double x1);

//Funcao recebe as arvores binarias, 3 coordenadas x,y, sendo X,Y,X2,Y2 do bounding box e a radiacao
//Chama a analisaSegmentos que vai criar os poligonos de sombra de acordo com as coordenadas x,y
//Funcao nao retorna nada!
void CriaPoligonos(Arvore arv1,Arvore arv2,double x,double y,double X,double Y,double X2,double Y2,double Radio);

//Funcao recebe a arvore binaria, 3 coordenadas x,y, sendo X,Y,X2,Y2 do bounding box e a radiacao
//Percorre recursivamente a arvore criando os poligonos de acordo com a coordenada x,y, atribui a radiacao pro poligono de acordo com a reducao
//Funcao nao retorna nada!
void AnalisaSegmentos(Arvore arv2,Noh nod,double x,double y,double X,double Y,double X2,double Y2,double radio);

//Funcao recebe o noh e o nome do arquivo .svg
//Percorre recursivamente a arvore criando os poligonos no arquivo .svg
//Funcao nao retorna nada!
void PercorreBinaria(Noh nod,char svg[]);

//Funcao recebe o noh, coordena x,y e um ponteiro double Radiacao
//Percorre recursivamente a arvore verificando a quais poligonos o ponto x,y eh interno chamando a funcao PontoInPoligono
//Funcao nao retorna nada!
void Poligonos(Noh nod,double x,double y,double *Radiacao);

//Funcao recebe 2 vetores, sendo um de coordenadas X e outro de coordenas Y, quantidade de cantos e coordenadas x,y
//Verifica se o ponto x,y pertence ao poligono com as coordenadas dos vetores passados
//Funcao retorna um valor booleano, true se o ponto x,y pertence ao poligono ou false caso contrario!
bool PontoInPoligono(double PolyX[],double PolyY[],int Cantos,double x,double y);

#endif
