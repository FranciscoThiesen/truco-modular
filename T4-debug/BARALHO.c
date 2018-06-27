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


#ifdef _DEBUG
	#include   "CESPDIN.H"
	#include   "GENERICO.h"
	#include   "CONTA.h"
	#include   "..\\Tabelas\\IdTiposEspaco.def"
#endif


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
	#ifdef _DEBUG
				CNT_CONTAR( "DestruirValor" ) ;
			#endif
	
	
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
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriaCarta" ) ;
			#endif
			
	*pCarta = (BAR_tppCarta)malloc(sizeof(BAR_tpCarta));
	if(*pCarta == NULL)
	{
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriaCarta: Faltou memoria" ) ;
			#endif
			
		return BAR_CondRetFaltouMemoria;
	}
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriaCarta:Nao faltou memoria" ) ;
			#endif
	
	(*pCarta)->nome=nome;
	strcpy((*pCarta)->naipe,naipe);
	(*pCarta)->peso=peso;
	return BAR_CondRetOK;
	
}/* Fim função: BAR  &Criar carta */

/***************************************************************************
*
*  Função: BAR  &Destruir carta
*  ****/
BAR_tpCondRet BAR_DestruirCarta(BAR_tppCarta pCarta)
{
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_DestruirCarta:" ) ;
			#endif
	
	free(pCarta);
	return BAR_CondRetOK;
}/* Fim função: BAR  &Destruir carta */

/***************************************************************************
*
*  $FC Função: BAR  &Criar Baralho
*  ****/
BAR_tpCondRet BAR_CriarBaralho(BAR_tppBaralho *pBaralho)
{
	
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:" ) ;
			#endif
	
	
	int i;
	BAR_tppCarta pcarta;
	BAR_tppCarta *vetor_cartas=NULL;
	BAR_tpCondRet retorno;

	//ponteiro para baralho
	*pBaralho = (BAR_tpBaralho*)malloc(sizeof(BAR_tpBaralho));
	if ( *pBaralho == NULL )
	{
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:faltou memoria" ) ;
			#endif
		
		return  BAR_CondRetFaltouMemoria ;
	}
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Nao faltou memoria" ) ;
			#endif
	
	
	//cria as 40 cartas e armazena em um vetor
	retorno = BAR_CriaVetorCartas(&vetor_cartas);

	(*pBaralho)->Cartas = LIS_CriarLista((void (*) (void *pDado))BAR_DestruirCarta);

	if((*pBaralho)->Cartas==NULL)
	{
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Faltou memoria para as cartras" ) ;
			#endif
		
		return BAR_CondRetFaltouMemoria;
	}
	
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Nao faltou memoria para as cartras" ) ;
			#endif
	
	

	for(i=0;i<TRUCO;i++)
	{
		#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Cartas inseridas no baralho" ) ;
			#endif
		
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
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriaVetorCartas:" ) ;
			#endif
	
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
		#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriaVetorCartas:Faltou memoria" ) ;
			#endif
		
		return BAR_CondRetFaltouMemoria;
	}
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriaVetorCartas:Nao falotu memoria" ) ;
			#endif
	

	for(i = 0; i < 40; ++i)
	{
		
		#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriaVetorCartas:Atribuicao de peso" ) ;
			#endif
		
		//printf(" valor = %c, naipe = %s \n\n", valores[i/4], naipe[i%4]);
		if(valores[i/4] == '4' && strcmp(naipe[i%4], "paus") == 0) 
		{
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:4 Paus" ) ;
			#endif
			
			
			peso = 14;
		}
		else if(valores[i/4]== '7' && strcmp(naipe[i%4], "copas") == 0)
		{ 
	
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:7 Copas" ) ;
			#endif
			
			peso = 13;
		}
		else if(valores[i/4] == 'A' && strcmp(naipe[i%4], "espadas") == 0)
		{
			#ifdef _DEBUG
				CNT_CONTAR("BAR_CriarBaralho:A Espadas") ;
			#endif

			peso = 12;
		}
		else if(valores[i/4] == '7' && strcmp(naipe[i%4], "ouros") == 0)
		{ 
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:7 Ouros" ) ;
			#endif
			
			peso = 11;
		}
		else if(valores[i/4] == '3')
		{
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor 3" ) ;
			#endif
			
			peso = 10;
		}
		else if(valores[i/4] == '2')
		{ 
				#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor 2" ) ;
			#endif
	
			peso = 9;
		}
		else if(valores[i/4] == 'A')
		{ 
	
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor A" ) ;
			#endif
	
			peso = 8;
		}
		else if(valores[i/4] == 'K')
		{ 
	
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor K" ) ;
			#endif
			peso = 7;
		}
		else if(valores[i/4] == 'J')
		{
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor J" ) ;
			#endif
			
			peso = 6;
		}
		else if(valores[i/4] == 'Q')
		{ 
	
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor Q" ) ;
			#endif
	
			peso = 5;
		}
		else if(valores[i/4] == '7')
		{
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor 7" ) ;
			#endif
			
			peso = 4;
		}
		else if(valores[i/4] == '6')
		{
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor 6" ) ;
			#endif
			
			peso = 3;
		}
		else if(valores[i/4] == '5')
		{
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor 5" ) ;
			#endif
			
			peso = 2;
		}
		else if(valores[i/4] == '4')
		{
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Valor 4" ) ;
			#endif
			
			peso = 1;
		}
		retorno = BAR_CriaCarta(&carta, valores[i/4], peso, naipe[i%4]);
		if(retorno != BAR_CondRetOK)
		{ 
	
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Retorno nao OK" ) ;
			#endif
	
			return retorno;
		}
		
		#ifdef _DEBUG
				CNT_CONTAR( "BAR_CriarBaralho:Retorno igual a CondRetOK" ) ;
			#endif

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
	   
	   
	   #ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:" ) ;
			#endif
	   

	   int i = -1; //tamBaralho = -1;
	   
	   LIS_tppLista pListaDestino = NULL;

       if( pBaralho == NULL )
	   {
		   
		   #ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Baralho nao existe") ;
			#endif
		   
		   return BAR_CondRetBaralhoNaoExiste ;
	   }
	   
	   #ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Baralho existe" ) ;
			#endif
	   
	   
	   pListaDestino=LIS_CriarLista((void (*) (void *pDado))BAR_DestruirCarta);
	   
	   if(pListaDestino==NULL)
	   {
		   #ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Faltou memoria" ) ;
			#endif
		   
		   return BAR_CondRetFaltouMemoria;
	   }
	   
	   
	   #ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Nao faltou memoria" ) ;
			#endif
	   
	   IrInicioLista( pListaDestino );

	   srand((unsigned) time(NULL));

	   for(i = 40; i > 0; i--)
	   {
		   
		   #ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Sorteio para embaralhamento" ) ;
			#endif
		   
			BAR_tppCarta corrente,copia;
			LIS_tpCondRet condRetLis;
			int inxCarta = rand() % i;							/* Sorteia uma carta */

			IrInicioLista( pBaralho->Cartas );					/* Inicio do baralho */

			if( LIS_AvancarElementoCorrente( pBaralho->Cartas, inxCarta ) != LIS_CondRetOK )	/* Vai para a carta sorteada */
			{
				
				#ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Tamanho errado" ) ;
			#endif
				
				
				return BAR_CondRetTamanhoErrado;
			}
			
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Tamanho certo" ) ;
			#endif
			

			corrente = (BAR_tppCarta) retorna_corrente(pBaralho->Cartas);

			

			BAR_CriaCarta(&copia, corrente->nome, corrente->peso, corrente->naipe);

			condRetLis = LIS_InserirElementoApos(pListaDestino,copia);

			if( condRetLis == LIS_CondRetListaVazia )
			{
				
				
				#ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Lista vazia" ) ;
			#endif
				
				
				return BAR_CondRetListaVazia;
			}
			else if( condRetLis == LIS_CondRetFaltouMemoria )
			{
				
				#ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Faltou memoria" ) ;
			#endif
				
				
			    return BAR_CondRetFaltouMemoria;
			}
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Nao eh vazia nem faltou memoria" ) ;
			#endif
			
			
			if( LIS_ExcluirElemento(pBaralho->Cartas) != LIS_CondRetOK)
			{
				
				#ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Falha no embaralhamento" ) ;
			#endif

				return BAR_FalhaNoEmbaralhamento;
			}	
			
			
			#ifdef _DEBUG
				CNT_CONTAR( "BAR_Embaralhar:Embaralhamento nao falhou" ) ;
			#endif
			
	   }

	   LIS_DestruirLista( pBaralho->Cartas );	/*Destrói a lista antiga*/

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
	   
	   
	   #ifdef _DEBUG
				CNT_CONTAR( "BAR_DestruirBaralho:" ) ;
			#endif
	   

      if( pBaralho == NULL )
	  {
		  
		    #ifdef _DEBUG
				CNT_CONTAR( "BAR_DestruirBaralho:Baralho nulo" ) ;
			#endif
		  
		  free(pBaralho) ;
		  return BAR_CondRetOK ;
		  
	  }
	  
	        #ifdef _DEBUG
				CNT_CONTAR( "BAR_DestruirBaralho:Baralho nao nulo" ) ;
			#endif
	  

      if(pBaralho->Cartas != NULL)
	  {
		  
		    #ifdef _DEBUG
				CNT_CONTAR("BAR_DestruirBaralho:Cartas do baralho nao nulo") ;
			#endif
		  
		  
		  LIS_DestruirLista( pBaralho->Cartas ) ;
	  }
	  
	  #ifdef _DEBUG
				CNT_CONTAR( "BAR_DestruirBaralho:Cartas nulas" ) ;
			#endif

      free( pBaralho ) ;

	  return BAR_CondRetOK;

   } /* Fim função: EMB  &Destruir baralho */

BAR_tpCondRet BAR_RemoveCartaDoBaralho( BAR_tppBaralho pBaralho, BAR_tppCarta* pCarta)
{
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_RemoveCartaDoBaralho:" ) ;
			#endif
	
	
	
	int res;
	BAR_tppCarta auxiliar;
	//*pCarta = (BAR_tppCarta)malloc(sizeof(BAR_tpCarta));
	if(*pCarta == NULL)
	{
		
		#ifdef _DEBUG
				CNT_CONTAR( "BAR_RemoveCartaDoBaralho:Faltou memoria" ) ;
			#endif
		
		
		return BAR_CondRetFaltouMemoria;
	}
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_RemoveCartaDoBaralho:Nao faltou memoria" ) ;
			#endif
	
	auxiliar = (BAR_tppCarta) LIS_ObterValor(pBaralho->Cartas);

	(*pCarta)->nome = auxiliar->nome;
	strcpy((*pCarta)->naipe,auxiliar->naipe);
	(*pCarta)->peso = auxiliar->peso;

	res = LIS_ExcluirElemento(pBaralho->Cartas);

	if(res != LIS_CondRetOK) 
	{
		
		#ifdef _DEBUG
				CNT_CONTAR( "BAR_RemoveCartaDoBaralho:Lista vazia" ) ;
			#endif
		
		
		return BAR_CondRetListaVazia;
	}
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_RemoveCartaDoBaralho:Lista nao vazia" ) ;
			#endif
	
	

	return BAR_CondRetOK;
}

char *GetNaipe(BAR_tppCarta carta);
int GetPeso(BAR_tppCarta carta);
char GetNome(BAR_tppCarta carta);

void BAR_ImprimeBaralho(BAR_tppBaralho pBaralho)
{
	
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_ImprimeBaralho:" ) ;
			#endif
	
	
	int i;
	
	IrInicioLista( (LIS_tppLista) pBaralho->Cartas);

	for(i = 0; i < 40; ++i) 
	{
		
		
		#ifdef _DEBUG
				CNT_CONTAR( "BAR_ImprimeBaralho:Cartas impresas" ) ;
			#endif
		
		
		BAR_tppCarta corrente =  (BAR_tppCarta) LIS_ObterValor(pBaralho->Cartas) ;
		LIS_AvancarElementoCorrente( (LIS_tppLista) pBaralho->Cartas, 1);
		printf("%c	-	%s	-	%d\n",GetNome(corrente) ,GetNaipe(corrente), GetPeso(corrente));
	}
}

char *GetNaipe(BAR_tppCarta carta)
{
	
	#ifdef _DEBUG
				CNT_CONTAR( "GetNaipe:" ) ;
			#endif
	
	
	char *naipe = (char*)malloc(sizeof(20*sizeof(char)));
	strcpy(naipe,carta->naipe);
	return naipe;
}

int GetPeso(BAR_tppCarta carta)
{
	
	#ifdef _DEBUG
				CNT_CONTAR( "GetPeso:" ) ;
			#endif
	
	return carta->peso;
}

char GetNome(BAR_tppCarta carta)
{
	
	#ifdef _DEBUG
				CNT_CONTAR( "GetNome:" ) ;
			#endif
	
	
	return carta->nome;
}

void BAR_ImprimeCarta(BAR_tppCarta carta)
{
	
	#ifdef _DEBUG
				CNT_CONTAR( "BAR_ImprimeCarta:" ) ;
			#endif
	
	
	printf("naipe=%s\tpeso=%d\tnome=%c\n", carta->naipe, carta->peso, carta->nome);
}


/********** Fim do módulo de implementação: BAR  BARALHO **********/