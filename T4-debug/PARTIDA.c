/***************************************************************************
*  $MCI Módulo de implementação: PTD PARTIDA
*
*  Arquivo gerado:              PARTIDA.c
*  Letras identificadoras:      PTD
*
*  Projeto: INF 1301 / Truco
*  Gestor:  DI/PUC-Rio
*  Autores: Arthur Cavalcante Gomes Coelho(acgc)
* 	        Francisco Geiman Thiese       (fgt)
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       acgc   30/04/2018 início desenvolvimento
*  	  2       fgt    25/05/2018 implementacao da logica de partida
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
*  $TC Tipo de dados: PTD Jogador
*
*
***********************************************************************/

typedef struct PTD_tagJogador{
	char nome[NOMEMAXIMO];
	BAR_tppCarta mao[3];
	int idEquipe;

} PTD_tpJogador;

/***********************************************************************
*
*  $TC Tipo de dados: PTD Partida
*
*
***********************************************************************/

typedef struct PTD_tagPartida {
	LIS_tppLista Jogadores;
	int placar[2];
	BAR_tppBaralho Baralho;
	BAR_tppCarta manilhas[4];
} PTD_tpPartida;


/***** Protótipos das funções encapuladas no módulo *****/
PTD_tpCondRet DestruirJogador(PTD_tppJogador pJogador);

/***********************************************************************
*
*  $FC Função: PTD  -Destruir jogador
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo ponteiro passado
*
***********************************************************************/
PTD_tpCondRet DestruirJogador(PTD_tppJogador pJogador)
{
	free(pJogador);
	return PTD_CondRetOK;
}

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PTD  &Imprime jogadores
*  ****/
void PTD_ImprimeJogadores(LIS_tppLista *pJogadores) // encapsular ou jogar fora
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
		jogador = (PTD_tppJogador) ( LIS_ObterValor(*pJogadores));
	}
}/* Fim função: PTD  &Imprime Jogadores */

/***************************************************************************
*
*  Função: PTD  &Cria jogador
*  ****/
PTD_tpCondRet PTD_CriaJogador(PTD_tppJogador *pJogador, char nome[30])
{
	*pJogador = (PTD_tppJogador)malloc(sizeof(PTD_tpJogador));
	if( (*pJogador) == NULL ) return PTD_CondRetJogadorNaoExiste;
	strcpy((*pJogador)->nome, nome);
	return PTD_CondRetOK;
}/* Fim função: PTD  &Imprime Jogadores */

/***************************************************************************
*
*  Função: PTD  &Cria lista jogadores
*  ****/
PTD_tpCondRet PTD_CriaListaJogadores(int n_jogadores,LIS_tppLista *pJogadores, char nomes[10][1][NOMEMAXIMO])
{
	int i;
	LIS_tpCondRet CondRetLista;
	PTD_tpCondRet CondRetJogador;
	PTD_tppJogador pJogador;
	*pJogadores = LIS_CriarLista((void (*) (void *pDado))DestruirJogador);
	if(pJogadores == NULL)
	{
		return PTD_CondRetFaltouMemoria;
	}
	for(i=0;i<n_jogadores;i++)
	{
		CondRetJogador = PTD_CriaJogador(&pJogador,nomes[i][1]);
		if(CondRetJogador != PTD_CondRetOK)
		{
			return CondRetJogador;
		}
		CondRetLista = LIS_InserirElementoApos(*pJogadores,pJogador);
		if(CondRetLista != LIS_CondRetOK)
		{
			return PTD_CondRetListaVazia;
		}
	}
	IrInicioLista(*pJogadores);
	return PTD_CondRetOK;
}/* Fim função: PTD  &Imprime Jogadores */


/***************************************************************************
*
*  Função: PTD  &Monta equipes
*  ****/
PTD_tpCondRet PTD_MontaEquipes(LIS_tppLista *pJogadores, int jogadoresPorEquipe)
{
	// vou colocar uma assertiva so pra lembrarmos disso
	// assert(jogadoresPorEquipe == 1 || jogadoresPorEquipe == 2 || jogadoresPorEquipe == 3)
	int i;
	PTD_tppJogador jogador;
	if(pJogadores == NULL)  PTD_CondRetListaVazia; //se lista == NULL
	IrInicioLista(*pJogadores);
	for(i = 0; i < 2 * jogadoresPorEquipe; ++i)
	{
		jogador=(PTD_tppJogador) LIS_ObterValor(*pJogadores);				
		jogador->idEquipe = i % 2;
		LIS_AvancarElementoCorrente(*pJogadores,1);
	}
	return PTD_CondRetOK;
}/* Fim função: PTD  &Imprime Jogadores */

/***************************************************************************
*
*  Função: PTD  &Cria partida
*  ****/
PTD_tpCondRet PTD_CriaPartida(PTD_tppPartida *pPartida, int n_jogadores)
{
	int i;
	PTD_tpCondRet ret;
	char nomes[10][1][NOMEMAXIMO]; // char string_matrix[ROWS][COLUMNS][STRING_LENGTH]
	*pPartida = (PTD_tppPartida) malloc(sizeof(PTD_tpPartida));


	(*pPartida)->placar[0] = (*pPartida)->placar[1] = 0;

	for( i = 0; i < n_jogadores; ++i)
	{
		printf("Digite o nome do %d-esimo jogador\n", i);
		scanf("%s", nomes[i][1]);
	}

	//Cria Lista de Jogadores
	ret = PTD_CriaListaJogadores(n_jogadores,&(*pPartida)->Jogadores, nomes);
	if(ret != PTD_CondRetOK)
	{
		return ret;
	}
	//Aponta cada jogador a uma equipe
	ret = PTD_MontaEquipes(&(*pPartida)->Jogadores,3);
	if(ret != PTD_CondRetOK)
	{
		return ret;
	}
	return PTD_CondRetOK;
}/* Fim função: PTD  &Cria Partida */


/***************************************************************************
*
*  Função: PTD  &Distribui cartas
*  ****/
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
	IrInicioLista((*pPartida)->Jogadores);
	return PTD_CondRetOK;
}/* Fim função: PTD  &Distribui Cartas */

/***************************************************************************
*
*  Função: PTD  &Responde truco
*  ****/
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
}/* Fim função: PTD  &Responde truco */

/***************************************************************************
*
*  Função: PTD  &Calcula vencedor rodada
*  ****/
int PTD_CalculaVencedorRodada(int *cartas, int numJogadores)
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
}/* Fim função: PTD  &Calcula vencedor rodada */


/***************************************************************************
*
*  Função: PTD  &Pega jogada
*  ****/
PTD_tpCondRet PTD_PegaJogada(LIS_tppLista Jogadores, int* pesoCartas, int numJogadores, int* valorPartida, int* equipeDesistente, int* pediramTrucoNaRodada)
{
	BAR_tppCarta pCarta;
	BAR_tppCarta pCartaDummy;
	PTD_tppJogador pJogador;	
	int k,i, peso, cartasDisponiveis = 0, escolha, j, flagPediuTruco, equipeAtual, pedidosTruco[5] = {1,3,6,9,12}, indiceAtual = 0;
	IrInicioLista(Jogadores);
	for(i = 0; i < numJogadores; ++i)
	{
		pJogador = (PTD_tppJogador) LIS_ObterValor( Jogadores );
		if (pJogador == NULL)
		{
			return PTD_CondRetListaVazia;
		}
		if(i != 0)
			printf("Peso da ultima carta jogada pela equipe adversária: %d\n",pesoCartas[(sizeof(pesoCartas)/4) - (i)]); // vetor de int, bytes =4, sizeof pega o numero total de ints salvos, divindo por 4 temos o indice do final
		printf("A rodada atualmente esta valendo %d pontos.\n", *valorPartida);
		printf("Vamos exibir as cartas do jogador %s\n" , pJogador->nome);
		cartasDisponiveis = 0;
		for(j = 0; j < 3; ++j) 
		{
			if( pJogador->mao[j] != NULL ) // quer dizer que o jogador ainda nao jogou essa carta da mao
			{
				cartasDisponiveis++;
				printf("%d carta -> ", cartasDisponiveis);
				BAR_ImprimeCarta(pJogador->mao[j]);
			}
		}
		if( indiceAtual < 4 && (*pediramTrucoNaRodada) == 0)
		{
			printf("Pedir truco?\n1-Sim\n2-Nao\n");
			scanf("%d",&escolha);
			while(escolha != 1 && escolha != 2) 
			{
				printf("Por favor, digite um valor valido\n");
				scanf("%d", &escolha);
			}
			if(escolha == 1) // Pedido de truco da equipe i%2 
			{
				*(pediramTrucoNaRodada) = 1;
				indiceAtual = 1;
				equipeAtual = i % 2;
				while(indiceAtual < 5)
				{
					equipeAtual ^= 1;
					// Nao tem mais como pedir truco novamente
					if(indiceAtual == 4) 
					{
						printf("A equipe %d deseja:\n1 - Aceitar o truco\n2 - Recusar o truco\n", equipeAtual);
						scanf("%d", &escolha);
						while(escolha != 1 && escolha != 2) 
						{
							printf("Por favor, digite uma escolha valida\n");
							scanf("%d", &escolha);
						}
						if(escolha == 1)
						{
							*(valorPartida) = 12;
							break; // fim da sequencia de pedidos de truco
						}
						else
						{
							*(valorPartida) = 9;
							*(equipeDesistente) = equipeAtual; // equipe recusou
							return PTD_CondRetOK;
						}
					}
				
					else
					{
						printf("A equipe %d deseja:\n1 - Aceitar o truco\n2 - Recusar o truco\n3 - Aumentar o truco\n", equipeAtual);
						scanf("%d", &escolha);
						while(escolha != 1 && escolha != 2 && escolha != 3)
						{
							printf("Por favor, digite uma escolha valida\n");
							scanf("%d", &escolha);
						}
						if(escolha == 1)
						{
							*(valorPartida) = pedidosTruco[indiceAtual];
							break; 
						}
						else if(escolha == 2)
						{
							*(valorPartida) = pedidosTruco[indiceAtual - 1];
							*(equipeDesistente) = equipeAtual;
							return PTD_CondRetOK;
						}
						else indiceAtual++;
					}
				}
			}
		}
		printf("Jogador %s, Digite o numero da carta escolhida: ",pJogador->nome);
		scanf("%d",&escolha);
		while( escolha < 1 || escolha > cartasDisponiveis ) 
		{
			printf("Digite uma carta com valor permitido por favor: ");
			scanf("%d", &escolha);
		}
		for(k=0;k<100;k++) printf("\n");
		cartasDisponiveis = 1;
		for(j = 0; j < 3; ++j)
		{
			if(pJogador->mao[j] != NULL)
			{
				if(cartasDisponiveis == escolha)
				{
					pesoCartas[i] = BAR_GetPeso(pJogador->mao[j]);
					pJogador->mao[j] = NULL;
					break;
				}
				else cartasDisponiveis++;
			}
		}
		LIS_AvancarElementoCorrente(Jogadores,1);
	}
	return PTD_CondRetOK;
}/* Fim função: PTD  &Pega jogada */

/***************************************************************************
*
*  Função: PTD  &Imprime Maos
*  ****/
void PTD_ImprimeMaos(PTD_tppPartida* pPartida, int numJogadores)
{
	int i, j;
	char msg;
	PTD_tppJogador pJogador;
	for(j = 0; j < numJogadores; ++j)
	{
		pJogador = (PTD_tppJogador) LIS_ObterValor( (*pPartida)->Jogadores );
		printf("Cartas do jogador: %s\n",pJogador->nome);
		for(i=0;i<3;i++)
		{
			BAR_ImprimeCarta(pJogador->mao[i]);
		}
		if(j == numJogadores - 1) 
		{
			printf("Digite 0 para continuar a partida\n");
			scanf(" %c", &msg);
			break;
		}
		printf("Digite 0 para ver a mao do jogador seguinte:\n");
		scanf(" %c",&msg);
		for(i=0;i<100;i++) printf("\n");
		LIS_AvancarElementoCorrente((*pPartida)->Jogadores,1);
	}
	for(i=0;i<100;i++) printf("\n");
}/* Fim função: PTD  &Pega jogada */

PTD_tpCondRet PTD_InterfacePartida()
{
	PTD_tppPartida pPartida;
	int control = 1, pontosEquipePartida[2] = {0, 0}, pontosEquipeRodada[2] = {0, 0};
	int resposta, nrodada, nmao,numJogadores,i, *cartasJogadas, valorRodada = 1, winner, flagImprime, desistente = -1, pediramTrucoNessaRodada;
	
	nmao, nrodada = 0;

	while(control)
	{
		PTD_tpCondRet retorno;
		printf("Iniciar partida?\t1-Sim\t2-Nao\n");
		scanf("%d",&resposta);

		// inicializando o placar das equipes
		pontosEquipePartida[0] = pontosEquipePartida[1] = 0;

		if(resposta==1)
		{
			printf("Iniciar partida para quantos jogadores?(Maximo de 6 jogadores)\n");
			scanf("%d",&numJogadores);
			while(numJogadores > 6 || (numJogadores % 2) != 0 || numJogadores < 2)
			{
				printf("Por favor digite um numero valido de jogadores\n");
				scanf("%d",&numJogadores);
			}
			cartasJogadas = (int* ) malloc( sizeof(int) * numJogadores);
			if(cartasJogadas == NULL)
			{
				return PTD_CondRetFaltouMemoria;
			}
			retorno = PTD_CriaPartida(&pPartida, numJogadores);
			if(retorno != PTD_CondRetOK)
			{
				return retorno;
			}
			printf("Equipes e Jogadores criados, baralho devidamente embaralhado!\n");

			control = 0;

			while( pontosEquipePartida[0] < 12 && pontosEquipePartida[1] < 12) 
			{
				/* Enquanto nenhuma equipe tem 12 pontos, vamos realizar uma nova rodada */
				pontosEquipeRodada[0] = pontosEquipeRodada[1] = 0;
				valorRodada = 1;
				BAR_CriarBaralho( &(pPartida->Baralho) );
				BAR_Embaralhar(pPartida->Baralho);
				printf("Digite 0 para continuar 1 para imprimir o baralho recem criado\n");
				scanf("%d", &flagImprime);

				if(flagImprime) BAR_ImprimeBaralho(pPartida->Baralho);
				
				retorno = PTD_DistribuiCartas(&pPartida, numJogadores);
				if(retorno != PTD_CondRetOK)
				{
					return retorno;
				}
				PTD_ImprimeMaos(&pPartida,numJogadores);

				desistente = -1; 
				valorRodada = 1; 
				pediramTrucoNessaRodada = 0;

				while(pontosEquipeRodada[0] < 2 && pontosEquipeRodada[1] < 2)
				{
					retorno = PTD_PegaJogada(pPartida->Jogadores, cartasJogadas, numJogadores, &valorRodada, &desistente, &pediramTrucoNessaRodada);
					if(retorno != PTD_CondRetOK)
					{
						return retorno;
					}
					if(desistente != -1)
					{
						winner = desistente ^ 1;
						pontosEquipeRodada[winner] += 2;
						break;
					}
					else
					{
						winner = PTD_CalculaVencedorRodada(cartasJogadas, numJogadores);
						pontosEquipeRodada[winner] += 1;
					}
					printf("A equipe ganhadora dessa jogada foi a equipe %d\n\n" , winner);
				}
				if(pontosEquipeRodada[0] > pontosEquipeRodada[1]) pontosEquipePartida[0] += valorRodada;
				else pontosEquipePartida[1] += valorRodada;
				printf("Essa rodada valeu um total de %d pontos\n", valorRodada);
				printf("A equipe ganhadora dessa rodada foi a equipe %d\n\n" , winner);
				printf("Equipe0 %d : %d Equipe1\n", pontosEquipePartida[0], pontosEquipePartida[1]);
			}
			// Aqui ja temos alguma equipe com pelo menos 12 pontos, vamos imprimir o campeao
			if( pontosEquipePartida[0] >= 12 ) printf("Equipe 0 ganhou \n");
			else printf("Equipe 1 ganhou \n");
		}
	}
	return PTD_CondRetOK;
}/* Fim função: PTD  &Imprime maos */


int main()
{
	PTD_InterfacePartida();
	return 0;
}
