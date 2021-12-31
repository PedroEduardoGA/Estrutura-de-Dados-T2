#include <stdio.h>
#include "svg.h"

void iniciaSvg(char arq[])//recebe nome do svg
{
    FILE *arquivo;
    
    arquivo = fopen(arq, "w");
    if (arquivo == NULL)
    { 
        printf("Nao foi possivel criar o arquivo svg!");
        return;
    }
    fprintf(arquivo, "<svg xmlns='http://www.w3.org/2000/svg'>");//Link para visualizacao na web
    
    fclose(arquivo);
}

void finalizaSvg(char arq[])//recebe nome do svg
{
	FILE* arquivo;
	
    arquivo = fopen(arq, "a");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel Abrir o arquivo svg para finaliza-lo!");
        return;
    }
    fseek(arquivo, 0, SEEK_END);//leva o ponteiro pro final do arquivo
    fprintf(arquivo, "\n</svg>");
    
    fclose(arquivo);
}

void criaLinha(double x1, double y1, double x2, double y2, char cor[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg para criacao da linha!");
        return;
	}
	fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s\" />\n", x1, y1, x2, y2, cor);//cria uma linha de x1,y1 ate x2,y2
    fclose(arq);
}

void criaRetangulo(double largura, double altura, double x, double y, char cor1[], char cor2[], char svg[])//Cor2 Preenche
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o o svg pra criar um retangulo!");
        return;
	}
	fprintf(arq, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" />\n", x, y, largura, altura, cor2, cor1);
    fclose(arq);
}

void CriaPontinho(double x,double y, double raio,char Contorno[],char Preenchimento[],char svg[])
{   
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg pra criar um circulo!");
        return;
	}
	fprintf(arq, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\"/>\n",x,y,raio,Contorno,Preenchimento);
    fclose(arq);
}

void CriaCirculoRIP(double x,double y, double raio,char svg[])
{
    FILE *arq;
    double x1,y1,x2,y2,var;

    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg pra criar um circulo!");
        return;
	}
	fprintf(arq, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>\n",x,y,raio);

    //ContasPraDesenhar a Cruz
    var=raio/2.0;
    x1=x-var;
    x2=x+var;
    y2=y1=y-0.34;
    fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:white\" />\n", x1, y1, x2, y2);//criada a linha horizontal da cruz
    
    var=raio/2.0;
    y1=y-var;
    y2=y+var;
    x2=x1=x;
    fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:white\" />\n", x1, y1, x2, y2);//cria a linha vertical da cruz
    
    fclose(arq);
}

void criaBoundingBox(double x, double y,double largura, double altura, char cor1[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg para criar a bounding box!");
        return;
	}
	fprintf(arq, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"%s\" fill-opacity=\"0\" stroke-width=\"2\" stroke-dasharray=\"5\" />\n",x, y, largura, altura, cor1);
    fclose(arq);
}

void TextoSvg(double x, double y, char texto[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o svg pra criacao de texto!");
    }
    fprintf(arq, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"black\">%s</text>", x, y, texto);
    fclose(arq);
}

void LinhaTracejada(double x1, double y1, double x2, double y2, char cor[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo de saida");
        return;
	}
	fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-dasharray=\"5,5\"/>\n", x1, y1, x2, y2, cor);
    fclose(arq);
}

void Animacao(double x1,double x2,double y1,double y2,double raio,char CorFILL[],char CorBord[],char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo de saida");
        return;
	}
    fprintf(arq, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: #000000; stroke-width:1; stroke-dasharray:2 2\"/>",x1,y1,x2,y2);
    fprintf(arq,"<circle cx=\"0\" cy=\"0\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"8s\" repeatCount=\"indefinite\" /> </circle>\n",raio,CorBord,CorFILL,x1,y1,x2,y2);
    
    fclose(arq);
}

void criaCircVazio(double x, double y,double rai, char cor1[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg para criar a bounding box!");
        return;
	}
	fprintf(arq, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"none\" stroke=\"%s\" fill-opacity=\"0\" stroke-width=\"2\" stroke-dasharray=\"5\" />\n",x, y,rai,cor1);
    
    fclose(arq);
}

void CriaPoligono(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,char cor[],char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg para criar o poligono!");
        return;
	}
	fprintf(arq,"\t<polygon points=\"%lf,%lf %lf,%lf %lf,%lf %lf,%lf\" fill=\"none\" stroke=\"%s\"/>\n",x1,y1,x2,y2,x3,y3,x4,y4,cor);
    
    fclose(arq);
}