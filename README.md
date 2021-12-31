# Projeto T2 - Estrutura de Dados I
*Projeto desenvolvido na disciplina de Estrutura de Dados I, foi utilizado o sistema operacional Windows 7, para o funcionamento do projeto, todos os arquivos.c e arquivos.h são compilados executando o comando make no terminal, então o makefile será executado realizando a compilação de todos os códigos e gerando um executável para o projeto: **progr**, para utilizar o projeto é necessário informar parâmetros de entrada via argumentos pela linha de comando no terminal, cmd ou PowerShell, exemplo:*

### ./progr -e DiretórioEntrada -f nome_arquivo.geo -q SubDiretório/nome_arquivo.qry -o DiretórioSaida
---
*Em resumo o projeto recebe um arquivo .geo que contém coordenadas para geração de retângulos e circulos e um arquivo .qry que contém consultas para serem realizadas com estes dados informados no arquivo .geo, o projeto utiliza as seguintes estruturas de dados: **Arvore Binária**, **Arvore KD** e **Lista Dinâmica**, o projeto gera no diretório de saída arquivos .svg e .txt para mostrar os resultados das consultas realizadas ao longo da execução. Alguns exemplos de consultas são remoções de retângulos, deslocamento de circulos(com animação) para dentro de retângulos de acordo com a menor distância entre eles, calculo de nivel de exposição usando polígonos para saber quando um circulo está atras de alguma "parede"(algum segmento de algum retângulo)*

*No arquivo.geo temos como argumentos:*
- **cc** (Informa a cor de borda do(s) retângulo(s))
- **cp** (Informa a cor de preenchimento do(s) retângulo(s)) e por fim 
- **bc** (Informa a cor de borda do(s) circulo(s))
- **pc** (Informa a cor de preenchimento do(s) circulo(s))
- **r** (Informa as coordenadas e as dimensões de um retângulo)  
- **r** (Informa as coordenadas e o raio de um circulo) 
*Após a leitura do .geo os retângulos informados são inseridos na lista (Dinâmica/Estática) e é gerado um arquivo .svg inicial que contém os retângulos desenhados.*

*No arquivo.qry temos 6 consultas:*
- **dpi** (Informa uma coordenada x,y e o programa removerá todos os retângulos que tiver essa coordenada como ponto interno)
- **dr** (Informa o id de um retângulo e o programa removerá todos os retângulos que estiverem inteiramente contidos neste retângulo que foi informado)
- **fg** (Informa uma região(Coordenadas x,y e o raio) que será usada para determinar quais circulos(pessoas) vão se locomover para o retângulo(Edificio) mais próximo)
- **im** (Informa as coordenadas de um circulo(Meteoro) e sua radiação, o programa vai calcular o raio de acordo com a radiação e vai atualizar a radiação de todos circulos presentes no programa, circulos que forem internos a retângulos recebem menos radiação)
- **t30** (Informa para o programa que decorreram 30 minutos, todos os circulos que possuirem radiação maior que 8000 serão eliminados da execução e sua posição será marcada com um circulo com uma cruz branca)
- **nve** (Informa coordenadas x,y, o programa vai calcular o nível de exposição à radiação nesse ponto informado)

### Resumo dos Parâmetros do programa:
|  Argumento  | Opcional  |    Descrição   |
| :---         |     :---:      |          ---: |
| -e diretórioEntrada   | Sim     | Informa o caminho para o diretório de entrada(Caso exista) que contém os arquivos de entrada do programa    |
| -f nome_arquivo.geo    | Não      | Informa o nome do arquivo.geo que contém os dados iniciais para execução do programa      |
| -q Subdir/nome_arquivo.qry   | Sim    | Informa o subdiretório(Caso esteja em um) e o nome do arquivo.qry que contém os parâmetros de consulta para ser utilizado com um arquivo.geo informado posteriormente    |
| -o diretórioSaída   | Não     | Informa o caminho para o diretório de saída que será usado para armazenas os arquivos gerados ao longo da execução do programa    |



