// BARALHO2.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LISTA.h"

const int tamanhoDoBaralho = 40;

typedef struct carta 
{
	int naipe;
	int valor;
} BRL_carta;

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
//               /* Número de elementos da lista */
//
//         void ( * ExcluirValor ) ( void * pValor ) ;
//               /* Ponteiro para a função de destruição do valor contido em um elemento */
//
//   } LIS_tpLista ;

//static LIS_tppLista PreencheBaralho(LIS_tppLista baralho);

static void Destruir(void * var )
{
	free(var) ;
}

LIS_tppLista CriarBaralho()
{ 
	unsigned int i=0; LIS_tppLista baralho; BRL_carta  carta ;
    BRL_carta* card;
	baralho = LIS_CriarLista( Destruir ) ;
	for(i = 0; i < tamanhoDoBaralho; i++)
	{
		carta.naipe = i/10 ;
		carta.valor = i%10 ;
		LIS_InserirElementoApos( baralho, &carta) ;
		card = (BRL_carta*) LIS_ObterValor(baralho) ;
		printf("%d,  %d\n", card->naipe, card->valor) ;
	}
	return baralho ;
}

static void imprimeBaralho(LIS_tppLista baralho)
{ 
	BRL_carta * var;
	int i = 0;
	IrInicioLista(baralho);

	while(i < tamanhoDoBaralho) 
	{ 
		var = (BRL_carta*) LIS_ObterValor(baralho);
		printf("%d  %d %d \n", var->naipe, var->valor, i);

		LIS_AvancarElementoCorrente( baralho, 1);
		i++;
	}
	
	IrInicioLista(baralho); // restaurando o curElem para o inicio da lista
}

LIS_tppLista BAR_NovoBaralhoEmbaralhado()
{
	LIS_tppLista baralho;
	
	BRL_carta** cartas; // temos que lembrar de dar free nos enderecos que demos malloc, talvez destroiLista resolva isso...

	int inseridoNoBaralho[40], totalCartasInseridas = 0, index;

	unsigned int i, j;

	cartas = (BRL_carta**) malloc(sizeof(BRL_carta) * 40);
	for(j = 0; j < 40; ++j) cartas[j] = (BRL_carta*)  malloc(sizeof (BRL_carta) ); 

	srand( time(NULL) ); // colocando o tempo atual na seed
	
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

BRL_carta* BAR_PegaCartaDoTopo(LIS_tppLista baralho)
{

	BRL_carta* ptrCarta = (BRL_carta*) malloc(sizeof(BRL_carta) ); 
	BRL_carta* ptrCartaRet = (BRL_carta*) malloc(sizeof(BRL_carta) );

	if(ptrCarta == NULL || ptrCartaRet == NULL) 
	{
		printf("Problema com a alocacao de memoria\n");
		return NULL;
	}
	
	IrInicioLista(baralho);

	ptrCarta = (BRL_carta*) LIS_ObterValor(baralho);
	
	if(ptrCarta == NULL) 
	{
		printf("Problema ao retirar uma carta do topo da pilha\n");
		return NULL;
	}
	
	ptrCartaRet->valor = ptrCarta->valor;
	ptrCartaRet->naipe = ptrCarta->naipe;

	LIS_ExcluirElemento( baralho );

	return ptrCartaRet;
}

static void esvaziaBaralhoUmaCartaPorVez(LIS_tppLista baralho)
{
	int i = 0;
	BRL_carta* x;
	for(i = 0; i < 40; ++i)
	{
		x = BAR_PegaCartaDoTopo(baralho);
		printf("%d %d\n", x->naipe, x->valor);
	}
	LIS_EsvaziarLista(baralho);
}

int main(void)
{ 
	LIS_tppLista baralho;
	CriarBaralho();
	baralho = BAR_NovoBaralhoEmbaralhado();
	imprimeBaralho(baralho);
	printf("\n\n");
	esvaziaBaralhoUmaCartaPorVez(baralho);
	system("pause") ;
	return ;
}
