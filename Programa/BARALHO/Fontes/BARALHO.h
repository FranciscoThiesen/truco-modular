#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*
*  $MCD Módulo de definição: BAR  BARALHO
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Projeto: INF 1301 / Truco
*  Gestor:  DI/PUC-Rio
*  Autores: Arthur Cavalcante Gomes Coelho(acgc)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       acgc   30/04/2018 início desenvolvimento
*
*  $ED Descrição do módulo
*     Cria o elemento carta
*     Implementa baralhos de 40 cartas e embaralhamento.
*     Baralhos são compostos por uma lista de cartas.
*     Embaralha o baralho de 40 cartas aleatoriamente.
*
***************************************************************************/

#include   "LISTA.H"

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um baralho */

typedef struct BAR_tagBaralho * BAR_tppBaralho;

/* Tipo referência para uma carta */

typedef struct BAR_tagCarta * BAR_tppCarta ;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo BARALHO
*
***********************************************************************/

typedef enum {

      BAR_CondRetOK ,
            /* Concluiu corretamente */

      BAR_CondRetListaVazia ,
            /* A lista n�o cont�m elementos */

      BAR_CondRetFaltouMemoria,
            /* Faltou mem�ria ao tentar criar um elemento de lista */

	  BAR_CondRetCartaNaoCriada,
			/* Nao foi possivel criar o ponteiro Carta */

	  BAR_CondRetBaralhoNaoExiste,
			/* Ponteiro para baralho vazio */
	  BAR_CondRetTamanhoErrado
			/* Tamanho da lista de cartas errado */

} BAR_tpCondRet ;



/***********************************************************************
*
*  $FC Função: BAR  &Cria carta
*
*  $ED Descrição da função
*     Cria uma carta.
*	  Uma carta é composta por seu nome, peso e naipe
*
*  $EP Parâmetros
*	  pCarta		- endereço que vai receber a carta a ser criada
*
*
*  $FV Valor retornado
*     BAR_CondRetOK				- se tiver criado a carta com sucesso
*	  BAR_CondRetFaltouMemoria  - se não tiver conseguido alocar memória para a carta
*	  BAR_CondRetCartaNaoCriada - se houver falha na atribuição *pCarta=aux_carta
*
***********************************************************************/
BAR_tpCondRet BAR_CriaCarta(BAR_tppCarta *pCarta,char nome, int peso,char *naipe);


/***********************************************************************
*
*  $FC Função: BAR  &Destruir carta
*
*  $ED Descrição da função
*     Destrói a carta fornecida.
*     Se ocorrer algum erro durante a destruição, o baralho resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     BAR_CondRetOK    - destruiu sem problemas
*
***********************************************************************/
BAR_tpCondRet DestruirCarta(BAR_tppCarta pCarta);


/***********************************************************************
*
*  $FC Função: BAR  &Criar baralho
*
*  $ED Descrição da função
*     Cria um baralho.
*	  Um baralho é composto por um ponteiro para uma cabeça de uma lista com as cartas.
*	  O baralho é criado com todas as 40 cartas que pertencem ao jogo de Truco.
*
*  $EP Parâmetros
*	  pBaralho		- endereço que vai receber o baralho a ser criado
*
*  $FV Valor retornado
*     BAR_CondRetOK				- se tiver criado o baralho com sucesso
*	  BAR_CondRetFaltouMemoria  - se não tiver conseguido alocar memória para o baralho
*	  BAR_CondRetListaVazia - se (*pBaralho)->pCartas é NULL
*
***********************************************************************/
BAR_tpCondRet BAR_CriarBaralho(BAR_tppBaralho *pBaralho);


/***********************************************************************
*
*  $FC Função: BAR  &CriaVetorCartas
*
*  $ED Descrição da função
*     Cria vetor de cartas e preenche-o com as cartas usadas no jogo de truco
*
*  $EP Parâmetros
*	  cartas[]		- vetor que será preenchido pelas cartas
*
*  $FV Valor retornado
*     BAR_CondRetOK				- se tiver criado o vetor com sucesso
*	  BAR_CondRetFaltouMemoria  - se não tiver conseguido alocar memória para a carta
*	  BAR_CondRetCartaNaoCriada - se houver falha na atribuição *pCarta=aux_carta
*
***********************************************************************/
BAR_tpCondRet BAR_CriaVetorCartas(BAR_tppCarta *cartas[]);


/***********************************************************************
*
*  $FC Função: BAR  &Embaralhar
*
*  $ED Descrição da função
*     Embaralha as cartas contidas no baralho em uma ordem aleatória.
*	  Pega as cartas da lista do baralho e distribui em ordem aleatória
*	  em uma nova lista. Depois, troca o ponteiro da lista do baralho.
*
*  $EP Parâmetros
*     pBaralho - ponteiro para o baralho a ser embaralhado
*
*  $FV Valor retornado
*     BAR_CondRetOK				  - embaralhou sem problemas
*	  BAR_CondRetTamanhoErrado	  - tamanho do baralho errado
*	  BAR_CondRetFaltouMemoria	  - faltou memoria para criar a lista nova
*	  BAR_CondRetBaralhoNaoExiste - pBaralho é NULL
*	  BAR_CondRetListaVazia		  - Lista vazia de cartas
*
***********************************************************************/
BAR_tpCondRet BAR_Embaralhar( BAR_tppBaralho pBaralho );


/***********************************************************************
*
*  $FC Função: BAR  &Destruir baralho
*
*  $ED Descrição da função
*     Destrói o baralho fornecido.
*     O parâmetro ponteiro para o baralho não é modificado.
*     Se ocorrer algum erro durante a destruição, o baralho resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     BAR_CondRetOK    - destruiu sem problemas
*
***********************************************************************/
BAR_tpCondRet BAR_DestruirBaralho( BAR_tppBaralho pBaralho );



#undef BARALHO_EXT

/********** Fim do módulo de definição: BAR  BARALHO **********/
#else
#endif
