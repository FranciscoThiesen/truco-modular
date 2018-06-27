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
	// ret = BAR_CriarBaralho(&(*pPartida)->Baralho);
	//assert
	
	/*
	falta criar as manilhas
	*/
	return PTD_CondRetOK;
}


static void print_funcoes(PTD_tppPartida pPartida)
{
	int control = 1;

	while(control)
	{
		printf("1-Imprimir Jogadores\t2-Imprimir Baralho\t0-Sair\n\n");
		scanf("%d",&control);

		switch(control)
		{
		case 1:
			printf("\nImprimindo os Jogadores e suas respectiovas equipes:\n");
			PTD_ImprimeJogadores(&pPartida->Jogadores);
			break;
		case 2:
			printf("Imprimindo Baralho de partida, nao embaralhado:\n");
			BAR_ImprimeBaralho(pPartida->Baralho);
			break;
		}
	}
}


PTD_tpCondRet PTD_DistribuiCartas(PTD_tppPartida *pPartida, int numJogadores) //assume que o baralho esteja embaralhado
{
	int i, j, contador = 0;
	BAR_tppCarta pCarta[40];
	PTD_tppJogador pJogador;
	IrInicioLista((*pPartida)->Jogadores);
	for(j = 0; j < numJogadores; ++j)
	{
		for(i=0;i<3;i++)
		{
			BAR_CriaCarta(&pCarta[contador],'a',0,"default");
			BAR_RemoveCartaDoBaralho((*pPartida)->Baralho, &pCarta[contador]);
			pJogador = (PTD_tppJogador) LIS_ObterValor( (*pPartida)->Jogadores );
			pJogador->mao[i] = pCarta[contador++];
		}
		LIS_AvancarElementoCorrente((*pPartida)->Jogadores,1);
	}
	
	//assert(LIS_AvancarElementoCorrente((*pPartida)->Jogadores,1) == LIS_CondRetFimLista)
	
	IrInicioLista((*pPartida)->Jogadores);
	return PTD_CondRetOK;
}

int PTD_RespondeTruco(int pontuacaoDesejada, int equipe)
{
	int resposta;
	if(pontuacaoDesejada < 12)
	{
		// tem a opcao de pedir truco ^ 2
		printf("Digite 1 para aceitar o pedido truco, 2 para recusar o truco ou 3 para dobrar o pedido de truco\n");
		scanf("%d", &resposta);
	}
	else
	{
		printf("Digite 1 para aceitar o pedido de truco ou digite 2 para recusar o pedido de truco");
		scanf("%d", &resposta);
	}
	return resposta;
}


int CalculaVencedorRodada(int *cartas, int numJogadores)
{
	int i;
	int melhorCarta[2] = {0, 0}, posicaoMelhorCarta[2] = {0,0};
	for(i = 0; i < numJogadores; ++i)
	{
		if(cartas[i%2] > melhorCarta[i%2]) 
		{
			melhorCarta[i%2] = cartas[i%2];
			posicaoMelhorCarta[i%2] = i;
		}
	}
	if(melhorCarta[0] != melhorCarta[1]) return ( ( melhorCarta[0] > melhorCarta[1] ) ? 0 : 1);
	return ( (posicaoMelhorCarta[0] < posicaoMelhorCarta[1]) ? 0 : 1 );
}


// nao precisamos armazenas as cartas jogadas, somente os pesos delas para decidir quem ganhou determinada mao
PTD_tpCondRet PTD_PegaJogada(LIS_tppLista Jogadores, int* pesoCartas, int numJogadores)
{
	BAR_tppCarta pCarta;
	BAR_tppCarta pCartaDummy;
	PTD_tppJogador pJogador;	
	int i, peso, cartasDisponiveis = 0, escolha, j;
	printf("Esta na vez do jogador %s\nSuas opcoes de cartas serao exibidas abaixo\n", (PTD_tppJogador)LIS_ObterValor(Jogadores));
	printf("Vamos realizar uma jogada\n");
	IrInicioLista(Jogadores);
	for(i = 0; i < numJogadores; ++i)
	{
		pJogador = (PTD_tppJogador) LIS_ObterValor( Jogadores );
		printf("Vamos exibir as cartas do jogador %s\n" , pJogador->nome);
		cartasDisponiveis = 0;
		for(j = 0; j < 3; ++j) 
		{
			if( pJogador->mao[j] != NULL ) // quer dizer que o jogador ainda nao jogou essa carta da mao
			{
				cartasDisponiveis++;
				printf("Digite %d para jogar essa carta -> ", cartasDisponiveis);
				BAR_ImprimeCarta(pJogador->mao[j]);
			}
		}
		printf("Digite o numero da carta escolhida");
		scanf("%d",&escolha);
		while( escolha < 1 || escolha > cartasDisponiveis ) 
		{
			printf("Digite uma carta com valor permitido por favor\n");
			scanf("%d", &escolha);
		}
		cartasDisponiveis = 1;
		for(j = 0; j < 3; ++j)
		{
			if(pJogador->mao[j] != NULL)
			{
				if(cartasDisponiveis == escolha)
				{
					pesoCartas[i] = GetPeso(pJogador->mao[j]);
					pJogador->mao[j] = NULL;
					break;
				}
				else cartasDisponiveis++;
			}
		}
		if(LIS_AvancarElementoCorrente(Jogadores,1) != LIS_CondRetOK)
		{
			return PTD_CondRetListaVazia;
		}
	}
	return PTD_CondRetOK;
}
void PTD_ImprimeMaos(PTD_tppPartida* pPartida, int numJogadores)
{
	int i, j;
	PTD_tppJogador pJogador;
	for(j = 0; j < numJogadores; ++j)
	{
		pJogador = (PTD_tppJogador) LIS_ObterValor( (*pPartida)->Jogadores );
		printf("Cartas do jogador:\t%s\t\n",pJogador->nome);
		for(i=0;i<3;i++)
		{
			
			BAR_ImprimeCarta(pJogador->mao[i]);
		}
		puts("\n\n");
		LIS_AvancarElementoCorrente((*pPartida)->Jogadores,1);
	}
}

int PTD_InterfacePartida()
{
	PTD_tppPartida pPartida;
	int control = 1, pontosEquipePartida[2] = {0, 0}, pontosEquipeRodada[2] = {0, 0};
	int resposta, nrodada, nmao,numJogadores,i, *cartasJogadas, valorRodada = 1, winner, flagImprime;
	
	nmao, nrodada = 0;

	while(control)
	{
		printf("Iniciar partida?\t1-Sim\t2-Nao\n");
		scanf("%d",&resposta);

		// inicializando o placar das equipes
		pontosEquipePartida[0] = pontosEquipePartida[1] = 0;

		if(resposta==1)
		{
			
			printf("Iniciar partida para quantos jogadores?(Máximo de 10 jogadores)\n");
			scanf("%d",&numJogadores);
			//assert
			cartasJogadas = (int* ) malloc( sizeof(int) * numJogadores);
			PTD_CriaPartida(&pPartida, numJogadores);
			//assert
			//BAR_Embaralhar(pPartida->Baralho);
			//assert
			printf("Equipes e Jogadores criados, baralho devidamente embaralhado!\n");
			//BAR_ImprimeBaralho(pPartida->Baralho);

			//PTD_DistribuiCartas(&pPartida, numJogadores);
			
			//PTD_ImprimeMaos(&pPartida, numJogadores);
			control = 0;

			while( pontosEquipePartida[0] < 3 && pontosEquipePartida[1] < 3) 
			{
				/* Enquanto nenhuma equipe tem 12 pontos, vamos realizar uma nova rodada */
				pontosEquipeRodada[0] = pontosEquipeRodada[1] = 0;
				valorRodada = 1;
				BAR_CriarBaralho( &(pPartida->Baralho) );
				BAR_Embaralhar(pPartida->Baralho);
				

				printf("Digite 0 para continuar 1 para imprimir o baralho recem criado\n");
				scanf("%d", &flagImprime);

				if(flagImprime) BAR_ImprimeBaralho(pPartida->Baralho);
				
				PTD_DistribuiCartas(&pPartida, numJogadores);
								
				while(pontosEquipeRodada[0] < 2 && pontosEquipeRodada[1] < 2)
				{
					PTD_PegaJogada(pPartida->Jogadores, cartasJogadas, numJogadores);
					
					winner = CalculaVencedorRodada(cartasJogadas, numJogadores);

					pontosEquipeRodada[winner]++;

					printf("Vamos imprimir os pesos das cartas jogadas, respectivamente");
					for(i = 0; i < numJogadores; ++i) printf("%d ", cartasJogadas[i]);
					puts("");
				}
				if(pontosEquipeRodada[0] > pontosEquipeRodada[1]) pontosEquipePartida[0] += valorRodada;
				else pontosEquipePartida[1] += valorRodada;
				printf("Equipe1 %d : %d Equipe2\n", pontosEquipePartida[0], pontosEquipePartida[1]);
			}
			// Aqui ja temos alguma equipe com pelo menos 12 pontos, vamos imprimir o campeao
			if( pontosEquipePartida[0] == 12 ) printf("Equipe 0 ganhou \n");
			else printf("Equipe 1 ganhou \n");
		}
	}
	//BAR_ImprimeBaralho(pPartida->Baralho);
	return 0;
}


int main()
{
	//int retorno,resposta;
	//BAR_tppCarta *cartas=NULL;
	//BAR_tppBaralho Baralho;
	BAR_tppCarta carta = NULL;
	PTD_tppPartida novaPartida;

	
	if(BAR_CriaCarta(&carta,'a',10,"ouros")==BAR_CondRetOK)
	{
		printf("sucesso em criar uma carta!\n");
	}


	PTD_InterfacePartida();

		return 0;
}


		//retorno=DestruirCarta(*carta);
		/*
	retorno=BAR_CriaVetorCartas(&cartas);

	if(retorno==BAR_CondRetOK) printf("sucesso\n");

	retorno = BAR_CriarBaralho(&Baralho);
	if(retorno==BAR_CondRetOK) printf("sucesso\n");

	BAR_Embaralhar(Baralho);

	BAR_ImprimeBaralho(Baralho);
	*/


	// PTD_CriaPartida(&novaPartida, 6);

	// print_funcoes(novaPartida);
	/*
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
	*/
