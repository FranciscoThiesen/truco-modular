#if ! defined( BARALHO_ )
#define BARALHO_

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

typedef struct carta * BAR_tppCarta;


/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/
   typedef enum {
		 BAR_CondRetOK,
               /* Concluiu corretamente */

         BAR_CondRetBaralhoVazio,
               /* O baralho não contém cartas */

         BAR_CondRetFaltouMemoria
		       /* Faltou memória para alocação */

   } BAR_tpCondRet ;

   

   /***********************************************************************
*
*  $FC Função: BAR_CriaNovoBaralhoEmbaralhado
*
*  $ED Descrição da função
*     Cria um ponteiro para o baralho , sendo que este baralho é embaralhado na sua criação.
*
*  $EP Parâmetros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho embaralhado.
*
*     Se ocorreu erro de falta de memória , é retornado o valor NULL.
*
***********************************************************************/

   LIS_tppLista BAR_CriaNovoBaralhoEmbaralhado();

   /***********************************************************************
*
*  $FC Função: BAR_PegaCartaDoTopo
*
*  $ED Descrição da função
*     Uma carta é tirada do topo do baralho , sendo o ponteiro dela retornado pela função.
*     O primeiro elemento apontado pela lista do baralho é considerado a carta no topo.
*     A função remove a carta do baralho durante a execução.
*
*  $EP Parâmetros
*     baralho - ponteiro para o baralho.
*	  carta - ponteiro para o tipo carta.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a carta tirada.
*
*     Se ocorreu algum erro, por exemplo falta de memória , o ponteiro da carta será retornado como NULL.
*    
***********************************************************************/

   BAR_tppCarta BAR_PegaCartaDoTopo( LIS_tppLista baralho, BAR_tppCarta carta );

/***********************************************************************
*
*  $FC Função: BAR_DestroiBaralho
*
*  $ED Descrição da função
*     Destrói o baralho por completo.
*
*  $EP Parâmetros
*     baralho - ponteiro para o baralho. 
*
*  $FV Valor retornado
*     Se executou corretamente retorna BAR_CondRetOK.
*     Se o baralho veio já vazio , retorna BAR_CondRetBaralhoVazio.
*     Se teve falta de memória durante a execução , retorna BAR_CondRetFaltouMemoria.
*
***********************************************************************/
   BAR_tpCondRet BAR_DestroiBaralho( LIS_tppLista baralho );

/***********************************************************************
*
*  $FC Função: BAR_CriaCarta
*
*  $ED Descrição da função
*     Cria umum ponteiro para o tipo carta.

*
*  $EP Parâmetros
*     valor - valor inteiro da carta.
*     naipe - valor inteiro do naipe da carta.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a carta.
*     Se ocorreu algum erro de falta de memória ,a função retorna NULL.
*
***********************************************************************/

   BAR_tppCarta BAR_CriaCarta(int valor, int naipe);

/***********************************************************************
*
*  $FC Função: BAR_ObtemNaipe
*
*  $ED Descrição da função
*     Obtém o naipe da carta recebida pela função.
*
*  $EP Parâmetros
*     Ponteiro para o tipo carta.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o valor inteiro do naipe.
*
*     Se a carta recebida tiver valor NULL , o valor de retorno será -1.
***********************************************************************/

   int BAR_ObtemNaipe(BAR_tppCarta carta);

/***********************************************************************
*
*  $FC Função: BAR_ObtemValor
*
*  $ED Descrição da função
*     Obtém o valor da carta recebida pela função.
*
*  $EP Parâmetros
*     Ponteiro para o tipo carta.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o valor inteiro da carta.
*
*     Se a carta recebida tiver valor NULL , o valor de retorno será -1.
*
***********************************************************************/

   int BAR_ObtemValor(BAR_tppCarta carta);

   #undef BARALHO_EXT

   #else
   #endif