#if ! defined( BARALHO_ )
#define BARALHO_

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

#include "LISTA.H"

/***** Declara��es exportadas pelo m�dulo *****/

typedef struct carta * BAR_tppCarta;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/
   typedef enum {
		 BAR_CondRetOK,
               /* Concluiu corretamente */

         BAR_CondRetBaralhoVazio,
               /* A lista n�o cont�m elementos */

         BAR_CondRetNaoObteveCarta,
               /* N�o encontrou o valor procurado */

         BAR_CondRetFaltouMemoria,

		 BAR_CartaNula
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } BAR_tpCondRet ;

   /***********************************************************************
*
*  $FC Fun��o: BAR  &Criar baralho
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro ser� utilizado pelas fun��es do BARALHO.c que lidam com manipula��o de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/
   BAR_tpCondRet BAR_InsereCartaNoBaralho( BAR_tppCarta carta, LIS_tppLista baralho );

   /***********************************************************************
*
*  $FC Fun��o: BAR  &Criar baralho
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro ser� utilizado pelas fun��es do BARALHO.c que lidam com manipula��o de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista BAR_CriarNovoBaralhoEmbaralhado();

   /***********************************************************************
*
*  $FC Fun��o: BAR  &Criar baralho
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro ser� utilizado pelas fun��es do BARALHO.c que lidam com manipula��o de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   BAR_tppCarta BAR_PegaCartaDoTopo( LIS_tppLista baralho, BAR_tppCarta carta );

/***********************************************************************
*
*  $FC Fun��o: BAR  &Criar baralho
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro ser� utilizado pelas fun��es do BARALHO.c que lidam com manipula��o de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/
   BAR_tpCondRet BAR_DestruirBaralho( LIS_tppLista baralho );

   #undef BARALHO_EXT

   #else
   #endif