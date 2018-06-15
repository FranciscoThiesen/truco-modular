/*
#include <stdio.h>
#include <stdlib.h>
#include "BARALHO.h"
#include "LISTA.H"

int xablau()
{
	int retorno;
	BAR_tppCarta *cartas=NULL;
	BAR_tppBaralho Baralho=(BAR_tppBaralho)malloc(sizeof(BAR_tppBaralho));
	BAR_tppCarta carta = NULL;
	if(BAR_CriaCarta(&carta,'a',10,"ouros")==BAR_CondRetOK)
	{
	printf("sucesso em criar uma carta!\n");
	}
	//retorno=DestruirCarta(*carta);
	retorno=BAR_CriaVetorCartas(&cartas);
		if(retorno==BAR_CondRetOK)
		printf("sucesso\n");
	retorno=BAR_CriarBaralho(&Baralho);
		if(retorno==BAR_CondRetOK)
		printf("sucesso\n");
	retorno=BAR_Embaralhar(Baralho);
	if(retorno==BAR_CondRetOK)
		printf("sucesso\n");
	retorno=BAR_DestruirBaralho( Baralho );
	if(retorno==BAR_CondRetOK)
		printf("sucesso\n");
	return 0;
}
*/