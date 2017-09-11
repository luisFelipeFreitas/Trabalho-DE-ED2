#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include "geracao_particoes.h"
#include "nomes.h"
#include "cliente.h"
#include <stdlib.h>
#include <limits.h>


void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
	//TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}

int selecionaMenor(Cliente *clientes[], int marcado[], int M) {
    int i = 0;
    if (M <= 0)
        return -1;
    Cliente *c = NULL;
    int resp = -1;

    for (i = 0; i < M; i++) {
        if (marcado[i] != 0 || clientes[i] == NULL) {

        } else if (c == NULL) {
            c = clientes[i];
            resp = i;
        } else {
            if (c->cod_cliente > clientes[i]->cod_cliente) {
                c = clientes[i];
                resp = i;
            }
        }
    }

    return resp;
}

void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
    Cliente * clientes[M];
    Cliente *clienteDaVez, *clienteLido;
    Cliente *clienteMax = cliente(INT_MAX, "");
    Nomes *particaoDaVez = nome_arquivos_saida;
    int marcado[M];
    int i = 0, controle = 1, atual = -1;
    FILE *in = fopen(nome_arquivo_entrada, "rb");
    FILE *out = fopen(particaoDaVez->nome, "wb");

    for (i = 0; i < M; i++) {
        clientes[i] = le_cliente(in);
        marcado[i] = 0;
    }
    clienteLido = clientes[0];

    while (controle != 0) {
        atual = selecionaMenor(clientes, marcado, M);
        if (atual >= 0) {
            clienteDaVez = clientes[atual];
            clienteLido = le_cliente(in);
            if (clienteDaVez->cod_cliente != INT_MAX) {
                salva_cliente(clienteDaVez, out);
            } else {
                salva_cliente(clienteMax, out);
                controle = 0;
                fclose(out);
            }
            if (clienteLido != NULL) {
                if (clienteLido->cod_cliente < clienteDaVez->cod_cliente) {
                    marcado[atual] = 1;
                }
            }
            clientes[atual] = clienteLido;
        } else {
            salva_cliente(clienteMax, out);
            fclose(out);
            for (i = 0; i < M; i++) {
                if (marcado[i] == 1) {
                    marcado[i] = 0;
                }
            }
            particaoDaVez = particaoDaVez->prox;
            if (particaoDaVez != NULL) {
                out = fopen(particaoDaVez->nome, "wb");
            } else {
                fclose(out);
                controle = 0;
            }
        }
    }
    fclose(in);
}




void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n)
{
	//TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}

