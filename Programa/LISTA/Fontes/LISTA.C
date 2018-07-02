/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
#include   "CESPDIN.H"
#include   "GENERICO.h"
#include   "CONTA.h"
#endif

#define LISTA_OWN
#include "LISTA.H"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {

	void * pValor ;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt ;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx ;
	/* Ponteiro para o elemento sucessor */

} tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {

	tpElemLista * pOrigemLista ;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista ;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr ;
	/* Ponteiro para o elemento corrente da lista */

	int numElem ;
	/* N�mero de elementos da lista */

	void ( * ExcluirValor ) ( void * pValor ) ;
	/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

} LIS_tpLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void LiberarElemento( LIS_tppLista   pLista ,
	tpElemLista  * pElem   ) ;

static tpElemLista * CriarElemento( LIS_tppLista pLista ,
	void *       pValor  ) ;

static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

LIS_tppLista LIS_CriarLista(
	void   ( * ExcluirValor ) ( void * pDado ) )
{

	LIS_tpLista * pLista = NULL ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_CriarLista" ) ;
#endif

	pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
	if ( pLista == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_CriarLista: Faltou memoria" ) ;
#endif
		return NULL ;
	} /* if */

#ifdef _DEBUG
	CNT_CONTAR( "LIS_CriarLista: Nao faltou memoria" ) ;
#endif

#ifdef _DEBUG
	CNT_CONTAR( "LIS_CriarLista: Definiu tipo do espaco" ) ;
#endif

	LimparCabeca( pLista ) ;

	pLista->ExcluirValor = ExcluirValor ;

	return pLista ;

} /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

void LIS_DestruirLista( LIS_tppLista pLista )
{
#ifdef _DEBUG
	CNT_CONTAR( "LIS_DestruirLista" ) ;
#endif

#ifdef _DEBUG
	if(pLista==NULL)
	{
		CNT_CONTAR("LIS_DestruirLista: Lista e NULL");
		assert( pLista != NULL ) ;
	}
#endif

#ifdef _DEBUG
	CNT_CONTAR( "LIS_DestruirLista: Lista nao e NULL" ) ;
#endif
	LIS_EsvaziarLista( pLista ) ;

	free( pLista ) ;

} /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista( LIS_tppLista pLista )
{

	tpElemLista * pElem ;
	tpElemLista * pProx ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_EsvaziarLista" ) ;
#endif

#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

#ifdef _DEBUG
	CNT_CONTAR( "LIS_EsvaziarLista: Lista nao e NULL" ) ;
#endif
	pElem = pLista->pOrigemLista ;
	while ( pElem != NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_EsvaziarLista: Liberar elemento") ;
#endif
		pProx = pElem->pProx ;
		LiberarElemento( pLista , pElem ) ;
		pElem = pProx ;
	} /* while */

#ifdef _DEBUG
	CNT_CONTAR( "LIS_EsvaziarLista: Limpar cabeca" ) ;
#endif
	LimparCabeca( pLista ) ;

} /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
	void * pValor        )
{

	tpElemLista * pElem ;
#ifdef _DEBUG
	CNT_CONTAR( "LIS_InserirElementoAntes" ) ;
#endif

#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

#ifdef _DEBUG
	CNT_CONTAR( "LIS_InserirElementoAntes: Lista nao e NULL" ) ;
#endif

	/* Criar elemento a inerir antes */

	pElem = CriarElemento( pLista , pValor ) ;

	if ( pElem == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_InserirElementoAntes: Faltou memoria ao criar elemento" ) ;
#endif
		return LIS_CondRetFaltouMemoria ;
	} /* if */
#ifdef _DEBUG
	CNT_CONTAR( "LIS_InserirElementoAntes: Nao faltou memoria ao criar elemento" ) ;
#endif
	/* Encadear o elemento antes do elemento corrente */

	if ( pLista->pElemCorr == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_InserirElementoAntes: Inserir elemento em lista vazia" ) ;
#endif
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_InserirElementoAntes: Inserir elemento em lista nao vazia" ) ;
#endif

		if ( pLista->pElemCorr->pAnt != NULL )
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoAntes: Elemento corrente nao e o inicial" ) ;
#endif
			pElem->pAnt  = pLista->pElemCorr->pAnt ;
			pLista->pElemCorr->pAnt->pProx = pElem ;
		} else
		{

#ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoAntes: Elemento corrente e o inicial" ) ;
#endif
			pLista->pOrigemLista = pElem ;
		} /* if */

		pElem->pProx = pLista->pElemCorr ;
		pLista->pElemCorr->pAnt = pElem ;
	} /* if */

	pLista->pElemCorr = pElem ;

	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
	void * pValor        )

{

	tpElemLista * pElem ;
#ifdef _DEBUG
	CNT_CONTAR( "LIS_InserirElementoApos" ) ;
#endif
#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif
#ifdef _DEBUG
	CNT_CONTAR( "LIS_InserirElementoApos: Lista nao e NULL" ) ;
#endif
	/* Criar elemento a inerir ap�s */

	pElem = CriarElemento( pLista , pValor ) ;
	if ( pElem == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_InserirElementoApos: Faltou memoria ao criar elemento" ) ;
#endif

		return LIS_CondRetFaltouMemoria ;
	} /* if */
#ifdef _DEBUG
	CNT_CONTAR( "LIS_InserirElementoApos: Nao faltou memoria ao criar elemento" ) ;
#endif
	/* Encadear o elemento ap�s o elemento */

	if ( pLista->pElemCorr == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_InserirElementoApos: Inserir elemento em lista vazia" ) ;
#endif
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_InserirElementoApos: Inserir elemento em lista nao vazia" ) ;
#endif
		if ( pLista->pElemCorr->pProx != NULL )
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos: Elemento corrente nao e final" ) ;
#endif
			pElem->pProx  = pLista->pElemCorr->pProx ;
			pLista->pElemCorr->pProx->pAnt = pElem ;
		} else
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos: Elemento corrente e final" ) ;
#endif
			pLista->pFimLista = pElem ;
		} /* if */

		pElem->pAnt = pLista->pElemCorr ;
		pLista->pElemCorr->pProx = pElem ;

	} /* if */

	pLista->pElemCorr = pElem ;

	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
{

	tpElemLista * pElem ;
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ExcluirElemento" ) ;
#endif
#ifdef _DEBUG
	assert( pLista  != NULL ) ;
#endif

#ifdef _DEBUG
	CNT_CONTAR( "LIS_ExcluirElemento: Lista nao e NULL" ) ;
#endif

	if ( pLista->pElemCorr == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ExcluirElemento: Lista vazia" ) ;
#endif
		return LIS_CondRetListaVazia ;
	} /* if */

#ifdef _DEBUG
	CNT_CONTAR( "LIS_ExcluirElemento: Lista nao esta vazia" ) ;
#endif


	pElem = pLista->pElemCorr ;

	/* Desencadeia � esquerda */

	if ( pElem->pAnt != NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente nao e o inicial" ) ;
#endif
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} else {
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente e o inicial" ) ;
#endif
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia � direita */

	if ( pElem->pProx != NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente nao e o final" ) ;
#endif
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente e o final" ) ;
#endif
		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	LiberarElemento( pLista , pElem ) ;

	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

void * LIS_ObterValor( LIS_tppLista pLista )
{
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ObterValor" ) ;
#endif
#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ObterValor: Lista nao e NULL" ) ;
#endif
	if ( pLista->pElemCorr == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ObterValor: Lista esta vazia" ) ;
#endif
		return NULL ;
	} /* if */
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ObterValor: Lista nao esta vazia" ) ;
#endif
	return pLista->pElemCorr->pValor ;

} /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

void IrInicioLista( LIS_tppLista pLista )
{
#ifdef _DEBUG
	CNT_CONTAR( "LIS_IrInicioLista" ) ;
#endif
#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif
#ifdef _DEBUG
	CNT_CONTAR( "LIS_IrInicioLista: Lista nao e NULL" ) ;
#endif
	pLista->pElemCorr = pLista->pOrigemLista ;

} /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

void IrFinalLista( LIS_tppLista pLista )
{
#ifdef _DEBUG
	CNT_CONTAR( "LIS_IrFinalLista" ) ;
#endif
#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif
#ifdef _DEBUG
	CNT_CONTAR( "LIS_IrFinalLista: Lista nao e NULL" ) ;
#endif

	pLista->pElemCorr = pLista->pFimLista ;

} /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
	int numElem )
{

	int i ;

	tpElemLista * pElem ;
#ifdef _DEBUG
	CNT_CONTAR( "LIS_AvancarElementoCorrente" ) ;
#endif
#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

#ifdef _DEBUG
	CNT_CONTAR( "LIS_AvancarElementoCorrente: Lista nao e NULL" ) ;
#endif
	/* Tratar lista vazia */

	if ( pLista->pElemCorr == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Lista esta vazia" ) ;
#endif
		return LIS_CondRetListaVazia ;

	} /* fim ativa: Tratar lista vazia */

#ifdef _DEBUG
	CNT_CONTAR( "LIS_AvancarElementoCorrente: Lista nao esta vazia" ) ;
#endif

	/* Tratar avan�ar para frente */

	if ( numElem > 0 )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancar para frente" ) ;
#endif
		pElem = pLista->pElemCorr ;
		for( i = numElem ; i > 0 ; i-- )
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancou elemento" ) ;
#endif
			if ( pElem == NULL )
			{
#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Chegou no final da lista" ) ;
#endif
				break ;
			} /* if */
			pElem    = pElem->pProx ;
		} /* for */
#ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Terminou de avancar elemento" ) ;
#endif

		if ( pElem != NULL )
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao chegou no final da lista" ) ;
#endif
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */
#ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Elemento final vira o corrente" ) ;
#endif
		pLista->pElemCorr = pLista->pFimLista ;
		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avan�ar para frente */

	/* Tratar avan�ar para tr�s */

	else if ( numElem < 0 )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancar para tras" ) ;
#endif
		pElem = pLista->pElemCorr ;
		for( i = numElem ; i < 0 ; i++ )
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_AvancarElementoCorrente: Voltou elemento" ) ;
#endif
			if ( pElem == NULL )
			{
#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Chegou no inicio da lista" ) ;
#endif
				break ;
			} /* if */
			pElem    = pElem->pAnt ;
		} /* for */
#ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Terminou de voltar elemento" ) ;
#endif
		if ( pElem != NULL )
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao chegou no inicio da lista" ) ;
#endif
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */
#ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente: Elemento inicial vira o corrente" ) ;
#endif
		pLista->pElemCorr = pLista->pOrigemLista ;
		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avan�ar para tr�s */
#ifdef _DEBUG
	CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao avanca elemento" ) ;
#endif
	/* Tratar n�o avan�ar */

	return LIS_CondRetOK ;

} /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
	void * pValor        )
{

	tpElemLista * pElem ;
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ProcurarValor" ) ;
#endif
#ifdef _DEBUG
	assert( pLista  != NULL ) ;
#endif
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ProcurarValor: Lista nao e NULL" ) ;
#endif
	if ( pLista->pElemCorr == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor: Lista esta vazia" ) ;
#endif
		return LIS_CondRetListaVazia ;
	} /* if */
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ProcurarValor: Lista nao esta vazia" ) ;
#endif
	for ( pElem  = pLista->pElemCorr ;
		pElem != NULL ;
		pElem  = pElem->pProx )
	{
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor: Procurar no elemento" ) ;
#endif
		if ( pElem->pValor == pValor )
		{
#ifdef _DEBUG
			CNT_CONTAR( "LIS_ProcurarValor: Achou" ) ;
#endif
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */
#ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor: Procurar no proximo" ) ;
#endif
	} /* for */
#ifdef _DEBUG
	CNT_CONTAR( "LIS_ProcurarValor: Nao achou" ) ;
#endif
	return LIS_CondRetNaoAchou ;

} /* Fim fun��o: LIS  &Procurar elemento contendo valor */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

void LiberarElemento( LIS_tppLista   pLista ,
	tpElemLista  * pElem   )
{
#ifdef _DEBUG
	CNT_CONTAR( "LiberarElemento" ) ;
#endif
	if ( ( pLista->ExcluirValor != NULL )
		&& ( pElem->pValor != NULL        ))
	{
#ifdef _DEBUG
		CNT_CONTAR( "LiberarElemento: Excluiu valor" ) ;
#endif
		pLista->ExcluirValor( pElem->pValor ) ;
	} /* if */
#ifdef _DEBUG
	CNT_CONTAR( "LiberarElemento: Liberou elemento" ) ;
#endif
	free( pElem ) ;

	pLista->numElem-- ;

} /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento( LIS_tppLista pLista ,
	void *       pValor  )
{

	tpElemLista * pElem ;
#ifdef _DEBUG
	CNT_CONTAR( "CriarElemento" ) ;
#endif
	pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
	if ( pElem == NULL )
	{
#ifdef _DEBUG
		CNT_CONTAR( "CriarElemento: Faltou memoria ao criar elemento" ) ;
#endif
		return NULL ;
	} /* if */
#ifdef _DEBUG
	CNT_CONTAR( "CriarElemento: Criou elemento com sucesso" ) ;
#endif
	pElem->pValor = pValor ;
	pElem->pAnt   = NULL  ;
	pElem->pProx  = NULL  ;

	pLista->numElem ++ ;

	return pElem ;

} /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

void LimparCabeca( LIS_tppLista pLista )
{
#ifdef _DEBUG
	CNT_CONTAR( "LimparCabeca" ) ;
#endif
	pLista->pOrigemLista = NULL ;
	pLista->pFimLista = NULL ;
	pLista->pElemCorr = NULL ;
	pLista->numElem   = 0 ;

} /* Fim fun��o: LIS  -Limpar a cabe�a da lista */



/***********************************************************************
*
*  $FC Fun��o: LIS  -Retorna ponteiro corrente da lista
*
***********************************************************************/
void *retorna_corrente(LIS_tppLista pLista)
{
#ifdef _DEBUG
	CNT_CONTAR( "retorna_corrente" ) ;
#endif
	return pLista->pElemCorr->pValor;
}/* Fim fun��o: LIS  -Retorna corrente */



/***********************************************************************
*
*  $FC Fun��o: LIS  -Retorna numero de elementos da lista
*
***********************************************************************/

int LIS_numElem(LIS_tppLista pLista)
{
#ifdef _DEBUG
	CNT_CONTAR( "LIS_numElem" ) ;
#endif
	return pLista->numElem;
}



/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/
