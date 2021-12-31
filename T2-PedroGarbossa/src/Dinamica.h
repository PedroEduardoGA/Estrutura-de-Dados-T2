#ifndef _DINAMICA_H
#define _DINAMICA_H
//Modulo responsavel pela manipulacao da lista dinamica

typedef void* No; //void pointer
typedef void* Lista; //void pointer

//Cria uma lista vazia, retorna uma lista vazia, nao recebe nada como parametro!
Lista Create();

//Insere os parametros dos retangulos, necessita de uma lista para insercao dos parametros, retorna a lista com as informacoes!
void insert(Lista l, char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura);

//Imprimi todos elementos da lista, precisa de uma lista com pelo menos 1 elemento, nao retorna nada!
void print(Lista l);

//Desaloca a memoria da lista, recebe uma lista, nao retorna nada!
void liberalist(Lista l);

//Remove o elemento com id informado, precisa de uma lista e um id, nao retorna nada!
void RemoveElemento(Lista l, char id[]);

//Insere os parametros, apos tal posicao, necessita de uma lista e as informacoes que serao inseridas, e uma posicao para ser 
//inserido apos ela, nao retorna nada!
void InsereAfter(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i);

//Insere os parametros, anteriormente tal posicao, necessita de uma lista e as informacoes que serao inseridas, e uma posicao para 
//ser inserido anterior a ela, nao retorna nada!
void InsereBefore(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i);

//Pega o ultimo noh da lista, recebe uma lista, retorna o ultimo noh da lista, caso a lista esteja vazia, retorna NULL!
No GetLast(Lista L);

//Pega o primeiro noh da lista, recebe uma lista, retorna o primeiro noh da lista caso a lista esteja vazia, retorna NULL!
No GetFirst(Lista L);

//Pega o noh posterior a posicao informada da lista, recebe uma lista, retorna o noh posterior da posicao, caso a posicao seja maior
//que o tamanho da lista retorna NULL, caso a lista esteja vazia, retorna NULL!
No GetNext(Lista L,int pos);

//Pega o noh anterior a posicao informada da lista, recebe uma lista, retorna o noh anterior da posicao, caso a posicao seja maior
//que o tamanho da lista retorna NULL, caso posicao seja 0 retorna NULL, pois o eh o elemento anterior do primeiro noh, caso a lista 
//esteja vazia, retorna NULL!
No GetPrevious(Lista L, int pos);

//Pega o noh do elemento com Id igual ao informado, recebe uma lista e um Id, retorna o noh com Id informado, caso Id nao exista na lista
//retorna NULL, caso a lista esteja vazia, retorna NULL!
No GetElemento(Lista L,char IdRect[70]);

//Ordena a lista passada, recebe a lista somente
//Nao retorna nada, caso a lista esteja vazia a funcao eh interrompida!
void Qsort(Lista L);

//Insere no svg os elementos contidos na lista, recebe a lista e o nome do arquivo .svg
//Funcao nao retorna nada, caso nao seja possivel abrir o arquivo .svg eh informado na tela e a funcao eh interrompida!
void SvgQry(Lista L, char nomeSvG[]);

#endif
