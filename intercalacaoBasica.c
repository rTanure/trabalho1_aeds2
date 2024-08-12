#include "employee.h"
#include "intercalacaoBasica.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void intercalacao_basica(FILE *out, int num_p) {
    typedef struct vetor {
        Employee *fun;
        FILE *f;
    } TVet;

    TVet v[num_p];
    char nome[20];
    int fim = 0; // Controle do fim do procedimento

    // Inicializa as partições
    for (int i = 0; i < num_p; i++) {
        sprintf(nome, "partition%i.dat", i);
        v[i].f = fopen(nome, "rb");

        if (v[i].f != NULL) {
            v[i].fun = read_employee(v[i].f);
            if (v[i].fun == NULL) {
                v[i].fun = employee(INT_MAX, "", "", 0, 0, 0, 0, 0, 0, 0, 0);
            }
        } else {
            fim = 1;
        }
    }

    while (!fim) {
        int menor = INT_MAX;
        int pos_menor = -1;

        for (int i = 0; i < num_p; i++) {
            if (v[i].fun != NULL && v[i].fun->id < menor) {
                menor = v[i].fun->id;
                pos_menor = i;
            }
        }

        if (pos_menor == -1) {
            fim = 1; // Acabou o processamento
        } else {
            save_employee(out, v[pos_menor].fun);

            free(v[pos_menor].fun); // Libera o funcionário atual
            v[pos_menor].fun = read_employee(v[pos_menor].f);

            if (v[pos_menor].fun == NULL) {
                v[pos_menor].fun = employee(INT_MAX, "", "", 0, 0, 0, 0, 0, 0, 0, 0);
            }
        }
    }

    // Fecha os arquivos de partição
    for (int i = 0; i < num_p; i++) {
        fclose(v[i].f);
        free(v[i].fun);
    }
}
