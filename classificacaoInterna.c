//
// Created by richa on 05/08/2024.
//
#include "employee.h"
#include "classificacaoInterna.h"
//#include "insertionSortMemoria.c"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


int classificacao_interna(FILE *file, int M){

    rewind(file); //posiciona cursor no inicio do arquivo

    int reg = 0;
    int nFunc = get_employees_count(file);
    int qtdParticoes = 0;
    int employee_size = get_employee_size();
    char *nomeParticao[20];

    while (reg < nFunc) {
        printf("%d != %d\n", reg, nFunc);
        //le o arquivo e coloca no vetor
        Employee *v[M];
        int i = 0;
        while (!feof(file)) {
            fseek(file, (reg) * employee_size, SEEK_SET);
            v[i] = read_employee(file);
            print_employee(v[i]);
            i++;
            reg++;
            if(i>=M) break;
        }



        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M) {
            M = i;
        }

        //faz ordenacao
        for (int j = 1; j < M; j++) {
            Employee *f = v[j];
            i = j - 1;
            while ((i >= 0) && (v[i]->id > f->id)) {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = f;
        }



        //cria arquivo de particao e faz gravacao
        sprintf(nomeParticao, "partition%i.dat", qtdParticoes);
        //nome = fopen(nomeParticao, "wb");

        //printf("\n%s\n", nome);


        FILE *p;

        if ((p = fopen(nomeParticao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {

            for (int j = 0; j < M; j++) {
                fseek(p, (j) * employee_size, SEEK_SET);
                //imprime(v[i]);

                save_employee(p, v[j]);
            }

            //imprimirBase(p);
            fclose(p);
            qtdParticoes++;
        }
        for(int jj = 0; jj<M; jj++)
            free(v[jj]);
    }

    return qtdParticoes;

}