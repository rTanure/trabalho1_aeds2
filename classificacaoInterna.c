#include "employee.h"
#include "classificacaoInterna.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int classificacao_interna(FILE *arq, int M) {
    rewind(arq); // Posiciona o cursor no início do arquivo

    int reg = 0;
    int nFunc = get_employees_count(arq);
    int qtdParticoes = 0;
    int t = get_employee_size();
    char nomeParticao[20];

    while (reg < nFunc) {
        Employee *v[M];
        int i = 0;

        // Lê até M registros ou até o fim do arquivo
        while (i < M && reg < nFunc) {
            fseek(arq, reg * t, SEEK_SET);
            v[i] = read_employee(arq);
            i++;
            reg++;
        }

        // Ordenação por inserção
        for (int j = 1; j < i; j++) {
            Employee *f = v[j];
            int k = j - 1;
            while (k >= 0 && v[k]->id > f->id) {
                v[k + 1] = v[k];
                k--;
            }
            v[k + 1] = f;
        }

        sprintf(nomeParticao, "partition%i.dat", qtdParticoes);
        FILE *p = fopen(nomeParticao, "wb+");

        if (p != NULL) {
            for (int j = 0; j < i; j++) {
                fseek(p, j * t, SEEK_SET);
                save_employee(p, v[j]);
                free(v[j]); // Libera memória
            }
            fclose(p);
            qtdParticoes++;
        } else {
            printf("Erro ao criar arquivo de saída\n");
            break;
        }
    }

    return qtdParticoes;
}
