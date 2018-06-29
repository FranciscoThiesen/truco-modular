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
BAR_tpCondRet BAR_CriaCarta(BAR_tppCarta *pCarta, char nome, int peso, char *naipe)
{
	*pCarta = (BAR_tppCarta)malloc(sizeof(BAR_tpCarta));
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
	retorno = BAR_CriaVetorCartas(&vetor_cartas);

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
	char *naipe[10];
	char valores[] = "A234567JQK";
	int i,j, peso;

	BAR_tppCarta carta=NULL;

	naipe[0]="ouros";naipe[2]="copas";
	naipe[1]="paus";naipe[3]="espadas";

	*cartas = (BAR_tppCarta *)malloc(40 * sizeof(BAR_tppCarta));

	if(*cartas==NULL)
	{
		return BAR_CondRetFaltouMemoria;
	}

	for(i = 0; i < 40; ++i)
	{
		//printf(" valor = %c, naipe = %s \n\n", valores[i/4], naipe[i%4]);
		if(valores[i/4] == '4' && strcmp(naipe[i%4], "paus") == 0) peso = 14;
		else if(valores[i/4]== '7' && strcmp(naipe[i%4], "copas") == 0) peso = 13;
		else if(valores[i/4] == 'A' && strcmp(naipe[i%4], "espadas") == 0) peso = 12;
		else if(valores[i/4] == '7' && strcmp(naipe[i%4], "ouros") == 0) peso = 11;
		else if(valores[i/4] == '3') peso = 10;
		else if(valores[i/4] == '2') peso = 9;
		else if(valores[i/4] == 'A') peso = 8;
		else if(valores[i/4] == 'K') peso = 7;
		else if(valores[i/4] == 'J') peso = 6;
		else if(valores[i/4] == 'Q') peso = 5;
		else if(valores[i/4] == '7') peso = 4;
		else if(valores[i/4] == '6') peso = 3;
		else if(valores[i/4] == '5') peso = 2;
		else if(valores[i/4] == '4') peso = 1;
		retorno = BAR_CriaCarta(&carta, valores[i/4], peso, naipe[i%4]);
		if(retorno != BAR_CondRetOK) return retorno;

		(*cartas)[i] = carta;
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

			corrente = (BAR_tppCarta) retorna_corrente(pBaralho->Cartas);

			

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
			if( LIS_ExcluirElemento(pBaralho->Cartas) != LIS_CondRetOK) return BAR_FalhaNoEmbaralhamento;
	   }

	   LIS_DestruirLista( pBaralho->Cartas );	/* Destrói a lista antiga */

	   IrInicioLista( pListaDestino );

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

BAR_tpCondRet BAR_RemoveCartaDoBaralho( BAR_tppBaralho pBaralho, BAR_tppCarta* pCarta)
{
	int res;
	BAR_tppCarta auxiliar;
	//*pCarta = (BAR_tppCarta)malloc(sizeof(BAR_tpCarta));
	if(*pCarta == NULL)
	{
		return BAR_CondRetFaltouMemoria;
	}
	auxiliar = (BAR_tppCarta) LIS_ObterValor(pBaralho->Cartas);

	(*pCarta)->nome = auxiliar->nome;
	strcpy((*pCarta)->naipe,auxiliar->naipe);
	(*pCarta)->peso = auxiliar->peso;

	res = LIS_ExcluirElemento(pBaralho->Cartas);

	if(res != LIS_CondRetOK) 
	{
		return BAR_CondRetListaVazia;
	}

	return BAR_CondRetOK;
}

char *GetNaipe(BAR_tppCarta carta);
int GetPeso(BAR_tppCarta carta);
char GetNome(BAR_tppCarta carta);

void BAR_ImprimeBaralho(BAR_tppBaralho pBaralho)
{
	int i;
	
	IrInicioLista( (LIS_tppLista) pBaralho->Cartas);

	for(i = 0; i < 40; ++i) 
	{
		BAR_tppCarta corrente =  (BAR_tppCarta) LIS_ObterValor(pBaralho->Cartas) ;
		LIS_AvancarElementoCorrente( (LIS_tppLista) pBaralho->Cartas, 1);
		printf("%c	-	%s	-	%d\n",GetNome(corrente) ,GetNaipe(corrente), GetPeso(corrente));
	}
}

char *GetNaipe(BAR_tppCarta carta)
{
	char *naipe = (char*)malloc(sizeof(20*sizeof(char)));
	strcpy(naipe,carta->naipe);
	return naipe;
}

int GetPeso(BAR_tppCarta carta)
{
	return carta->peso;
}

char GetNome(BAR_tppCarta carta)
{
	return carta->nome;
}

void BAR_ImprimeCarta(BAR_tppCarta carta)
{
	printf("naipe=%s  peso=%d  nome=%c\n", carta->naipe, carta->peso, carta->nome);
}


/********** Fim do módulo de implementação: BAR  BARALHO **********/