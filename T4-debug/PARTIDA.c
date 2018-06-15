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
	PTD_tppJogador* jogadores;
	int placar[2];
	BAR_tppBaralho baralho;
	BAR_tppCarta manilha;
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

PTD_tpCondRet PTD_CriaJogador(PTD_tppJogador* jogador, char nome[30])
{
	if( (*jogador) == NULL ) return PTD_CondRetJogadorNaoExiste;
	strcpy((*jogador)->nome, nome);
	return PTD_CondRetOK;
}

PTD_tpCondRet PTD_CriaListaJogadores(int n_jogadores)
{
	int i;
	LIS_tpCondRet CondRetLista;
	PTD_tpCondRet CondRetJogador;
	PTD_tppJogador pJogador;
	LIS_tppLista jogadores;
	jogadores = LIS_CriarLista((void (*) (void *pDado))DestruirCarta);
	
	for(i=0;i<n_jogadores;i++)
	{
		CondRetJogador = PTD_CriaJogador(&pJogador,"default");
		CondRetLista = LIS_InserirElementoApos(jogadores,pJogador);
	}
	return PTD_CondRetOK;
}

/*
PTD_tpCondRet PTD_MontaEquipes(LIS_tppLista jogadores, int jogadoresPorEquipe)
{
	// vou colocar uma assertiva so pra lembrarmos disso
	// assert(jogadoresPorEquipe == 1 || jogadoresPorEquipe == 2 || jogadoresPorEquipe == 3)
	int i;

	// os jogadores pares vao ser da equipe 0, e os impares vao ser da equipe 1
	// o parametro teve que ser ponteiro de ponteiro, porque minha funcao altera um campo de um ponteiro ja criado.
	for(i = 0; i < 2 * jogadoresPorEquipe; ++i)
	{
		if(jogadores == NULL)  PTD_CondRetListaVazia; //se lista == NULL
		(PTD_tppJogador) LIS_ObterValor(jogadores);				//(*jogadores[i])->idEquipe = i % 2;

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
/*
PTD_tpCondRet PTD_CriaPartida(PTD_tppPartida pPartida, int numeroDeJogadores)
{
	int i, ret;
	PTD_tppPartida novaPartida = (PTD_tppPartida) malloc(sizeof(PTD_tpPartida));
	novaPartida->placar[0] = novaPartida->placar[1] = 0;
	novaPartida->jogadores = (PTD_tppJogador*) malloc(numeroDeJogadores * sizeof(PTD_tppJogador) );
	char nome[NOMEMAXIMO];
	for( i = 0; i < numeroDeJogadores; ++i)
	{
		printf("Digite o nome do %d-esimo jogador\n", i);
		scanf("%s", nome);
		if(PTD_CriaJogador(&(novaPartida->jogadores[i]), nome) != PTD_CondRetOK)
		{
			return PTD_CondRetJogadorNaoExiste;
		}
	}
	if(PTD_MontaEquipes(&(novaPartida->jogadores), numeroDeJogadores) != PTD_CondRetOK)
	{
		return PTD_CondRetJogadorNaoExiste;
	}

	// se o if logo abaixo tiver algum problema eu posso ter uma ideia do que eh - Francisco
	if(BAR_CriarBaralho(&(novaPartida->baralho)) != BAR_CondRetOK)
	{
		return PTD_CondRetFaltouMemoria;
	}
	if(BAR_Embaralhar(novaPartida->baralho) != BAR_CondRetOK) return PTD_CondRetBaralhoNaoExiste;

	if(PTD_DefineManilha(&novaPartida) != PTD_CondRetOK) return PTD_CondRetBaralhoNaoExiste;

	pPartida = novaPartida;

	return PTD_CondRetOK;
}
*/
int main()
{
	int retorno;
	BAR_tppCarta *cartas=NULL;
	BAR_tppBaralho Baralho=(BAR_tppBaralho)malloc(sizeof(BAR_tppBaralho));
	BAR_tppCarta carta = NULL;

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

	return 0;
}
