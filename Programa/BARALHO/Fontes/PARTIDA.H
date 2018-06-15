#if ! defined( PARTIDA_ )
#define PARTIDA_
/***************************************************************************
*
*  $MCD Módulo de definição: PRT  PARTIDA
*
*  Arquivo gerado:              PARTIDA.h
*  Letras identificadoras:      PRT
*
*  Projeto: INF 1301 / Truco
*  Gestor:  DI/PUC-Rio
*  Autores: Arthur Cavalcante Gomes Coelho(acgc)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       acgc   30/04/2018 início desenvolvimento
*
*  $ED Descrição do módulo
*     Criacao dos jogadores
*     Divisao das Equipes
*     Definicao da manilha fixa
*     Definicao da pontuacao das Cartas
*     Inicializacao de partida
*     Execucao de Rodada
*     Jogada para cada jogador ( com opcoes de pedir truco, etc ... )
*     Manutencao do Placar
*
***************************************************************************/

#include   "LISTA.H"
#include   "BARALHO.h"

#if defined( PARTIDA_OWN )
   #define PARTIDA_EXT
#else
   #define PARTIDA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um baralho */

typedef struct PTD_tagPartida * PTD_tppPartida;

typedef struct PTD_tagJogador * PTD_tppJogador;



/***********************************************************************
*
*  $TC Tipo de dados: PTD Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo BARALHO
*
***********************************************************************/

typedef enum {

      PTD_CondRetOK ,
            /* Concluiu corretamente */

      PTD_CondRetListaVazia ,
            /* A lista n�o cont�m elementos */

      PTD_CondRetFaltouMemoria,
            /* Faltou mem�ria ao tentar criar um elemento de lista */

     PTD_CondRetCartaNaoCriada,
         /* Nao foi possivel criar o ponteiro Carta */
     PTD_CondRetBaralhoNaoExiste,
         /* Ponteiro para baralho vazio */
     PTD_CondRetTamanhoErrado,
         /* Tamanho da lista de cartas errado */
      PTD_FalhaNoEmbaralhamento,
            /* Nao conseguimos remover uma carta do baralho antigo durante o processo de embaralhamento */
     PTD_CondRetJogadorNaoExiste
} PTD_tpCondRet ;

PTD_tpCondRet PTD_CriaJogador(PTD_tppJogador jogador); // acho que precisa ser mesmo ponteiro pra ponteiro, porque quero que a mudanca persista

PTD_tpCondRet PTD_MontaEquipes(PTD_tppJogador* jogadores, int jogadoresPorEquipe);

PTD_tpCondRet PTD_DefineManilha(BAR_tppBaralho pBaralho);

PTD_tpCondRet PTD_PedeCarta(PTD_tppJogador* jogador); // pede que o jogador selecione uma das suas cartas e remove ela de sua mao

PTD_tpCondRet PTD_DistribuiAsCartas(PTD_tppJogador** jogadores);





#undef PARTIDA_EXT

/********** Fim do módulo de definição: BAR  BARALHO **********/
#else
#endif
