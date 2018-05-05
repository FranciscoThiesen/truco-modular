#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include "Baralho.h"

static const char CRIAR_BARALHO_CMD         [ ] = "=criarbaralho"     ;
static const char ESVAZIA_BARALHO_CMD         [ ] = "=esvaziarbaralho"     ;
static const char DESTRUIR_BARALHO_CMD         [ ] = "=destruirbaralho"     ;
static const char EMBARALHAR_CMD         [ ] = "=embaralhar"     ;
static const char ADICIONAR_CARTA_CMD         [ ] = "=adicionarcarta"     ;
static const char ACHAR_CARTA_CMD         [ ] = "=acharcarta"     ;
static const char REMOVER_CARTA_CMD         [ ] = "=removercarta"     ;
static const char TIRAR_VIRA_CMD         [ ] = "=tirarvira"     ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   40
#define DIM_VALOR     100

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 )
	{
	
	}
	else if ( strcmp( ComandoTeste , ESVAZIA_BARALHO_CMD ) == 0 )
	{
	
	}
	else if ( strcmp( ComandoTeste , DESTRUIR_BARALHO_CMD ) == 0 )
	{
	
	}
	else if ( strcmp( ComandoTeste , EMBARALHAR_CMD ) == 0 )
	{
	
	}
	else if ( strcmp( ComandoTeste , ADICIONAR_CARTA_CMD ) == 0 )
	{
	
	}
	else if ( strcmp( ComandoTeste , ACHAR_CARTA_CMD ) == 0 )
	{
	
	}
	else if ( strcmp( ComandoTeste , REMOVER_CARTA_CMD ) == 0 )
	{
	
	}
	else if ( strcmp( ComandoTeste , TIRAR_VIRA_CMD ) == 0 )
	{
	
	}
}