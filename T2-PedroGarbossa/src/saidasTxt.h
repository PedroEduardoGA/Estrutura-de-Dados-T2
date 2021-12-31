#ifndef _SAIDASTXT_H
#define _SAIDASTXT_H
//Modulo responsavel por trabalhar com abertura, escrita, leitura e fechamento de arquivos .txt

/*Cria o arquivo TXT caso haja consultas, recebe o nome do arquivo TXT, nao retorna nada! Caso nao seja possivel criar o arquivo, retornara NULL!*/
void CriaArquivo(char arquivo[]);

/*Cria uma linha no arquivo TXT, reportando que o ID nao existe na lista, recebe o nome do arquivo TXT, um ID e o tipoconsulta, 
nao retorna nada!Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void IdInexiste(char arquivo[],char IDE[],char TipoConsulta[]);

/*Cria uma linha no arquivo TXT, reportando que o retangulo ID foi removido, recebe o nome do arquivo TXT, um ID e o tipo, nao retorna nada!
Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void RemoveuRetan(char arquivo[],char IDE[],char Tipo[]);

/*Cria uma linha no arquivo TXT, reportando o status do circulo ID, recebe o nome do arquivo TXT, um ID, char Consulta e o tipo, nao retorna nada!
Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void SaidaIm(char arquivo[],char IDE[],char Consulta[],int Tipo);

/*Cria uma linha no arquivo TXT, reportando o ID do circulo, recebe o nome do arquivo TXT e um ID, nao retorna nada!
Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void FgCirculo(char arquivo[],char Id[]);

/*Cria uma linha no arquivo TXT, reportando o ID do retangulo, recebe o nome do arquivo TXT e um ID, nao retorna nada!
Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void FgRetan(char arquivo[],char Id[]);

/*Cria uma linha no arquivo TXT, reportando o nivel de exposicao no ponto x,y, recebe o nome do arquivo TXT, double x e y e o nivel de radiacao,
nao retorna nada! Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void SaidaNve(char arquivo[],double x,double y,double nivel);

#endif
