/***************************************************************************
*  $MCI Módulo de implementação: TBAR Teste baralho de cartas
*
*  Arquivo gerado:              TESTBAR.c
*  Letras identificadoras:      TBAR
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301
*  Autores: Francisco, Gabriel e Roberto
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Baralho.h"

static const char CRIA_CARTA_CMD                     [ ] = "=criacarta";
static const char OBTEM_NAIPE_CMD                    [ ] = "=obtemnaipe";
static const char OBTEM_VALOR_CMD                    [ ] = "=obtemvalor";
static const char CRIA_BARALHO_EMBARALHADO_CMD       [ ] = "=criabaralhoembaralhado";
static const char DESTROI_BARALHO_CMD                [ ] = "=destroibaralho";
static const char RETIRA_TOPO_BARALHO_CMD            [ ] = "=retiratopobaralho";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_CARTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[DIM_VT_LISTA];
BAR_tppCarta   vtCartas[DIM_VT_CARTA];


/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxLista(int inxLista, int Modo);

static int ValidarInxCarta(int inxCarta, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*  $TC Tipo de dados: BAR Descritor da carta
***********************************************************************/
typedef struct BAR_tagCarta
{
	int num;
	int naipe;
} BAR_tpCarta;

/***********************************************************************
*
*  $FC Função: TBAR &Testar baralho
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas e cartas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criacarta                  <inxCarta>   <naipe>        <número>
*     =obtemnaipe                 <inxCarta>   <naipeEsp>
*     =obtemvalor                 <inxCarta>   <valorEsp>
*	  =criabaralhoembaralhado     <inxBaralho> <condRetEsp>
*     =destroibaralho             <inxBaralho> <condRetEsp>
*     =retiratopobaralho          <inxBaralho> <cartaEsp>
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int inxCarta = -1,
		inxCarta2 = -1,
		inxLista = -1,
		inxBaralho = -1,
		numLidos = -1,
		ValEsp = -1,
		CondRetEsp = -1,
		numElem = -1;

	TST_tpCondRet CondRet;

	BAR_tppCarta pCarta;

	/* Testar CriarCarta */
	
	if (strcmp(ComandoTeste, CRIA_CARTA_CMD) == 0)
	{
		int naipe, num;

		numLidos = LER_LerParametros("iii",
			&inxCarta, &naipe, &num);

		if ((numLidos != 3)
			|| (!ValidarInxCarta(inxCarta, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		vtCartas[inxCarta] =
			BAR_CriaCarta(naipe, num);

		return TST_CompararPonteiroNulo(1, vtCartas[inxCarta],
			"Erro em ponteiro de nova lista.");

	} /* fim ativa: Testar CriaCarta */

	/* Testar Obter Naipe */

	else if(strcmp(ComandoTeste, OBTEM_NAIPE_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxCarta, &ValEsp);

		if ((numLidos != 2)
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt( ValEsp ,
                      BAR_ObtemNaipe( vtCartas[ inxCarta ] ) ,
                     "Naipe retornado está errado."   ) ;

	} /* fim ativa: Testar ObtemNaipe */	

	/* Testar Obter Valor */
	else if(strcmp(ComandoTeste, OBTEM_VALOR_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxCarta, &ValEsp);

		if ((numLidos != 2)
			|| (!ValidarInxCarta(inxCarta, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt( ValEsp ,
                      BAR_ObtemValor( vtCartas[ inxCarta ] ) ,
                     "Número retornado está errado."   ) ;

	} /* fim ativa: Testar ObterValor */

	return TST_CondRetNaoConhec;

}
  /*****  Código das funções encapsuladas no módulo  *****/

  /***********************************************************************
  *
  *  $FC Função: TBAR -Validar indice de lista
  *
  ***********************************************************************/

int ValidarInxLista(int inxLista, int Modo)
{

	if ((inxLista <  0)
		|| (inxLista >= DIM_VT_LISTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtListas[inxLista] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtListas[inxLista] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TBAR -Validar indice de lista */

  /***********************************************************************
  *
  *  $FC Função: TBAR -Validar indice de carta
  *
  ***********************************************************************/

int ValidarInxCarta(int inxCarta, int Modo)
{

	if ((inxCarta <  0)
		|| (inxCarta >= DIM_VT_CARTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtCartas[inxCarta] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtCartas[inxCarta] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TBAR -Validar indice de carta */

/********** Fim do módulo de implementação: TBAR Teste baralho de cartas **********/

