//
// Created by richa on 11/08/2024.
//

#ifndef PONTOS_H
#define PONTOS_H

#include <stdio.h>
#include <time.h>


typedef struct Ponto
{
    int id;
    int id_func;
    time_t date;
    int type;
} Ponto;

void baterPonto(FILE *file, int id_func, char type);

int get_days_worked(FILE *file, int id_func);

#endif //PONTOS_H
