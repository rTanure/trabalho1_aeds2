#include <stdio.h>
#include <time.h>
#include "pontos.h"

#include <stdlib.h>

Ponto *ponto(int id, int id_func, time_t date, int type)
{
    Ponto *ponto = malloc(sizeof(Ponto));
    ponto->date = date;
    ponto->id = id;
    ponto->id_func = id_func;
    ponto->type = type;
    return ponto;
}

void save_ponto(FILE *file, Ponto *ponto) {
    fwrite(&ponto->id, sizeof(int), 1, file);
    fwrite(&ponto->id_func, sizeof(int), 1, file);
    fwrite(&ponto->date, sizeof(time_t), 1, file);
    fwrite(&ponto->type, sizeof(int), 1, file);
};

size_t get_pontos_size() {
    size_t totalSize = 0;

    totalSize += sizeof(((Ponto *)0)->id);
    totalSize += sizeof(((Ponto *)0)->id_func);
    totalSize += sizeof(((Ponto *)0)->type);
    totalSize += sizeof(((Ponto *)0)->date);

    return totalSize;
}

int get_pontos_count(FILE *file) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int num_employees = file_size / get_pontos_size();
    return num_employees;
}

void baterPonto(FILE *file, int id_func, char type)
{
    Ponto *novo_ponto = ponto(get_pontos_count(file) + 1, id_func, time(NULL), type);
    fseek(file, 0, SEEK_END);
    save_ponto(file, novo_ponto);
    free(novo_ponto);
}

Ponto *read_ponto(FILE *file) {
    Ponto *ponto = malloc(sizeof(Ponto));

    fread(&ponto->id, sizeof(int), 1, file);
    fread(&ponto->id_func, sizeof(int), 1, file);
    fread(&ponto->date, sizeof(time_t), 1, file);
    fread(&ponto->type, sizeof(int), 1, file);

    return ponto;
};

int get_days_worked(FILE *file, int id_func)
{
    Ponto *ponto;

    int count = 0;
    for(int i = 0; i < get_pontos_count(file); i++)
    {
        fseek(file, get_pontos_size() * i, SEEK_SET);
        ponto = read_ponto(file);
        if(ponto->id_func == id_func && ponto -> type == 0) count++;
    }
    free(ponto);
    return count;
}