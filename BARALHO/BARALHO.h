#if ! defined( BARALHO_ )
#define BARALHO_

#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif



/***** Declarações exportadas pelo módulo *****/

typedef struct carta 
{
	int naipe;
	int valor;
} BRL_carta;

typedef struct carta * BAR_tppCarta;




/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
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
               /* A lista não contém elementos */

         BAR_CondRetNaoObteveCarta,
               /* Não encontrou o valor procurado */

         BAR_CondRetFaltouMemoria,

		 BAR_CartaNula
               /* Faltou memória ao tentar criar um elemento de lista */

   } BAR_tpCondRet ;

   /***********************************************************************
*
*  $FC Função: BAR  &Criar baralho
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro será utilizado pelas funções do BARALHO.c que lidam com manipulação de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/
   BAR_tpCondRet BAR_InsereCartaNoBaralho( BRL_carta* carta, LIS_tppLista baralho );

   /***********************************************************************
*
*  $FC Função: BAR  &Criar baralho
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro será utilizado pelas funções do BARALHO.c que lidam com manipulação de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista BAR_NovoBaralhoEmbaralhado();

   /***********************************************************************
*
*  $FC Função: BAR  &Criar baralho
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro será utilizado pelas funções do BARALHO.c que lidam com manipulação de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   BAR_tpCondRet BAR_PegaCartaDoTopo( LIS_tppLista baralho,BAR_tppCarta carta );

/***********************************************************************
*
*  $FC Função: BAR  &Criar baralho
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     Nenhum.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o baralho.
*     Este ponteiro será utilizado pelas funções do BARALHO.c que lidam com manipulação de cartas.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/
   void BAR_DestruirBaralho( LIS_tppLista baralho );

   #undef BARALHO_EXT

   #else
   #endif