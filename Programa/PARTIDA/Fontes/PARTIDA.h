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
*  $FC Função: PTD  &Cria jogador
*
*  $ED Descrição da função
*     Cria um jogador.
*	  Um jogador é composto por seu nome, por um vetor de cartas inicialmente vazio
*     e um identificador de Equipe
*
*  $EP Parâmetros
*    pJogador    - endereço que vai receber o jogador a ser criado
*
*
*  $FV Valor retornado
*    PTD_CondRetOK           - se tiver criado o jogador com sucesso
*    PTD_CondRetJogadorNaoExiste  - se não tiver conseguido alocar memória para o jogador
*
***********************************************************************/
PTD_tpCondRet PTD_CriaJogador(PTD_tppJogador *jogador, char nome[30]);

/***********************************************************************
*
*  $FC Função: PTD  &Monta equipes
*
*  $ED Descrição da função
*     Aponta um jogador para cada equipe jogador[0]->equipe1 jogador[1]-> equipe2.
*	  Os jogadores pares vao ser da equipe 0, e os impares vao ser da equipe 1
*	  Recebe uma lista de Jogadores e altera sua IdEquipe
*
*  $EP Parâmetros
*    pJogadores    - ponteiro para lista de Jogadores
*	 jogadoresPorEquipe - quantidade de jogadores por equipe
*
*
*  $FV Valor retornado
*    PTD_CondRetOK           - se tiver apontado as equipes corretamente
*    PTD_CondRetListaVazia  - se pJogadores for vazia
*
***********************************************************************/
PTD_tpCondRet PTD_MontaEquipes(LIS_tppLista *pJogadores, int jogadoresPorEquipe);

//PTD_tpCondRet PTD_DefineManilha(BAR_tppBaralho pBaralho);

PTD_tpCondRet PTD_PedeCarta(PTD_tppJogador* jogador); // pede que o jogador selecione uma das suas cartas e remove ela de sua mao

PTD_tpCondRet PTD_DistribuiAsCartas(PTD_tppJogador** jogadores);

void PTD_ImprimeMaos(PTD_tppPartida* pPartida, int numJogadores);

int PTD_InterfacePartida();



#undef PARTIDA_EXT

/********** Fim do módulo de definição: BAR  BARALHO **********/
#else
#endif
