/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.H"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {
	   #ifdef _DEBUG
         CNT_CONTAR( "LIS_CriarLista" ) ;
      #endif

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
		   #ifdef _DEBUG
			CNT_CONTAR( "LIS_CriarLista: Faltou memoria" ) ;
		 #endif
         return NULL ;
      } /* if */
	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_CriarLista: Nao faltou memoria" ) ;
      #endif

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {
	   #ifdef _DEBUG
         CNT_CONTAR( "LIS_DestruirLista" ) ;
      #endif

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {
	   #ifdef _DEBUG
         CNT_CONTAR( "LIS_EsvaziarLista" ) ;
      #endif

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_EsvaziarLista: Liberar elemento") ;
		 #endif
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */
	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_EsvaziarLista: Limpar cabeca" ) ;
      #endif

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {
	    #ifdef _DEBUG
         CNT_CONTAR( "LIS_InserirElementoAntes" ) ;
      #endif

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Lista e NULL" ) ;
		  #endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */
		  #ifdef _DEBUG
         CNT_CONTAR( "LIS_InserirElementoAntes: Lista nao e NULL" ) ;
      #endif

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Inserir elemento em lista vazia" ) ;
			#endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes: Inserir elemento em lista nao vazia" ) ;
			#endif
            if ( pLista->pElemCorr->pAnt != NULL )
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes: Elemento corrente nao e o inicial" ) ;
			   #endif
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes: Elemento corrente e o inicial" ) ;
			   #endif
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {
	   #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos" ) ;
	  #endif

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos: Faltou memoria ao criar elemento" ) ;
			#endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos: Nao faltou memoria ao criar elemento" ) ;
	 	 #endif

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos: Inserir elemento em lista vazia" ) ;
			#endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos: Inserir elemento em lista nao vazia" ) ;
			#endif
			 
            if ( pLista->pElemCorr->pProx != NULL )
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoApos: Elemento corrente nao e final" ) ;
				#endif
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoApos: Elemento corrente e final" ) ;
				#endif
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {
	   #ifdef _DEBUG
			CNT_CONTAR( "LIS_ExcluirElemento" ) ;
	  #endif

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		  
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente nao e o inicial" ) ;
			#endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente e o inicial" ) ;
			#endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente nao e o final" ) ;
			#endif
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento: Elemento corrente e o final" ) ;
			#endif
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {
	    #ifdef _DEBUG
		  CNT_CONTAR( "LIS_ObterValor" ) ;
	    #endif

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		#ifdef _DEBUG
		 CNT_CONTAR( "LIS_ObterValor: Corrente e NULL" ) ;
	    #endif
        return NULL ;
      } /* if */
	  #ifdef _DEBUG
		 CNT_CONTAR( "LIS_ObterValor: Corrente nao e NULL" ) ;
	    #endif

      return pLista->pElemCorr->pValor ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {
	    #ifdef _DEBUG
		  CNT_CONTAR( "LIS_IrInicioLista" ) ;
	    #endif

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {
	   #ifdef _DEBUG
		CNT_CONTAR( "LIS_IrFinalLista" ) ;
	  #endif

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {
	   #ifdef _DEBUG
		CNT_CONTAR( "LIS_AvancarElementoCorrente" ) ;
	  #endif

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancar para frente" ) ;
			#endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
				 #ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancou elemento" ) ;
			   #endif
               if ( pElem == NULL )
               {
				    #ifdef _DEBUG
						CNT_CONTAR( "LIS_AvancarElementoCorrente: Chegou no final da lista" ) ;
				  #endif
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Terminou de avancar elemento" ) ;
			#endif

            if ( pElem != NULL )
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao chegou no final da lista" ) ;
			   #endif
			   
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */
			
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Elemento final vira o corrente" ) ;
			#endif

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {
			 #ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Avancar para tras" ) ;
			#endif

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
				 #ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Voltou elemento" ) ;
			   #endif
               if ( pElem == NULL )
               {
				   #ifdef _DEBUG
						CNT_CONTAR( "LIS_AvancarElementoCorrente: Chegou no inicio da lista" ) ;
				  #endif
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */
			
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Terminou de voltar elemento" ) ;
			#endif

            if ( pElem != NULL )
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao chegou no inicio da lista" ) ;
			   #endif
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */
			
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Elemento inicial vira o corrente" ) ;
			#endif

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */
		 
		 #ifdef _DEBUG
				CNT_CONTAR( "LIS_AvancarElementoCorrente: Nao avanca elemento" ) ;
		 #endif

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {
	    #ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor" ) ;
	  #endif

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		  #ifdef _DEBUG
		   CNT_CONTAR( "LIS_ProcurarValor: Lista esta vazia" ) ;
	      #endif
         return LIS_CondRetListaVazia ;
      } /* if */
	  
	  IrInicioLista(pLista);

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
		  #ifdef _DEBUG
			CNT_CONTAR( "LIS_ProcurarValor: Procurar no elemento" ) ;
		  #endif
         if ( pElem->pValor == pValor )
         {
			#ifdef _DEBUG
			  CNT_CONTAR( "LIS_ProcurarValor: Achou valor" ) ;
		    #endif
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */
	   #ifdef _DEBUG
		CNT_CONTAR( "LIS_ProcurarValor: Nao achou" ) ;
	  #endif

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {
	   #ifdef _DEBUG
		 CNT_CONTAR( "LiberarElemento" ) ;
	  #endif

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
		  #ifdef _DEBUG
			CNT_CONTAR( "LiberarElemento: Excluiu valor" ) ;
		 #endif
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */
	  #ifdef _DEBUG
		 CNT_CONTAR( "LiberarElemento: Liberou elemento" ) ;
	  #endif
	  

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {
	   #ifdef _DEBUG
		 CNT_CONTAR( "CriarElemento" ) ;
	  #endif

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
		  #ifdef _DEBUG
				CNT_CONTAR( "CriarElemento: Faltou memoria ao criar elemento" ) ;
		 #endif
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;
	  
	   #ifdef _DEBUG
			CNT_CONTAR( "CriarElemento: Criou elemento com sucesso" ) ;
	  #endif

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {
	    #ifdef _DEBUG
		CNT_CONTAR( "LimparCabeca" ) ;
	  #endif

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */



/***********************************************************************
*
*  $FC Função: LIS  -Retorna ponteiro corrente da lista
*
***********************************************************************/
   void *retorna_corrente(LIS_tppLista pLista)
   {
	   return pLista->pElemCorr->pValor;
   }/* Fim função: LIS  -Retorna corrente */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

