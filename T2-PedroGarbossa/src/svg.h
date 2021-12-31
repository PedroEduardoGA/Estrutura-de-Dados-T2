#ifndef __SVG_H
#define __SVG_H
//Modulo responsavel por trabalhar com abertura, leitura e fechamento dos arquivos com extensao .svg

/*Cria a tag inicial de um svg para o arquivo com o nome recebido, recebe o nome do SVG, nao retorna nada! Caso nao seja possivel criar o 
arquivo retorna NULL!*/
void iniciaSvg(char arq[]);

/*Cria a tag final de um svg para o arquivo com o nome recebido, recebe o nome do SVG, nao retorna nada! Caso nao seja possivel abrir o 
arquivo retorna NULL!*/
void finalizaSvg(char arq[]);

/*Cria uma linha entre dois pontos com a cor selecionada no arquivo svg, recebe coordenadas x,y, uma cor e o nome do SVG, nao retorna nada! 
Caso nao seja possivel abrir o arquivo retorna NULL!*/
void criaLinha(double x1, double y1, double x2, double y2, char cor[], char svg[]);

/*Cria um retangulo a partir do ponto x y e da altura e largura, no arquivo svg, recebe coordenadas x,y, duas cores e o nome do SVG, 
nao retorna nada! Caso nao seja possivel abrir o arquivo retorna NULL!*/
void criaRetangulo(double largura, double altura, double x, double y, char cor1[], char cor2[], char svg[]);

/*Cria uma boundingBox a partir do ponto x,y e da altura e largura fornecida, recebe os parametros e cria a bounding box
com contorno tracejado, da cor informada, nao retorna nada! Caso nao seja possivel abrir o arquivo retorna NULL!*/
void criaBoundingBox(double x, double y,double largura, double altura, char cor1[], char svg[]);

/*Cria um circulo preto com uma cruz interna no ponto x,y, recebe double x,y,raio e o nome do arquivo svg
Funcao nao retorna nada! Caso nao seja possivel abrir o arquivo retorna NULL!*/
void CriaCirculoRIP(double x,double y, double raio,char svg[]);

/*Cria um circulo no SVG, recebe coordenadas x e y, raio, cores de preenchimento e de contorno, e o nome do SVG, funcao nao retorna nada!
Caso nao seja possivel abrir o arquivo retorna NULL!*/
void CriaPontinho(double x,double y, double raio,char Contorno[],char Preenchimento[],char svg[]);

/*Cria um texto a partir do ponto x e y, recebe o texto, x,y e o nome do svg, no arquivo svg escreve o texto passado! Caso 
nao seja possivel abrir o arquivo retorna NULL! Funcao nao retorna nada!*/
void TextoSvg(double x, double y, char texto[], char svg[]);

/*Insere uma linha traceja nas coordenadas desejada, recebe o nome do svg e as coordenada x1,y1,x2,y2, cor do traço, funcao nao retorna nada! 
Caso nao consiga  abrir o arquivo svg retornara NULL*/
void LinhaTracejada(double x1, double y1, double x2, double y2, char cor[], char svg[]);

/*Cria uma animacao de um circulo do ponto x1,y1 ate x2,y2 com raio e cores informadas, recebe as coordenadas x1,y1,x2,y2, o raio, as cores
de preenchimento e de borda e o nome do arquivo svg, funcao nao retorna nada! Caso nao consiga  abrir o arquivo svg retornara NULL*/
void Animacao(double x1,double x2,double y1,double y2,double raio,char CorFILL[],char CorBord[],char svg[]);

/*Cria um circulo sem preenchimento com contorno tracejado no ponto x,y com o raio e cor informados, recebe coordenada x,y, raio, a cor de contorno e o nome do arquivo
svg, funcao nao retorna nada! Caso nao seja possivel abrir o arquivo retorna NULL!*/
void criaCircVazio(double x, double y,double rai, char cor1[], char svg[]);

/*Cria um poligono no svg, recebe 4 coordenadas x,y, a cor do tracejado e o nome do arquivo .svg funcao nao retorna nada! 
Caso nao seja possivel abrir o arquivo retorna NULL!*/
void CriaPoligono(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,char cor[],char svg[]);

#endif