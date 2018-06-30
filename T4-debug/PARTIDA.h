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
*           Francisco Geiman Thiesen (fgt)
*  $HA Histórico de evolução:
*     Versão  Autores    Data       Observações
*     1       acgc,fgt   30/04/2018 início desenvolvimento
*
*  $ED Descrição do módulo
*	  Módulo principal encarregado de:
*     Criacao dos jogadores
*     Divisao das Equipes
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

/***********************************************************************
*
*  $FC Função: PTD & Interface Partida
*  
*  $ED Descrição da função
*    Essa funcao é responsável por orquestrar a realização de uma partida de
*    truco.
*
*  $EP Parâmetros
*    - Não possui
*
*  $FV Valor retornado
*    PTD_CondRetOK               - A partida foi realizada com sucesso
*    PTD_CondRetListaVazia       - Se a lista de jogadores ou o baralho se encontram vazios
*    PTD_CondRetJogadorNaoExiste - Se algum dos jogadores não existe durante a partida
*    PTD_CondRetFaltouMemoria    - Se não foi possível alocar a memória necessária para a execução da partida
*    PTD_CondRetCartaNaoCriada   - Erro na criação de alguma carta do baralho
*    PTD_CondRetTamanhoErrado    - Alguma das listas essenciais para a execução da partida não possui o tamanho correto
*    PTD_FalhaNoEmbaralhamento   - Erro na hora de embaralhar o baralho em algum momento da partida.
*    PTD_CondRetPartidaNaoCriada - Falha na criacao da partida
*
**********************************************************************/
PTD_tpCondRet PTD_InterfacePartida();


#undef PARTIDA_EXT

/********** Fim do módulo de definição: BAR  BARALHO **********/
#else
#endif
