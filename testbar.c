#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include "Baralho.h"

static const char ESVAZIA_BARALHO_CMD         [ ] = "=esvaziarbaralho"     ;
static const char DESTRUIR_BARALHO_CMD         [ ] = "=destruirbaralho"     ;
static const char EMBARALHAR_CMD         [ ] = "=embaralhar"     ;
static const char INSERIR_CARTA_CMD         [ ] = "=inserecarta"     ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pValor ) ;

static int ValidarInxBaralho( int inxBaralho , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 baralhos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =embaralhar                   inxLista
*     =destruirbaralho              inxLista
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*
***********************************************************************/



TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int inxLista  = -1 ,
        numLidos   = -1 ,
        CondRetEsp = -1  ;
	    TST_tpCondRet CondRet ;
		char * pDado ;

		int ValEsp = -1 ;

        int i ;

        int numElem = -1 ;

        StringDado[ 0 ] = 0 ;

	

	
	if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

    } /* fim ativa: Testar Destruir lista */
	else if ( strcmp( ComandoTeste , EMBARALHAR_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;
					   
	    if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
		vtListas[ inxLista ] =
                 BAR_NovoBaralhoEmbaralhado() ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;
	
	}/* fim ativa: Testar CriarLista */
	
	/* Testar remover carta */
	else if ( strcmp( ComandoTeste , REMOVER_CARTA_CMD ) == 0 )
	{
		
	}

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {
      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 ) || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;



   }

}