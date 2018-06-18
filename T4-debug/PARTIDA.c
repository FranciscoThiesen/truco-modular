/***************************************************************************
*  $MCI Módulo de implementação: PTD PARTIDA
*
*  Arquivo gerado:              PARTIDA.c
*  Letras identificadoras:      PTD
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

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "BARALHO.h"
#include "LISTA.H"
#include "PARTIDA.H"


#define PARTIDA_OWN
	#include "PARTIDA.h"
#undef PARTIDA_OWN

#define	TRUCO 40
#define NOMEMAXIMO 30

/***********************************************************************
*
*  $TC Tipo de dados: BAR Carta
*
*
***********************************************************************/
typedef struct PTD_tagJogador{
	char nome[NOMEMAXIMO];
	BAR_tppCarta mao[3];
	int idEquipe;

} PTD_tpJogador;

typedef struct PTD_tagPartida {
	LIS_tppLista Jogadores;
	int placar[2];
	BAR_tppBaralho Baralho;
	BAR_tppCarta manilhas[4];
} PTD_tpPartida;


PTD_tpCondRet DestruirJogador(PTD_tppJogador pJogador)
{
	free(pJogador);
	return PTD_CondRetOK;
}

/***********************************************************************
*
*  $TC Tipo de dados: BAR Baralho
*
*
***********************************************************************/


void PTD_ImprimeJogadores(LIS_tppLista *pJogadores)
{
	LIS_tpCondRet retorno;
	PTD_tppJogador jogador;
	IrInicioLista(*pJogadores);
	jogador = (PTD_tppJogador) ( LIS_ObterValor(*pJogadores));
	retorno = LIS_CondRetListaVazia;
	while(retorno != LIS_CondRetFimLista)
	{	
		printf("%s %d \n",jogador->nome,jogador->idEquipe );
		retorno = LIS_AvancarElementoCorrente(*pJogadores,1);
		//assertiva
		jogador = (PTD_tppJogador) ( LIS_ObterValor(*pJogadores));
	}
}

PTD_tpCondRet PTD_CriaJogador(PTD_tppJogador *jogador, char nome[30])
{
	*jogador = (PTD_tppJogador)malloc(sizeof(PTD_tpJogador));
	if( (*jogador) == NULL ) return PTD_CondRetJogadorNaoExiste;
	strcpy((*jogador)->nome, nome);
	return PTD_CondRetOK;
}

PTD_tpCondRet PTD_CriaListaJogadores(int n_jogadores,LIS_tppLista *pJogadores, char nomes[10][1][NOMEMAXIMO])
{
	int i;
	LIS_tpCondRet CondRetLista;
	PTD_tpCondRet CondRetJogador;
	PTD_tppJogador pJogador;
	*pJogadores = LIS_CriarLista((void (*) (void *pDado))DestruirJogador);
	//assertiva	
	for(i=0;i<n_jogadores;i++)
	{
		CondRetJogador = PTD_CriaJogador(&pJogador,nomes[i][1]);
		//assertiva
		CondRetLista = LIS_InserirElementoApos(*pJogadores,pJogador);
		//assertiva
	}
	IrInicioLista(*pJogadores);
	//assertiva
	return PTD_CondRetOK;
}


PTD_tpCondRet PTD_MontaEquipes(LIS_tppLista *pJogadores, int jogadoresPorEquipe)
{
	// vou colocar uma assertiva so pra lembrarmos disso
	// assert(jogadoresPorEquipe == 1 || jogadoresPorEquipe == 2 || jogadoresPorEquipe == 3)
	int i;
	PTD_tppJogador jogador;
	// os jogadores pares vao ser da equipe 0, e os impares vao ser da equipe 1
	// o parametro teve que ser ponteiro de ponteiro, porque minha funcao altera um campo de um ponteiro ja criado.
	if(pJogadores == NULL)  PTD_CondRetListaVazia; //se lista == NULL
	IrInicioLista(*pJogadores);
	for(i = 0; i < 2 * jogadoresPorEquipe; ++i)
	{
		jogador=(PTD_tppJogador) LIS_ObterValor(*pJogadores);				
		jogador->idEquipe = i % 2;
		LIS_AvancarElementoCorrente(*pJogadores,1);

	}
	return PTD_CondRetOK;
}
/*
PTD_tpCondRet PTD_DefineManilha(PTD_tppPartida* pPartida)
{
	int ret = BAR_RemoveCartaDoBaralho( (*pPartida)->baralho, (*pPartida)->manilha);
	if( ret != BAR_CondRetOK) return PTD_CondRetBaralhoNaoExiste;
	return PTD_CondRetOK;
}
*/

PTD_tpCondRet PTD_CriaPartida(PTD_tppPartida *pPartida, int n_jogadores)
{
	int i, ret;
	char nomes[10][1][NOMEMAXIMO]; // char string_matrix[ROWS][COLUMNS][STRING_LENGTH]
	*pPartida = (PTD_tppPartida) malloc(sizeof(PTD_tpPartida));


	(*pPartida)->placar[0] = (*pPartida)->placar[1] = 0;
	//assertiva

	for( i = 0; i < n_jogadores; ++i)
	{
		printf("Digite o nome do %d-esimo jogador\n", i);
		scanf("%s", nomes[i][1]);
	}

	//Cria Lista de Jogadores
	ret = PTD_CriaListaJogadores(n_jogadores,&(*pPartida)->Jogadores, nomes);
	//assert

	//Aponta cada jogador a uma equipe
	ret = PTD_MontaEquipes(&(*pPartida)->Jogadores,3);
	//assert

	//Cria o baralho
	ret = BAR_CriarBaralho(&(*pPartida)->Baralho);
	//assert
	
	/*
	falta criar as manilhas
	*/
	return PTD_CondRetOK;
}


int main()
{
	int retorno,resposta;
	//BAR_tppCarta *cartas=NULL;
	//BAR_tppBaralho Baralho;
	//BAR_tppCarta carta = NULL;
	PTD_tppPartida novaPartida;

	/*
	if(BAR_CriaCarta(&carta,'a',10,"ouros")==BAR_CondRetOK)
	{
		printf("sucesso em criar uma carta!\n");
	}
	//retorno=DestruirCarta(*carta);
	retorno=BAR_CriaVetorCartas(&cartas);

	if(retorno==BAR_CondRetOK) printf("sucesso\n");

	retorno = BAR_CriarBaralho(&Baralho);
	if(retorno==BAR_CondRetOK) printf("sucesso\n");

	BAR_Embaralhar(Baralho);

	BAR_ImprimeBaralho(Baralho);
	*/


	PTD_CriaPartida(&novaPartida, 6);

	printf("\nImprimindo os Jogadores e suas respectiovas equipes:\n");
	PTD_ImprimeJogadores(&novaPartida->Jogadores);

	printf("Imprimindo Baralho de partida, nao embaralhado:\n");
	BAR_ImprimeBaralho(novaPartida->Baralho);

	BAR_Embaralhar(novaPartida->Baralho);

	printf("Deseja imprimir o baralho de Partida embaralhado?\n1 = Sim\n0 = Nao\n");
	scanf("%d",&resposta);

	if(resposta == 1)
	{
		BAR_ImprimeBaralho(novaPartida->Baralho);
	}
	return 0;
}
