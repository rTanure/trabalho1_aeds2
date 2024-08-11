#include "employee.h"
#include "intercalacaoBasica.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void intercalacao_basica(FILE *file, int num_p){

    // Define a struct que contem o maior objeto e o
    typedef struct vetor{
        Employee *employee;
        FILE *f;
    }TVet;

    int fim = 0; //variavel que controla fim do procedimento
    int particao = 0;
    char *nome[20];


    //cria vetor de particoes
    TVet v[num_p];

    //abre arquivos das particoes, colocando variavel de arquivo no campo f do vetor
    //e primeiro funcionario do arquivo no campo func do vetor
    for (int i=0; i < num_p; i++) {
        // O que essa função faz?
        sprintf(nome, "partition%i.dat", particao);

        v[i].f = fopen(nome, "rb");

        if (v[i].f != NULL) {
            //fseek(v[i].f, v[i].aux_p * tamanho(), SEEK_SET);
            Employee *f = read_employee(v[i].f);
            if (f == NULL) {
                //arquivo estava vazio
                //coloca HIGH VALUE nessa posi??o do vetor
                v[i].employee = employee(INT_MAX, "", "", 0, 0, 0, 0, 0, 0, 0, 'a');
            }
            else {
                //conseguiu ler funcionario, coloca na posi??o atual do vetor
                v[i].employee = f;
            }
        }
        else {
            fim = 1;
        }

        particao++;
    }



    //int aux = 0;

    while (!(fim)) { //conseguiu abrir todos os arquivos

        // Menor valor encontrado no topo
        int menor = INT_MAX;
        // Index da partição que possui o menor valor
        int pos_menor;

        // Itera sobre as partições e encontra a com o menor valor no topo
        for(int i = 0; i < num_p; i++){
            if(v[i].employee->id < menor){
                menor = v[i].employee->id;
                pos_menor = i;
            }
        }
        // Verifica se não possui mais menores valores
        if (menor == INT_MAX) fim = 1;
        else {

            // Salva o menor funcionario no arquivo principal
            save_employee(file, v[pos_menor].employee);
            // Recupera o funcionairo da menor partição
            fseek(v[pos_menor].f, ftell(v[pos_menor].f) + get_employee_size(), SEEK_SET);

            Employee *f = read_employee(v[pos_menor].f);

            if (f == NULL) {
                printf("null\n");
                //arquivo estava vazio
                //coloca HIGH VALUE nessa posiçao do vetor
                v[pos_menor].employee = employee(INT_MAX, "", "", 0, 0, 0, 0, 0, 0, 0, 'a');
            }
            else {
                print_employee(v[pos_menor].f);
                printf(f);
                v[pos_menor].employee = f;
            }
            for (int f = 0; f < 100; f++) printf("passou\n");

        }
    }

    //fecha arquivos das partiÇões de entrada
    for(int i = 0; i < num_p; i++){
        printf("for 2");
        fclose(v[i].f);
    //    free(v[i].func);
    }
    //fecha arquivo de saída
    //fclose(out);
}


