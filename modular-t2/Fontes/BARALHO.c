// BARALHO2.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LISTA.h"
#include "BARALHO.h"

#define TAMANHO_MAX 40

typedef struct carta
{
	int naipe;
	int valor;
} BAR_tpCarta;

//typedef struct tagElemLista {
//
//        void * pValor ;
//            /* Ponteiro para o valor contido no elemento */
//
//        struct tagElemLista * pAnt ;
//            /* Ponteiro para o elemento predecessor */
//
//        struct tagElemLista * pProx ;
//            /* Ponteiro para o elemento sucessor */
//
//} tpElemLista ; 
// typedef struct LIS_tagLista {
//
//         tpElemLista * pOrigemLista ;
//               /* Ponteiro para a origem da lista */
//
//         tpElemLista * pFimLista ;
//               /* Ponteiro para o final da lista */
//
//         tpElemLista * pElemCorr ;
//               /* Ponteiro para o elemento corrente da lista */
//
//         int numElem ;
//               /* N�mero de elementos da lista */
//
//         void ( * ExcluirValor ) ( void * pValor ) ;
//               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */
//
//   } LIS_tpLista ;

//static LIS_tppLista PreencheBaralho(LIS_tppLista baralho);

static void Destruir(void * var )
{
	free(var) ;
}

static void imprimeBaralho(LIS_tppLista baralho)
{ 
	BAR_tpCarta * var;
	int i = 0;
	IrInicioLista(baralho);

	while(i < TAMANHO_MAX) 
	{ 
		var = (BAR_tpCarta*) LIS_ObterValor(baralho);
		printf("%d  %d %d \n", var->naipe, var->valor, i);

		LIS_AvancarElementoCorrente( baralho, 1);
		i++;
	}
	
	IrInicioLista(baralho); // restaurando o curElem para o inicio da lista
}


BAR_tppCarta BAR_CriaCarta( int valor, int naipe )
{
	BAR_tppCarta carta = (BAR_tppCarta) malloc( sizeof( BAR_tpCarta) );
	
	carta->valor = valor;
	carta->naipe = naipe;

	return carta;
}

int BAR_ObtemNaipe(BAR_tppCarta carta)
{
	return carta->naipe;
}

int BAR_ObtemValor(BAR_tppCarta carta)
{
	return carta->valor;
}

LIS_tppLista BAR_CriarNovoBaralhoEmbaralhado()
{
	LIS_tppLista baralho;

	BAR_tpCarta* cartas[TAMANHO_MAX];
	
	int inseridoNoBaralho[TAMANHO_MAX], totalCartasInseridas = 0, j;

	unsigned int i, index;

	for(j = 0; j < TAMANHO_MAX; ++j) cartas[j] = (BAR_tpCarta*)  malloc(sizeof (BAR_tpCarta) ); 

	srand( time( NULL) );
	
	memset(inseridoNoBaralho, 0, sizeof inseridoNoBaralho);
	
	baralho = LIS_CriarLista( Destruir );

	while(totalCartasInseridas < TAMANHO_MAX )
	{
		unsigned int indiceSorteado = rand() % (TAMANHO_MAX - totalCartasInseridas);

		index = 0;

		for(i = 0; i < TAMANHO_MAX; ++i)
		{
			if(inseridoNoBaralho[i] == 0)
			{
				if(index == indiceSorteado)
				{
					cartas[totalCartasInseridas] = BAR_CriaCarta( i / 10, i % 10);
					
					LIS_InserirElementoApos( baralho, cartas[totalCartasInseridas]) ;
										
					inseridoNoBaralho[i] = 1;
					
					totalCartasInseridas++;
					
					break;
				}
				else index++;
			}
		}
	}

	return baralho;
}

BAR_tppCarta BAR_PegaCartaDoTopo(LIS_tppLista baralho)
{

	BAR_tppCarta ptrCarta = (BAR_tppCarta) malloc(sizeof(BAR_tpCarta) ); 
	BAR_tppCarta carta    = (BAR_tppCarta) malloc(sizeof(BAR_tpCarta) );

	IrInicioLista(baralho);

	ptrCarta = (BAR_tppCarta) LIS_ObterValor(baralho);
	if(ptrCarta == NULL)
	{
		printf("Erro na chamada de LIS_ObterValor dentro de BAR_PegaValorDoTopo\n");
		exit(1);
	}

	carta->valor = ptrCarta->valor;
	carta->naipe = ptrCarta->naipe;

	LIS_ExcluirElemento( baralho );

	return carta;
}

BAR_tpCondRet BAR_DestruirBaralho(LIS_tppLista baralho)
{
	int i = 0;
	BAR_tppCarta x = (BAR_tppCarta) malloc( sizeof ( BAR_tpCarta) );
	if(baralho == NULL)
	{
		return BAR_CondRetBaralhoVazio;
	}

	for(i = 0; i < TAMANHO_MAX; ++i)
	{
		x = BAR_PegaCartaDoTopo(baralho);
		if(x == NULL) break;
	}
	
	LIS_DestruirLista(baralho);

	return BAR_CondRetOK;
}

int main(void)
{ 
	//LIS_tppLista baralho;
	//baralho = BAR_CriarNovoBaralhoEmbaralhado();
	//imprimeBaralho(baralho);
	//printf("\n\n");
	//BAR_DestruirBaralho(baralho);
	//system("pause") ;
	return ;
}
