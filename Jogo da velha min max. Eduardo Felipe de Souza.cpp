#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define N 10
/*Autor: Eduardo Felipe de Souza
  Jogo da velha utilizando a soma dos campos de tabela cujo resultado sempre vai ser 15
  Neste algoritmo tentei criar algo parecido com um algoritmo minimax para 
  	prever as jogadas do player quando se joga contra a maquina e tentar bloquear sua vitória
  Ambiente utilizado: Visual studio code com extencoes C/C++ e C/C++ Compile Run
*/

void exibirJogo(char[]);
void verificaganhador (char[], int[]);
int inteligenciaartificial(char[]);

int main( void )
{
	char jogo[N], venc = '-';
	int i, pos, plvsia, qtdfieldfree;
	int vp[2] = {0,0};/*Posição 0 indica vencedor (0 para ninguem, 1 para X e 2 para O). 
						E posição 1 indica a posição da jogada que o tornou vencedor*/
	
	jogo[0] = 'X';
	for ( i = 1; i < N; i++ )
	{
		jogo[i] = '-';
	}

	printf("Digite 1 para jogar contra um adversario humano\nOu digite 2 para o computador ser seu adversario:   ");
	scanf("%d",&plvsia);
	system("cls");
	printf( "\n" );
	do {
		printf("\nJOGADOR DA VEZ: %c", jogo[0]);
		printf("\nJOGO: ");
		for ( i = 1; i < N; i++ ) 
		{
			printf("%c", jogo[i]);
		}
		printf("\n");

		exibirJogo( jogo);
		if (jogo[0] == 'O')
		{
			switch (plvsia)
			{
				case 1:
					printf("\nESCOLHA SUA POSICAO: ");
					scanf("%d", &pos);
					printf( "\n" );
					break;
				case 2:
					pos = inteligenciaartificial(jogo);
					break;
			}
		}
		else
		{
			printf("\nESCOLHA SUA POSICAO: ");
			scanf("%d", &pos);
			printf( "\n" );
		}
		jogo[pos] = jogo[0];
		jogo[0] = ( jogo[0] == 'X' ? 'O' : 'X');

		verificaganhador(jogo, vp);//Função para verficação de ganhadores
		if (vp[0] != 0)//Checagem da resposta enviada por "verificaganhador"
			break;
		qtdfieldfree = 9;
		for (int i = 1; i < N; i ++)
			qtdfieldfree = (jogo[i] != '-' ? qtdfieldfree - 1 : qtdfieldfree);

		printf("\nAguarde.....");
		Sleep(2000);
		system("cls");
	}while (qtdfieldfree > 0);
	
	system("cls");
	exibirJogo(jogo);
	if (vp[0] != 0 )
	{
		venc = vp[0] == 1 ? 'X' : 'O';
		printf("\n\nPARABENS O JOGADOR '%c' VENCEU O JOGO", venc);
	}
	else
	{
		printf("\n\nPARECE QUE DEU VELHA");
	}

	return 0;
}

void verificaganhador (char jogo[], int pvspos[])
{
	char vencedor;
	int somapx = 0, somapo = 0;
	int jogora[N] = {0, 2, 9, 4, 7, 5, 3, 6, 1, 8};//Vetor com os valores indicador pelo final do R.A para verificar ganhador
	for (int i = 0; i < 9; i = i + 3)//A seguir verificação de ganhadores nas linhas
	{
		for (int j = 1; j <= 3; j++)
		{
			somapx = (jogo[j+i] == 'X' ? somapx + jogora[j+i] : somapx);
			somapo = (jogo[j+i] == 'O' ? somapo + jogora[j+i] : somapo);
			if (somapx == 15)
			{
				pvspos[0] = 1;
				pvspos[1] = j+i;
				break;
			}
			else if (somapo == 15)
			{
				pvspos[0] = 2;
				pvspos[1] = j+i;
				break;
			}
		}
		somapo = 0;
		somapx = 0;
	}
	for (int i = 1; i <= 3; i++)//A seguir verificação de ganhadores nas colunas
	{
		for (int j = 0; j < 9; j = j + 3)
		{
			somapx = (jogo[j+i] == 'X' ? somapx + jogora[j+i] : somapx);
			somapo = (jogo[j+i] == 'O' ? somapo + jogora[j+i] : somapo);
			if (somapx == 15)
			{
				pvspos[0] = 1;
				pvspos[1] = j+i;
				break;
			}
			else if (somapo == 15)
			{
				pvspos[0] = 2;
				pvspos[1] = j+i;
				break;
			}
		}
		somapo = 0;
		somapx = 0;
	}
	for (int i = 1; i <= 9; i = i + 4)//A seguir laço para verificação de vencedores no eixo diagonal esquerda->direita(\)
	{
		somapx = (jogo[i] == 'X' ? somapx + jogora[i] : somapx);
		somapo = (jogo[i] == 'O' ? somapo + jogora[i] : somapo);
		if (somapx == 15)
		{
			pvspos[0] = 1;
			pvspos[1] = i;
			break;
		}
		else if (somapo == 15)
		{
			pvspos[0] = 2;
			pvspos[1] = i;
			break;
		}
	}
	somapo = 0;
	somapx = 0;
	for (int i = 3; i <= 9; i = i + 2)//A seguir laço para verificação de vencedores no eixo diagonal direita->esquerda(/)
	{
		somapx = (jogo[i] == 'X' ? somapx + jogora[i] : somapx);
		somapo = (jogo[i] == 'O' ? somapo + jogora[i] : somapo);
		if (somapx == 15)
		{
			pvspos[0] = 1;
			pvspos[1] = i;
			break;
		}
		else if (somapo == 15)
		{
			pvspos[0] = 2;
			pvspos[1] = i;
			break;
		}
	}
}

int inteligenciaartificial(char jogo[])
{
	int naoprecisa;
	for(int i = 1; i < N; i++)
	{
		int vaiganhar[2] = {0,0};
		if(jogo[i] == '-')
		{
			jogo[i] = 'X';
			verificaganhador(jogo, vaiganhar);
			jogo[i] = '-';
			if (vaiganhar[0] == 1)
			{
				return i;
			}
		}
	}
	do
	{
		naoprecisa = ((rand()%8) + 1);
	} while (jogo[naoprecisa] != '-');
	return naoprecisa;
}

void exibirJogo(char jogo[])
{
	char v[N];
	int i;

	for ( i = 1; i < N; i++ )
	{
		v[i] = jogo[i] == 'X' || jogo[i] =='O' ? jogo[i] : i + 48;
	}

	printf( "     |     |     \n" );
	printf( "  %c  |  %c  |  %c  \n", v[1], v[2], v[3] );
	printf( "     |     |     \n" );
	printf( "-----|-----|-----\n" );
	printf( "     |     |     \n" );
	printf( "  %c  |  %c  |  %c  \n", v[4], v[5], v[6] );
	printf( "     |     |     \n" );
	printf( "-----|-----|-----\n" );
	printf( "     |     |     \n" );
	printf( "  %c  |  %c  |  %c  \n", v[7], v[8], v[9] );
	printf( "     |     |     \n\n" );
}