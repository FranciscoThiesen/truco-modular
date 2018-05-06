// BARALHO2.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LISTA.h"


typedef struct carta 
{
	int naipe;
	int valor;
} BRL_carta;

typedef struct tagElemLista {

        void * pValor ;
            /* Ponteiro para o valor contido no elemento */

        struct tagElemLista * pAnt ;
            /* Ponteiro para o elemento predecessor */

        struct tagElemLista * pProx ;
            /* Ponteiro para o elemento sucessor */

} tpElemLista ; 
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

//static LIS_tppLista PreencheBaralho(LIS_tppLista baralho);

void Destruir(void * var )
{
	free(var) ;
}

LIS_tppLista CriarBaralho()
{ 
	unsigned int i=0; LIS_tppLista baralho; BRL_carta  carta ;
    BRL_carta* card;
	baralho = LIS_CriarLista( Destruir ) ;
	for(i = 0; i < 40; i++)
	{
		carta.naipe = i/10 ;
		carta.valor = i%10 ;
		LIS_InserirElementoApos( baralho, &carta) ;
		card = (BRL_carta*) LIS_ObterValor(baralho) ;
		printf("%d,  %d\n", card->naipe, card->valor) ;
	}
	return baralho ;
}

static void imprimeLista(LIS_tppLista aiMeuBaralho)
{ 
	BRL_carta * var;
	int i = 0;
	IrInicioLista(aiMeuBaralho);

	while(i < 40) 
	{ 
		var = (BRL_carta*) LIS_ObterValor(aiMeuBaralho);
		printf("%d  %d %d \n", var->naipe, var->valor, i);

		LIS_AvancarElementoCorrente( aiMeuBaralho, 1);
		i++;
	}
	
	IrInicioLista(aiMeuBaralho); // restaurando o curElem para o inicio da lista
}

LIS_tppLista NovoBaralhoEmbaralhado()
{
	LIS_tppLista baralho;

	BRL_carta* cartas[40]; // temos que lembrar de dar free nos enderecos que demos malloc, talvez destroiLista resolva isso...
	
	int inseridoNoBaralho[40], totalCartasInseridas = 0, index, j;

	unsigned int i;

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


int main(void)
{ 
	LIS_tppLista baralho;
	CriarBaralho();
	baralho=NovoBaralhoEmbaralhado();
	imprimeLista(baralho);
	system("pause") ;
	return ;
}