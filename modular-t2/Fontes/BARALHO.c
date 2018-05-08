// BARALHO2.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LISTA.h"
#include "BARALHO.h"


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

	while(i < 40) 
	{ 
		var = (BAR_tpCarta*) LIS_ObterValor(baralho);
		printf("%d  %d %d \n", var->naipe, var->valor, i);

		LIS_AvancarElementoCorrente( baralho, 1);
		i++;
	}
	
	IrInicioLista(baralho); // restaurando o curElem para o inicio da lista
}

LIS_tppLista BAR_CriarNovoBaralhoEmbaralhado()
{
	LIS_tppLista baralho;

	BAR_tpCarta* cartas[40]; // temos que lembrar de dar free nos enderecos que demos malloc, talvez destroiLista resolva isso...
	
	int inseridoNoBaralho[40], totalCartasInseridas = 0, j;

	unsigned int i, index;

	for(j = 0; j < 40; ++j) cartas[j] = (BAR_tpCarta*)  malloc(sizeof (BAR_tpCarta) ); 

	srand( time( NULL) ); // colocando o tempo atual na seed
	
	memset(inseridoNoBaralho, 0, sizeof inseridoNoBaralho); // aqui digo que nenhuma carta foi inserida
	
	baralho = LIS_CriarLista( Destruir );

	//IrInicioLista(baralho);

	while(totalCartasInseridas < 40 )
	{
		unsigned int indiceSorteado = rand() % (40 - totalCartasInseridas);
		// entre todas as cartas ativas, vamos inserir a i-esima delas
		index = 0;

		for(i = 0; i < 40; ++i)
		{
			if(inseridoNoBaralho[i] == 0) // carta i ainda nao foi inserida
			{
				if(index == indiceSorteado) // chegamos na posicao desejada
				{
					cartas[totalCartasInseridas]->naipe = i / 10;
					cartas[totalCartasInseridas]->valor = i % 10;

					LIS_InserirElementoApos( baralho, cartas[totalCartasInseridas]) ;
					
					printf("Carta inserida na lista( naipe = %d, valor = %d i = %d\n", cartas[totalCartasInseridas]->naipe, cartas[totalCartasInseridas]->valor, i);
					
					inseridoNoBaralho[i] = 1;
					totalCartasInseridas++;
					break;
				}
				else index++;
			}
		}
	}

	printf("Total de cartas inseridas = %d\n", totalCartasInseridas);
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

	for(i = 0; i < 40; ++i)
	{
		x = BAR_PegaCartaDoTopo(baralho);
		if(x == NULL) break;
	}
	
	LIS_DestruirLista(baralho);

	return BAR_CondRetOK;
}

int main(void)
{ 
	LIS_tppLista baralho;
	baralho = BAR_CriarNovoBaralhoEmbaralhado();
	imprimeBaralho(baralho);
	printf("\n\n");
	BAR_DestruirBaralho(baralho);
	system("pause") ;
	return ;
}
