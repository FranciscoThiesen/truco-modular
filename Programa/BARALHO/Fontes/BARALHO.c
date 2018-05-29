/***************************************************************************
*  $MCI Módulo de implementação: BAR  BARALHO
*
*  Arquivo gerado:              BARALHO.c
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
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <stdlib.h>
#include   <time.h>
#include "BARALHO.h"
#include "LISTA.H"


#define BARALHO_OWN
	#include "BARALHO.h"
#undef BARALHO_OWN

#define	TRUCO 40


/***********************************************************************
*
*  $TC Tipo de dados: BAR Carta
*
*
***********************************************************************/

typedef struct BAR_tagCarta
{
	char nome;
	int peso;
	char naipe[20];
}	BAR_tpCarta;


/***********************************************************************
*
*  $TC Tipo de dados: BAR Baralho
*
*
***********************************************************************/

typedef struct BAR_tagBaralho
{
	LIS_tppLista Cartas;
}	BAR_tpBaralho;

/***** Protótipos das funções encapuladas no módulo *****/
BAR_tpCondRet DestruirValor(void * pValor);

/***********************************************************************
*
*  $FC Função: BAR  -Destruir elemento
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo ponteiro passado
*
***********************************************************************/
BAR_tpCondRet DestruirValor(void * pValor)
	{
		free(pValor);
		return BAR_CondRetOK;
	}

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: BAR  &Criar carta
*  ****/
BAR_tpCondRet BAR_CriaCarta(BAR_tppCarta *pCarta,char nome, int peso,char *naipe)
{
	*pCarta=(BAR_tppCarta)malloc(sizeof(BAR_tpCarta));
	if(*pCarta==NULL)
	{
		return BAR_CondRetFaltouMemoria;
	}
	(*pCarta)->nome=nome;
	strcpy((*pCarta)->naipe,naipe);
	(*pCarta)->peso=peso;
	return BAR_CondRetOK;
}/* Fim função: BAR  &Criar carta */

/***************************************************************************
*
*  Função: BAR  &Destruir carta
*  ****/
BAR_tpCondRet DestruirCarta(BAR_tppCarta pCarta)
{
	free(pCarta);
	return BAR_CondRetOK;
}/* Fim função: BAR  &Destruir carta */

/***************************************************************************
*
*  $FC Função: BAR  &Criar Baralho
*  ****/
BAR_tpCondRet BAR_CriarBaralho(BAR_tppBaralho *pBaralho)
{
	int i;
	BAR_tppCarta pcarta;
	BAR_tppCarta *vetor_cartas=NULL;
	BAR_tpCondRet retorno;

	//ponteiro para baralho
	*pBaralho = (BAR_tpBaralho*)malloc(sizeof(BAR_tpBaralho));
		if ( *pBaralho == NULL )
      {
         return  BAR_CondRetFaltouMemoria ;
      }
	//cria as 40 cartas e armazena em um vetor
	retorno=BAR_CriaVetorCartas(&vetor_cartas);

	(*pBaralho)->Cartas = LIS_CriarLista((void (*) (void *pDado))DestruirCarta);

	if((*pBaralho)->Cartas==NULL)
	{
		return BAR_CondRetFaltouMemoria;
	}
	for(i=0;i<TRUCO;i++)
	{
		//insere a carta na lista
		BAR_CriaCarta(&pcarta,vetor_cartas[i]->nome,vetor_cartas[i]->peso,vetor_cartas[i]->naipe);
		LIS_InserirElementoApos((*pBaralho)->Cartas,pcarta);
	}
	return BAR_CondRetOK;
}/* Fim função: BAR  &Criar baralho */


/***************************************************************************
*
*  $FC Função: BAR  &Cria vetor cartas
*  ****/
BAR_tpCondRet BAR_CriaVetorCartas(BAR_tppCarta *cartas[])
{
	BAR_tpCondRet retorno;
	char *naipe[10][4];
	int i,j,cont=0;
	BAR_tppCarta carta=NULL;

	naipe[0][0]="ouros";naipe[0][1]="copas";
	naipe[0][2]="paus";naipe[0][3]="espadas";

	*cartas = (BAR_tppCarta *)malloc(40 * sizeof(BAR_tppCarta));

	if(*cartas==NULL)
	{
		return BAR_CondRetFaltouMemoria;
	}

	for(cont=0,i=0;i<10;i++)
	{
		for(j=0;j<4;j++)
		{
			//cria cartas de 2 a 7
			if(i<6)
			{
				retorno=BAR_CriaCarta(&carta,(50+i),0,naipe[0][j]);
				if (retorno!=BAR_CondRetOK)
					return retorno;
			}
			//cria o J
			else if(cont>=24&&cont<28)
			{
				retorno=BAR_CriaCarta(&carta,'J',0,naipe[0][j]);
				if (retorno!=BAR_CondRetOK)
					return retorno;
			}
			//cria o Q
			else if(cont>=28&&cont<32)
			{
				retorno=BAR_CriaCarta(&carta,'Q',0,naipe[0][j]);
				if (retorno!=BAR_CondRetOK)
					return retorno;
			}
			//cria o K
			else if(cont>=32&&cont<36)
			{
				retorno=BAR_CriaCarta(&carta,'K',0,naipe[0][j]);
				if (retorno!=BAR_CondRetOK)
					return retorno;
			}
			//cria o A
			else if(cont>=36&&cont<40)
			{
				retorno=BAR_CriaCarta(&carta,'A',0,naipe[0][j]);
				if (retorno!=BAR_CondRetOK)
					return retorno;
			}
			(*cartas)[cont]=carta;
			cont++;
		}
	}
	return retorno;
}/* Fim função: BAR  &Cria vetor cartas */


/***************************************************************************
*
*  $FC Função: BAR  &Embaralhar
*  ****/
 BAR_tpCondRet BAR_Embaralhar( BAR_tppBaralho pBaralho )
   {

	   int i = -1; //tamBaralho = -1;
	   LIS_tppLista pListaDestino = NULL;

       if( pBaralho == NULL )
	   {
		   return BAR_CondRetBaralhoNaoExiste ;
	   }
	   pListaDestino=LIS_CriarLista((void (*) (void *pDado))DestruirCarta);
	   if(pListaDestino==NULL)
	   {
		   return BAR_CondRetFaltouMemoria;
	   }
	   IrInicioLista( pListaDestino );

	   srand((unsigned) time(NULL));

	   for(i = 40; i > 0; i--)
	   {
		   BAR_tppCarta corrente,copia;
		   LIS_tpCondRet condRetLis;
		   int inxCarta = rand() % i;							/* Sorteia uma carta */

		   IrInicioLista( pBaralho->Cartas );					/* Inicio do baralho */

		   if( LIS_AvancarElementoCorrente( pBaralho->Cartas, inxCarta ) != LIS_CondRetOK )	/* Vai para a carta sorteada */
			{
				return BAR_CondRetTamanhoErrado;
			}

		   corrente =(BAR_tppCarta) retorna_corrente(pBaralho->Cartas);

		   BAR_CriaCarta(&copia, corrente->nome, corrente->peso, corrente->naipe);

		   condRetLis = LIS_InserirElementoApos(pListaDestino,copia);

		   if( condRetLis == LIS_CondRetListaVazia )
		   {
				return BAR_CondRetListaVazia;
		   }
		   else if( condRetLis == LIS_CondRetFaltouMemoria )
		   {
			    return BAR_CondRetFaltouMemoria;
		   }
	   }

	   LIS_DestruirLista( pBaralho->Cartas );	/* Destrói a lista antiga */

	   pBaralho->Cartas = pListaDestino;		/* Baralho agora é composto pela lista embaralhada */

	   return BAR_CondRetOK;

   } /* Fim função: BAR  &Embaralhar */

 /***************************************************************************
*
*  $FC Função: BAR  &Destruir baralho
*  ****/
BAR_tpCondRet BAR_DestruirBaralho( BAR_tppBaralho pBaralho )
   {

      if( pBaralho == NULL )
	  {
		  free(pBaralho) ;
		  return BAR_CondRetOK ;
	  }

      if(pBaralho->Cartas != NULL)
		  LIS_DestruirLista( pBaralho->Cartas ) ;

      free( pBaralho ) ;

	  return BAR_CondRetOK;

   } /* Fim função: EMB  &Destruir baralho */


/********** Fim do módulo de implementação: BAR  BARALHO **********/
