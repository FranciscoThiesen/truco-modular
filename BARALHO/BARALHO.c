// BARALHO2.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LISTA.h"
#include "BARALHO.h"

/*typedef struct carta 
{
	int naipe;
	int valor;
} BRL_carta;*/

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

static void Destruir( void * var )
{
	free( var ) ;
}

void BAR_DestruirBaralho( LIS_tppLista baralho )
{
	LIS_DestruirLista( baralho );
}

static void imprimeBaralho( LIS_tppLista baralho )
{ 
	BRL_carta* var;
	int i = 0;
	IrInicioLista( baralho );

	while(i < 40) 
	{ 
		var = ( BRL_carta* ) LIS_ObterValor( baralho );
		printf("%d  %d %d \n", var->naipe, var->valor, i);

		LIS_AvancarElementoCorrente( baralho, 1 );
		i++;
	}
	
	IrInicioLista( baralho ); // restaurando o curElem para o inicio da lista
}

BAR_tpCondRet BAR_InsereCartaNoBaralho( BRL_carta* carta, LIS_tppLista baralho )
{
	if( carta == NULL ) return BAR_CartaNula;
	if( baralho == NULL ) return BAR_CondRetBaralhoVazio;

	LIS_InserirElementoApos( baralho, carta );

	return BAR_CondRetOK;
}

LIS_tppLista BAR_NovoBaralhoEmbaralhado()
{
	LIS_tppLista baralho;

	BRL_carta* cartas[40]; // temos que lembrar de dar free nos enderecos que demos malloc, talvez destroiLista resolva isso...
	
	int inseridoNoBaralho[40], totalCartasInseridas = 0, index, j;

	unsigned int i;

	for(j = 0; j < 40; ++j) cartas[j] = (BRL_carta*)  malloc( sizeof (BRL_carta) ); 

	srand( time(NULL) ); // colocando o tempo atual na seed
	
	memset( inseridoNoBaralho, 0, sizeof inseridoNoBaralho ); // aqui digo que nenhuma carta foi inserida
	
	baralho = LIS_CriarLista( Destruir );

	//IrInicioLista(baralho);

	while( totalCartasInseridas < 40 )
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

					BAR_InsereCartaNoBaralho( cartas[totalCartasInseridas], baralho );
					
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

BAR_tpCondRet BAR_PegaCartaDoTopo( LIS_tppLista baralho, BRL_carta* carta )
{
	BRL_carta* ptrCarta = ( BRL_carta* ) malloc( sizeof( BRL_carta) ); 
	
	if( ptrCarta == NULL )
	{
		printf("Erro na chamada de LIS_ObterValor dentro de BAR_PegaValorDoTopo\n");
		return BAR_CondRetFaltouMemoria;
	}

	if(baralho == NULL)
	{
		return BAR_CondRetBaralhoVazio;
	}

	IrInicioLista( baralho );

	ptrCarta = ( BRL_carta* ) LIS_ObterValor( baralho );

	if( ptrCarta == NULL )
	{
		free( ptrCarta );
		return BAR_CondRetNaoObteveCarta;
	}

	carta->valor = ptrCarta->valor;
	carta->naipe = ptrCarta->naipe;

	LIS_ExcluirElemento( baralho );
	//free(ptrCarta);

	return BAR_CondRetOK;
}

static void esvaziaBaralhoUmaCartaPorVez( LIS_tppLista baralho )
{  
	if( baralho != NULL )
	{
		int i = 0;
		BRL_carta* x = ( BRL_carta* ) malloc( sizeof( BRL_carta ) );
		if(x == NULL)
		{
			printf("Problema ao alocar um ponteiro para o tipo carta\n");
			return;
		}
		while( BAR_PegaCartaDoTopo( baralho, x ) == BAR_CondRetOK )
		{
			printf("%d %d\n", x->naipe, x->valor);
		}
		LIS_EsvaziarLista( baralho );
	}
}

int main()
{   
	BAR_tppCarta carta = (BRL_carta *) malloc( sizeof( BRL_carta ) s);
	
	LIS_tppLista baralho;
	
	//CriarBaralho();
	
	baralho = BAR_NovoBaralhoEmbaralhado();
	//imprimeBaralho(baralho); // imprime, mas nao remove nenhuma carta do baralho

	printf("\n\n");

	printf("%d\n", BAR_PegaCartaDoTopo( baralho, carta ) ); // tira uma carta do topo do baralho ( deveria retornar 0 )

	esvaziaBaralhoUmaCartaPorVez( baralho ); // esvazia todo o baralho

	printf("\n\n");

	printf("%d \n", BAR_PegaCartaDoTopo( baralho, carta ) );

	free( carta );

	system("pause") ;
	return ;
}