/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTBAR.c
*  Letras identificadoras:      TESTBAR
*
*  Nome da base de software:    teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: INF 1301	Truco
*  Gestor:  DI/PUC-Rio
*  Autores: acgc Arthur Cavalcante Gomes Coelho
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   acgc   08/05/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este mÇodulo contém as funções específicas para o teste do
*     módulo baralho. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     =criar        - chama a função ARV_CriarArvore( )
*     =insdir <Char>
*                   - chama a função ARV_InserirDireita( <Char> )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     "=insesq" <Char>
*                   - chama a função ARV_InserirEsquerda( <Char> )
*     "=irpai"      - chama a função ARV_IrPai( )
*     "=iresq"      - chama a função ARV_IrEsquerda( )
*     "=irdir"      - chama a função ARV_IrDireita( )
*     "=obter" <Char>
*                   - chama a função ARV_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a função ARV_DestruirArvore( )
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include "GENERICO.H"
#include "LERPARM.H"
#include "BARALHO.h"
#include "TST_ESPC.H"

/* Tabela dos nomes dos comandos de teste específicos */
#define CRIAR_BAR_CMD "=criarbaralho"
#define CRIAR_CAR_CMD "=criarcarta"
#define CRIA_VEC_CMD "=criavetor"
#define EMBARALHA_CMD "=embaralhar"
#define DESTRUIR_BAR_CMD "=destruirbaralho"
#define DESTROI_CAR_CMD "=destruircarta"
#define RESET_CARTA_CMD	"=resetvetorcartas"
#define RESET_BAR_CMD	"=resetvetorbaralhos"
#define	CHECA_BARALHOS_CMD "=checabaralhos"


#define DIM_VT_CARTA 10
#define FALSE 0
#define VAZIO 0
#define TRUE 1
#define NAO_VAZIO 1
#define DIM_VT_BAR 10
#define IRRELEVANTE 2

/*****  Dados encapsulados no módulo  *****/
BAR_tppCarta vCartas[DIM_VT_CARTA];
			/* ponteiro para uma carta */
BAR_tppBaralho vBaralhos [DIM_VT_BAR];
			/* vetor de baralhos */
BAR_tppCarta *vec_cartas = NULL;
			/* vetor de cartas */

/***** Protótipos das funções encapuladas no módulo *****/
static int ValidarInxCarta( int inxCarta , int Modo );
static int ValidarInxBaralho( int inxBaralho , int Modo ) ;
/*****  Código das funções exportadas pelo módulo  *****/


/*****************************************************************
******
*
* $FC Função: Efetuar operações de teste específicas para baralho
*
* $EP Parametros
* $P ComandoTeste - String contendo o comando
*
******************************************************************
*****/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
    BAR_tpCondRet CondRetObtido;
	BAR_tpCondRet auxiliar;
    BAR_tpCondRet CondRetEsperada = BAR_CondRetOK;
	int inxcarta,inxbaralho,inxbaralho2;
    char nome_carta;
    int peso_carta, i;
    char naipe_carta[20];
    int NumLidos   = -1;
    TST_tpCondRet Ret ;


	 /* Efetuar reset de teste de cartas */

     if ( strcmp( ComandoTeste , RESET_CARTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_CARTA ; i++ )
            {
               vCartas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de cartas */

	  /* Efetuar reset de teste de cartas */
	 else if ( strcmp( ComandoTeste , RESET_BAR_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_BAR ; i++ )
            {
               vBaralhos[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de cartas */


	/* Testar BAR Criar carta */

    else if( strcmp( ComandoTeste , CRIAR_CAR_CMD ) == 0 )
    {

      NumLidos = LER_LerParametros("icisi",&inxcarta,&nome_carta,&peso_carta,&naipe_carta,&CondRetEsperada);

		if( ( NumLidos != 5 ) || !(ValidarInxCarta( inxcarta , VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */

    CondRetObtido = BAR_CriaCarta(&vCartas[inxcarta],nome_carta,peso_carta,naipe_carta);

    return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                            "Retorno errado ao criar carta." );
	}/* fim ativa: Testar BAR Criar carta */


	/* Testar BAR Destruir carta */
	else if( strcmp( ComandoTeste , DESTROI_CAR_CMD ) == 0)
	{
		 NumLidos = LER_LerParametros("ii",&inxcarta,&CondRetEsperada);

		if ( ( NumLidos != 2 ) || ( ! ValidarInxCarta( inxcarta , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetObtido=DestruirCarta(vCartas[inxcarta]);
		vCartas[inxcarta] = NULL;

		return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                            "Retorno errado ao criar carta." );

	}/* fim ativa: Testar BAR Destruir carta */


	/* Testar BAR Cria vetor de cartas */

	else if( strcmp( ComandoTeste , CRIA_VEC_CMD ) == 0 )
	{
		NumLidos = LER_LerParametros("i",&CondRetEsperada);

		if ( NumLidos != 1 )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetObtido = BAR_CriaVetorCartas(&vec_cartas);

		return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                            "Retorno errado ao construir vetor de cartas." );
	}/* fim ativa: Testar BAR Cria vetor cartas */


	/* Testar BAR Criar baralho */

	else if( strcmp( ComandoTeste , CRIAR_BAR_CMD ) == 0 )
	{
		NumLidos = LER_LerParametros("ii",&inxbaralho,&CondRetEsperada);

		if( ( NumLidos != 2 ) || ( ! ValidarInxBaralho( inxbaralho , VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetObtido = BAR_CriarBaralho(&vBaralhos[inxbaralho]);

		return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                            "Retorno errado ao construir baralho." );
	}/* fim ativa: Testar BAR Criar baralho */


	/* Testar BAR Destruir baralho */
	else if( strcmp( ComandoTeste , DESTRUIR_BAR_CMD ) == 0 )
	{
		NumLidos = LER_LerParametros("ii",&inxbaralho,&CondRetEsperada);

		if( ( NumLidos != 2 ) || (!ValidarInxBaralho(inxbaralho,IRRELEVANTE)))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetObtido = BAR_DestruirBaralho(vBaralhos[inxbaralho]);
		vBaralhos[inxbaralho] = NULL;

		return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                            "Retorno errado ao destruir baralho." );

	}/* fim ativa: Testar BAR Destruir baralho */


	/* Testar BAR Embaralhar */

	else if( strcmp( ComandoTeste , EMBARALHA_CMD ) == 0 )
	{
		NumLidos = LER_LerParametros("ii",&inxbaralho,&CondRetEsperada);

		if( ( NumLidos != 2 )	|| ( ! ValidarInxBaralho( inxbaralho , IRRELEVANTE )))
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetObtido = BAR_Embaralhar(vBaralhos[inxbaralho]);

		return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                            "Retorno errado ao destruir baralho." );
	}/* fim ativa: Testar BAR Embaralhar */

}/********** Fim do módulo de implementação: Módulo de teste específico **********/


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TESTBAR -Validar indice da carta
*
***********************************************************************/
   int ValidarInxCarta( int inxCarta , int Modo )
   {

      if ( ( inxCarta <  0 )
        || ( inxCarta >= DIM_VT_CARTA ))
      {
         return FALSE ;
      } /* if */

      if ( Modo == VAZIO )
      {
         if ( vCartas[ inxCarta ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vCartas[ inxCarta ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */

      return TRUE ;

   } /* Fim Função: TESTBAR -Validar indice de carta */

   /***********************************************************************
   *
   *  $FC Função: TESTBAR -Validar indice do baralho
   *
   ***********************************************************************/
      int ValidarInxBaralho( int inxBaralho , int Modo )
   {

      if ( ( inxBaralho <  0 )
        || ( inxBaralho >= DIM_VT_BAR))
      {
         return FALSE ;
      } /* if */

	  if( Modo == IRRELEVANTE )
		return TRUE ;
      if ( Modo == VAZIO )
      {
         if ( vBaralhos[ inxBaralho ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vBaralhos[ inxBaralho ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */

      return TRUE ;

   } /* Fim função: TESTBAR -Validar indice do baralho */
