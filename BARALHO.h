#if ! defined( BARALHO_ )
#define BARALHO_

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/






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
		 BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetBaralhoVazio ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         BAR_CondRetNaoAchouCarta ,
               /* N�o encontrou o valor procurado */

         BAR_CondRetFaltouMemoria
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
   LIS_tppLista BAR_CriarBaralho();

   LIS_tppLista BAR_NovoBaralhoEmbaralhado();

   BRL_carta BAR_PegaCartaDoTopo(LIS_tppLista baralho);

   #undef BARALHO_EXT

   #else
   #endif
