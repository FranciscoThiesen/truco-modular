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
*	  Módulo principal encarregado de:
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

#define NOMEMAXIMO 30

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
     PTD_CondRetJogadorNaoExiste,
	 /* Nao conseguimos acessar o ponteiro referente ao jogador desejado, este deve ser NULL ou lixo */
	 PTD_CondRetPartidaNaoCriada,
	 /* Nao foi possivel criar uma partida */
} PTD_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PTD  &Cria partida
*
*  $ED Descrição da função
*     Recebe um ponteiro para a partida que será alocado na função
*	  e o numero de jogadores que irão participar do jogo,
*	  chama as funções: PTD_CriaListaJogadores e PTD_MontaEquipes
*	  já documentadas anteriormente. retorna PTD_CondRetOK se conseguiu
*	  criar uma partida inicial.
*
*  $EP Parâmetros
*    n_jogadores    - numero de jogadores
*	 pPartida - ponteiro para a Partida a ser criada
*
*  $FV Valor retornado
*    PTD_CondRetOK           - criou a partida sem problemas
*    PTD_CondRetListaVazia  - se se nao foi possivel inserir um jogador
*	 PTD_CondRetJogadorNaoExiste - se nao foi possivel criar um Jogador
*	 PTD_CondRetFaltouMemoria  - se nao foi possivel alocar memoria para
*	 a lista ou para a criacao de um jogador
*
***********************************************************************/
PTD_tpCondRet PTD_CriaPartida(PTD_tppPartida *pPartida, int n_jogadores);


PTD_tpCondRet PTD_PedeCarta(PTD_tppJogador* jogador); // pede que o jogador selecione uma das suas cartas e remove ela de sua mao


void PTD_ImprimeMaos(PTD_tppPartida* pPartida, int numJogadores);

int PTD_InterfacePartida();



#undef PARTIDA_EXT

/********** Fim do módulo de definição: BAR  BARALHO **********/
#else
#endif
