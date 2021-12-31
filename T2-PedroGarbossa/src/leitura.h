#ifndef LEITURA_H_
#define LEITURA_H_
#include "Dinamica.h"
#include "ArvoreKD.h"
#include "svg.h"
#include "Extras.h"
#include "ArvoreBinaria.h"
#include "saidasTxt.h"
//Modulo responsavel por trabalhar com abertura, leitura e fechamento dos arquivos .geo e .qry
//Na leituraGeo armazena os dados nas respectivas arvores e cria um svg inicial
//Na leituraQry realiza consultas que produzem saidas .txt e .svg

/* Funcao: LeituraGeo recebe 6 parametros: 
    "arv1" void pointer que uso pra apontar pra uma arvore KD, que uso pra armazenar os circulos!
    "arv2" void pointer que uso pra apontar pra uma arvore KD, que uso pra armazenar os retangulos!
    "bed" eh o diretorio caso informado o -e, entao sera passado pra bed o diretorio de entrada, caso nao seja informado o -e
    bed valera NULL!
    "nomeArq" eh o nome do arquivo geo informado logo apos o -f, caso nome do arquivo seja invalido retorna NULL!
    "dirSaida" eh o diretorio de saida informado apos o -o, diretorio sera usado pra produzir o svg inicial nesse diretorio!
    "*nx" recebe o endereco de uma variavel int que le o numero aproximado de retangulos a serem informados
    A funcao abre o arquivo .geo, le todos comandos e armazena nas arvores os respectivos dados, x,y,cor de preenchimento e cor de borda,
    insere no svg inicial os retangulos e os circulos, svg inicial que sera criado no diretorio de saida com o nome do arquivo geo 
    informado Ex: nomegeo.svg! Caso nao seja possivel abrir o arquivo retorna NULL! Funcao nao retorna nada!*/
void LeituraGeo(ArvoreKD arv1,ArvoreKD arv2, char* bed,char* nomeArq,char* dirSaida,int *nx);

/* Funcao: LeituraQry recebe 8 parametros: 
    "arv1" void pointer que uso pra apontar pra uma arvore KD, onde estao armazenados os circulos!
    "arv2" void pointer que uso pra apontar pra uma arvore KD, onde estao armazenados os retangulos!
    "DiretorioEnt" eh o diretorio caso informado o -e, entao sera passado pra variavel o diretorio de entrada, caso nao seja informado o -e
    DiretorioEnt valera NULL!
    "nomeQry" eh o nome do arquivo qry informado logo apos o -q, caso nome do arquivo seja invalido retorna NULL!
    "diretSaida" eh o diretorio de saida informado apos o -o, diretorio sera usado pra produzir os .txt das consultas nesse diretorio!
    "TxtSaida" recebera o nome do txt formatado como: nomegeo-nomeqry.txt
    "svg" recebera o nome do svg formatado como: nomegeo-nomeqry.svg
    A funcao abre o arquivo .qry, le todos comandos linha por linha e realiza a consulta, dependendo da consulta o efeito muda, algumas
    atualizam os dados das arvores, outras removem, outras inserem, cada consulta produz algum resultado no arquivo txt, no diretorio de 
    saida com o nome Ex: nomegeo-nomeqry.txt! Caso nao seja possivel abrir o arquivo a funcao retorna NULL! A Funcao nao retorna nada!*/
void LeituraQry(ArvoreKD arv1,ArvoreKD arv2,Lista dinamica,char* DiretorioEnt,char* nomeQry,char* diretSaida,char* TxtSaida,char svg[]);

#endif