#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

void LeituraGeo(ArvoreKD arv1,ArvoreKD arv2, char* bed,char* nomeArq,char* dirSaida,int *nx)
{
    char *pathFile=NULL;
    char *svg=NULL;

    if (bed != NULL)
    {
        pathFile= (char *) malloc((strlen(bed)+strlen(nomeArq)+2) * sizeof(char));
        sprintf(pathFile, "%s/%s", bed, nomeArq);
    }else//Se for nulo
        {
            pathFile= (char *) malloc((strlen(nomeArq)+1)*sizeof(char));
            strcpy(pathFile,nomeArq);//Se nao tiver o -e, vai ser copiado pra pathFile somente o nome do geo, ja que vai estar no mesmo diretorio
        }

    FILE* ArqGeo = fopen(pathFile, "r");
    if(ArqGeo == NULL)
    {
        printf("Nao foi possivel abrir o geo!\n");
        return;
    }
    char copy_linha[150];
    char linha[150];
    char lixo[3];//Nessa variavel vai o inicio dos comandos, como r,cc,cp

    strtok(nomeArq, ".");//Formata o nome do Geo, tirando o .geo para inserir no arquivo svg inicial

    svg= (char *) malloc((strlen(dirSaida)+strlen(nomeArq)+6) * sizeof(char));//6-> 5 por causa do / .svg + 1 do /0
    sprintf(svg, "%s/%s.svg",dirSaida,nomeArq);//Vai copiar pra svg o diretoriosaida /nome do geo.svg
    iniciaSvg(svg);
    
    char ID[70];
    char CorPrenche[30];
    char CorBord[30];
    char CorBordaCirc[30];
    char CorPreenCirc[30];
    double Px;
    double Py;
    double Largu;
    double Altu;
    double Raio;   

    //é copiado pra linha cada linha do geo, ate o gets ser nulo
    printf("\nRealizando leitura do .geo . . .");
    while (fgets(linha, sizeof(linha), ArqGeo) != NULL)//varre o arquivo linha por linha
    {
        sprintf(copy_linha, "%s", linha);//copia pra cpoy_linha o conteudo da linha lida

        if (strcmp(strtok(linha, " "), "cc") == 0)//separa a linha no espaco e compara o comando
        { 
            //a parte do strtok procura na linha pelo primeiro espaco em branco
            //Depois compara pra ver se eh cc
            sscanf(copy_linha, "%s %s", lixo, CorBord);//pra lixo vai a parte do comando como cc 
            
            if(strcmp(CorBord,"@")==0)//se o caractere de cor for @ indica que nao eh pra ter cor!
                strcpy(CorBord,"none"); //eh copiado pra variavel corBord none, no svg quando tem none nao eh feito colorimento 
        }

        if (strcmp(strtok(linha, " "), "bc") == 0)//separa a linha no espaco e compara o comando
        { 
            //a parte do strtok procura na linha pelo primeiro espaco em branco
            //Depois compara pra ver se eh bc
            sscanf(copy_linha, "%s %s", lixo, CorBordaCirc);//pra lixo vai a parte do comando como bc 
            
            if(strcmp(CorBordaCirc,"@")==0)//se o caractere de cor for @ indica que nao eh pra ter cor!
                strcpy(CorBordaCirc,"none"); //eh copiado pra variavel corBord none, no svg quando tem none nao eh feito colorimento 
        }

        if (strcmp(strtok(linha, " "), "pc") == 0)//separa a linha no espaco e compara o comando
        { 
            //a parte do strtok procura na linha pelo primeiro espaco em branco
            //Depois compara pra ver se eh pc
            sscanf(copy_linha, "%s %s", lixo, CorPreenCirc);//pra lixo vai a parte do comando como pc 
            
            if(strcmp(CorPreenCirc,"@")==0)//se o caractere de cor for @ indica que nao eh pra ter cor!
                strcpy(CorPreenCirc,"none"); //eh copiado pra variavel corBord none, no svg quando tem none nao eh feito colorimento 
        }

        if (strcmp(strtok(linha, " "), "cp") == 0)
        {
            sscanf(copy_linha, "%s %s", lixo, CorPrenche);
            
            if(strcmp(CorPrenche,"@")==0)//se o caractere de cor for @ indica que nao eh pra ter cor!
                strcpy(CorPrenche,"none");
        }

        if (strcmp(strtok(linha, " "), "r") == 0)
        {
            sscanf(copy_linha, "%s %s %lf %lf %lf %lf",lixo, ID, &Px, &Py, &Largu, &Altu);
            criaRetangulo(Largu, Altu, Px, Py, CorBord, CorPrenche, svg);//Cria o retangulo e seus parametros no svg
            InsereKD(arv2,ID,Px,Py,0,Largu,Altu,CorPrenche,CorBord);      
        }

        if (strcmp(strtok(linha, " "), "c") == 0)
        {
            sscanf(copy_linha, "%s %s %lf %lf %lf",lixo, ID, &Px, &Py, &Raio);
            CriaPontinho(Px,Py,Raio,CorBordaCirc,CorPreenCirc,svg);
            InsereKD(arv1,ID,Px,Py,Raio,0,0,CorPreenCirc,CorBordaCirc);//os 0 sao largura e altura    
        }
    }
    TextoSvg(-2.0,-4.0,"Pedro Eduardo Garbossa de Almeida",svg);
    finalizaSvg(svg);//finaliza o svg inicial
    fclose(ArqGeo);//Fecha o geo, apos inserir na lista escolhida todos os retangulos
    free(svg);//free do nome do svg
    free(pathFile);//free do path
    printf("\nVariaveis liberadas, saiu do geo!");
}

void LeituraQry(ArvoreKD arv1,ArvoreKD arv2,Lista dinamica,char* DiretorioEnt,char* nomeQry,char* diretSaida,char* TxtSaida,char svg[])
{
    char* pathQry=NULL;
    if (DiretorioEnt != NULL)
    {
        pathQry= (char *) malloc((strlen(nomeQry)+strlen(DiretorioEnt)+2) * sizeof(char));//2-> 1 pro / e 1 pro \0
        sprintf(pathQry, "%s/%s", DiretorioEnt, nomeQry);//Insere uma / entre o diretorio e o nome do qry 
    }
    else
        {
            pathQry= (char *) malloc((strlen(nomeQry)+1)*sizeof(char));
            strcpy(pathQry,nomeQry);//Se nao tiver o -e, vai ser copiado pra pathQry somente o nome do qry, ja que vai estar no mesmo diretorio
        }
        
    //arv2 eh retangulos, arv1 eh circulos
    FILE* ArqQry = fopen(pathQry, "r");
    if(ArqQry == NULL)
    {
        printf("Nao foi possivel abrir o Qry!\n");
        return;
    }
    char CopiaLinha[150];
    char linha[150];
    char lixo[4];//Nessa variavel vai o inicio dos comandos, como dr,t30, etc...

    //Variaveis do QRY
    char IDretan[70];
    char Radi[15];
    char* Exposicao;
    double Pontox,Pontoy,Raio,s,RadiacaoTotal=0.0,radiacao=0;
    double X=0,Y=0,X2=0,Y2=0;
    int Qtd,fg=0,first,im=0,d=0,ent=0,T30=0;
    NohKD node1,node2;
    Arvore Binaria= CreateTree();//cria a arvore binaria
    Arvore Binaria2=CreateTree();;//cria a arovre binaria que armazenara os poligonos
    Noh NodeBinaria;

    node2=GetFirstKD(arv2);
    CoordenadasBounding(node2,&X,&Y,&X2,&Y2);//vai pegar as menores coordenadas de X e Y e as maiores de X2 e Y2

    node1=GetFirstKD(arv1);
    CoordenadasBounding(node1,&X,&Y,&X2,&Y2);//vai pegar as menores coordenadas de X e Y em relacao aos circulos assim como as maiores X2,Y2
    criaBoundingBox(X,Y,X2,Y2,"red",svg);//cria a bounding box em volta de todos elementos

    first=0;
    printf("\nRealizando leitura do .qry . . .");
    while (fgets(linha, sizeof(linha), ArqQry) != NULL)//varre o arquivo linha por linha
    {
        sprintf(CopiaLinha, "%s", linha);//Copia tudo da linha pro CopiaLinha

        if (strcmp(strtok(linha, " "), "dpi") == 0)//-> dpi = remove
        {
            sscanf(CopiaLinha, "%s %lf %lf",lixo, &Pontox, &Pontoy);
            node2=GetFirstKD(arv2);
            Dpi(node2,Pontox,Pontoy,TxtSaida);

            node2=GetFirstKD(arv2);
            PercorreKD(arv2,node2,0,svg,TxtSaida);
    
            d=1;
            ent=d;
        }

        if (strcmp(strtok(linha, " "), "dr") == 0)//-> dr = remove
        {
            sscanf(CopiaLinha, "%s %s ",lixo, IDretan);

            dr(arv2,node2,0,0,0,0,IDretan,TxtSaida,0);

            node2=GetFirstKD(arv2);
            PercorreKD(arv2,node2,0,svg,TxtSaida);
            d=1;
            ent=d;
        }

        if (strcmp(strtok(linha, " "), "fg") == 0)
        {
            sscanf(CopiaLinha, "%s %lf %lf %lf ",lixo, &Pontox, &Pontoy, &Raio);
            criaCircVazio(Pontox,Pontoy,Raio,"red",svg);//svg
            
            node1=GetFirstKD(arv1);
            node2=GetFirstKD(arv2);
            Fg(node1,node2,Pontox,Pontoy,Raio,svg);

            if(first==0)
            {
                node2=GetFirstKD(arv2);
                SvgFinalKD(node2,svg,0,fg);//printa os retangulos inicialmente
            }
            fg=1;
        }

        if (strcmp(strtok(linha, " "), "im") == 0)
        {
            sscanf(CopiaLinha, "%s %lf %lf %lf ",lixo, &Pontox, &Pontoy, &s);
            RadiacaoTotal=RadiacaoTotal+s;//radiacao eh somada no valor da radiacao total da cidade
            Raio=s/5.0;//raio do circulo cinza que vai no svg

            Qtd=0;
            if((first==0)||(ent==1))//so vai ser acessado quando houver o primeiro comando im, se houver outros comandos im nao entrara aqui
            {
                ent=0;
                if(d==0)
                {
                    node2=GetFirstKD(arv2);
                    SvgFinalKD(node2,svg,0,fg);//printa os retangulos inicialmente
                }
                node2=GetFirstKD(arv2);
                DivideRetangulos(Binaria,node2);//percorre a arvore dos retangulos armazenando os segmentos na arvore binaria
            }

            if(d!=1)
            {
                CriaPontinho(Pontox,Pontoy,Raio,"darkgrey","darkgrey",svg);//svg
                TextoSvg(Pontox,Pontoy,"#",svg);//cria uma hashtag no svg no ponto em que o meteoro caiu - svg
            }else
                insert(dinamica,"id","darkgrey","darkgrey",Pontox,Pontoy,Raio,0);//se houve consulta dr ou dpi eh inserido na lista os meteoros pra pintar no svg posteriormente 
            
            if(EstaVazia(arv1)==0)//se a arvore dos circulos nao esta vazia
            {
                node1=GetFirstKD(arv1);
                InicializaVar(node1,s);//quantidade de paredes dos circulos sao zeradas a cada chamada   
            }
            node2=GetFirstKD(arv2);
            VerificaPonto(node2,&Qtd,Pontox,Pontoy);//verifica se o meteoro eh interno a algum edificio

            if(Qtd==0)//meteoro nao caiu dentro de predio
            {
                CriaPoligonos(Binaria,Binaria2,Pontox,Pontoy,X,Y,X2,Y2,RadiacaoTotal);//cria os poligonos pros segmentos pro meteoro 

                if(EstaVazia(arv1)==0)
                {
                    node1=GetFirstKD(arv1);
                    RadiacaoX_Y(Binaria2,node1,0.0,0.0,RadiacaoTotal,&radiacao,0);//percorre a arvore de circulos verificando quais pertencem a algum poligono     
                }
                
            }else
                {
                    if(EstaVazia(arv1)==0)
                    {
                        node1=GetFirstKD(arv1);
                        CalculaRadiacao(node1,&Qtd,&radiacao,RadiacaoTotal,2);    
                    } 
                }
            im=1;//indica que houve consulta im
        }

        if ((strcmp(linha,"t30") == 0) || (strcmp(linha, "t30\n") == 0))//por nao ter argumento analisamos pra ver se nao teve pula linha
        {
            sscanf(CopiaLinha, "%s ",lixo);

            node1=GetFirstKD(arv1);
            t30(arv1,node1,TxtSaida,svg);
            T30=1;
        }

        if (strcmp(strtok(linha, " "), "nve") == 0)
        {
            sscanf(CopiaLinha, "%s %lf %lf",lixo,&Pontox,&Pontoy);
        
            Qtd=0;
            radiacao=0;
            node2=GetFirstKD(arv2);
            VerificaPonto(node2,&Qtd,Pontox,Pontoy);//verifica se o ponto esta dentro de algum edificio
            if(Qtd==0)
            {
                node1=GetFirstKD(arv1);
                RadiacaoX_Y(Binaria2,node1,Pontox,Pontoy,RadiacaoTotal,&radiacao,1);
            }else
                CalculaRadiacao(NULL,&Qtd,&radiacao,RadiacaoTotal,1);//calcula a radiacao dado a quantidade de paredes que o ponto x,y tem
            
            Exposicao=CodigoExposicao(radiacao);//atribui a cor resultante a string exposicao
            criaRetangulo(4.0,4.0,Pontox,Pontoy,Exposicao,Exposicao,svg);//cria retangulo pequeno na cor da exposicao no ponto x,y -svg
            sprintf(Radi,"%lf",radiacao);//copia o valor da radiacao pra variavel char Radi
            TextoSvg(Pontox,Pontoy,Radi,svg);
            SaidaNve(TxtSaida,Pontox,Pontoy,radiacao);//saida txt
        }
        first++;
    }//Fim leitura .qry 
    if(fg==1)
    {
        node1=GetFirstKD(arv1);
        node2=GetFirstKD(arv2);
        AnalisaEdificios(node1,node2,TxtSaida,0);//percorre a arvore dos retangulos atribuindo a quantidade de pessoas dentro dele

        node2=GetFirstKD(arv2);
        SvgFinalKD(node2,svg,0,fg);//printa no svg somente as quantidade de cada retangulo
    }

    if((fg!=1)&&(im!=1))//pois nas consultas im e fg os retangulos sao printados na primeira execucacao da funcao 
    {
        node2=GetFirstKD(arv2);
        SvgFinalKD(node2,svg,0,fg);
    }

    if(d==1)//se houve consulta dpi ou dr os retangulos sao printados apos as consultas
    {
        node2=GetFirstKD(arv2);
        SvgFinalKD(node2,svg,0,fg);

        Qsort(dinamica);//ordena a lista dos meteoros
        SvgQry(dinamica,svg);//caso houve consulta dpi ou dr vai printar as bombas pela lista
    }

    if(im==1)
    {
        if(T30!=1)
        {
            node1=GetFirstKD(arv1);
            PercorreKD(arv1,node1,1,svg,TxtSaida);//atribui a cor dos circulos de acordo com a radiacao      
        }
        //NodeBinaria=GetFirstTree(Binaria2);
        //PercorreBinaria(NodeBinaria,svg);//printar poligonos no svg
    
        NodeBinaria=GetFirstTree(Binaria2);
        Libera(NodeBinaria);
        NodeBinaria=GetFirstTree(Binaria);
        Libera(NodeBinaria);
        printf("\nArvores dos segmentos e poligonos liberadas!");
    }
    
    node1=GetFirstKD(arv1);
    SvgFinalKD(node1,svg,1,fg);
    TextoSvg(X2+2.0,Y2,"Pedro Eduardo Garbossa de Almeida",svg);//printa meu nome no svg de saida

    fclose(ArqQry);//Fecha o qry, apos ler e realizar as consultas
    free(pathQry);//free no path do qry
    free(Binaria);
    free(Binaria2);
    printf("\nVariaveis liberadas, saiu do qry!");
}