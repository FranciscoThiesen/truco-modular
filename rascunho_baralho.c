// BARALHO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


 typedef struct CARTA 
 {
	 int NAIPE;
	 int VALOR ;
 }BRL_CARTA;


static LIS_tppLista PreencheBaralho(LIS_tppLista baralho);

 void CriarBaralho()
 {  int i=0;
    BRL_CARTA * carta;
	LIS_tppLista baralho;
	baralho= LIS_CriarLista( Destruir ) ;
    for(i=0;i<40;i++)
	{
	 LIS_InserirElementoApos( baralho ,carta);
	 baralho->pElemCorr;
	} 
}

void Destruir(void * var )
{
	free(var) ;
}

int _tmain(int argc, _TCHAR* argv[])
{

	//LIS_CriarLista(   ( * carta1 ) ( * pDado ) ) ;
	return 0;
}
