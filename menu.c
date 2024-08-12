#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "classificacaoInterna.h"
#include "intercalacaoBasica.h"
#include <string.h>

#include "employee.h"
#include "pontos.h"
#include "pontos.h"

void wait_for_enter() {
    printf("Pressione Enter para continuar...\n");
    _getch();
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void add_employee_menu(FILE *file) {
    // Aloca um espaco na memoria para salvar os dados do input
    Employee *employee = malloc(sizeof(Employee));

    // Captura os dados do novo funcionario
    clear_screen();
    printf("====== ADICIONAR NOVO FUNCIONARIO ======\n");
    printf("Nome: ");
    scanf(" %[^\n]s", employee->name);
    printf("Funcao: ");
    scanf(" %[^\n]s", employee->role);
    printf("Salario: ");
    scanf(" %lf", &employee->salary);
    printf("Hora de entrada: ");
    scanf(" %lf", &employee->entry_time);
    printf("Hora de saida: ");
    scanf(" %lf", &employee->exit_time);
    printf("Inicio almoco: ");
    scanf(" %lf", &employee->lunch_start);
    printf("Fim almoco: ");
    scanf(" %lf", &employee->lunch_end);

    // Completa os dados gerados automaticamente
    employee-> id = get_employees_count(file) + 1;
    employee-> hire_date = time(NULL);
    employee-> resignation_date = 0;
    employee-> state = 0;

    // Confirma a criação do novo funcionario
    char confirmation;
    do {
        clear_screen();
        printf("Confirme os dados do novo funcionario:\n\n");
        print_employee(employee);
        printf("\nSalvar dados? [s/n]: ");
        scanf("%c", &confirmation);
    } while (confirmation != 's' && confirmation != 'n');

    // Salva os dados no arquivo ou cancela a opeação
    if(confirmation == 's') {
        clear_screen();
        add_employee(file, employee);
        printf("\nDados salvos com sucesso!");
        wait_for_enter();
    } else {
        clear_screen();
        printf("\nOperacao cancelada com sucesso!");
        wait_for_enter();
    }

    // Libera o espaço na memoria em que os dados estavam
    free(employee);
}

void add_random_employee_menu(FILE *file) {
    clear_screen();
    int count;
    printf("Informe a quantidade de funcionários: ");
    scanf("%d", &count);
    add_random_employees(file, count);
    wait_for_enter();
}


void admin_menu(FILE *file, FILE *file_pontos) {
    unsigned int selection = 0;
    int id;
    Employee *e;

    do {
        system("cls");
        printf("======= PAINEL ADMIN =======\n");
        printf("1. Adicionar funcionario.\n");
        printf("2. Ver a quantidade de funcionarios.\n");
        printf("3. Adicionar varios funcionarios aleatorios.\n");
        printf("4. Verificar se a base funcionarios esta ordenada.\n");
        printf("5. Ordenar por classificacao interna.\n");
        printf("6. Imprimir funcionario em uma posicao.\n");
        printf("7. Imprimir lista de funcionarios.\n");
        printf("8. Dias trabalhados de um funcionario.\n");
        printf("9. Demitir um funcionario\n");


        printf("\n0. Voltar\n");
        printf("\n>>> Opcao selecionada: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                add_employee_menu(file);
                break;
            case 2:
                clear_screen();
                printf("Quantidade de funcioarios: %d\n", get_employees_count(file));
                wait_for_enter();
                break;
            case 3:
                add_random_employee_menu(file);
                break;
            case 4:
                clear_screen();
                if(verify_sorted_employees(file)) {
                    printf(">> A base de funcionarios esta ordenada.\n\n");
                }
                else
                {
                    printf(">> A base de funcionarios NAO esta ordenada.\n\n");
                }
                wait_for_enter();
                break;
            case 5:
                clear_screen();
                sort_employees(file);
                wait_for_enter();
                break;
            case 6:
                clear_screen();
                Employee *employee;

                printf("> Digite o id do funcionario: ");
                scanf("%d", &id);
                employee = get_employee_by_id(file, id);

                print_employee(employee);
                wait_for_enter();
                free(employee);
                break;
            case 7:
                rewind(file);
                for(int i = 0; i < get_employees_count(file); i++) {
                    fseek(file, get_employee_size() * i, SEEK_SET);
                    e = read_employee(file);

                    print_employee(e);
                    printf("\n==============\n");
                }
                wait_for_enter();
                break;
            case 8:
                clear_screen();

                printf("> Digite o id do funcionario: ");
                scanf("%d", &id);
                if(id < 0 || id > get_employees_count(file)) break;
                e = get_employee_by_id(file, id);
                int count = get_days_worked(file_pontos, id);
                printf("%s trabalhou por %d dias\n", e->name, count);
                // free(e);
                wait_for_enter();

                break;
            case 9:
                clear_screen();

                printf("> Digite o id do funcionario: ");
                scanf("%d", &id);

                e = get_employee_by_id(file, id);
                if(e == NULL)
                {
                    printf("Voce deve informar um id valido.\n");
                    wait_for_enter();
                    break;
                }
                e->resignation_date = time(NULL);
                int index = get_employee_index(file, e->id);
                update_employee(file, e, index);

                clear_screen();
                printf("%s foi demitido com sucesso!", e->name);
                wait_for_enter();
            default:
                break;
        }
    } while(selection != 0);
}

void menu_ponto(FILE *file, FILE *file_pontos)
{
    unsigned int selection = 0;

    do {
        system("cls");
        printf("======= PONTO ELETRONICO =======\n");
        printf("1. Bater ponto.\n");
        printf("\n0. Sair\n");
        printf("\n>>> Opcao selecionada: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                clear_screen();
                Employee *e;
                int id;
                printf("> Informe o seu id: ");
                scanf("%d", &id);

                e = get_employee_by_id(file, id);

                if(e == NULL) {
                    clear_screen();
                    printf("Usuario nao encontrado.\n");
                    wait_for_enter();
                    break;
                }

                if(e->resignation_date != 0) {
                    clear_screen();
                    printf("Voce foi demitido, nao pode bater ponto.\n");
                    wait_for_enter();
                    break;
                }

                if(e-> state != 3) e->state++;
                else e->state = 0;


                clear_screen();
                print_employee(e);
                int index = get_employee_index(file, id);
                update_employee(file, e, index);
                baterPonto(file_pontos, e->id, e->state);

                wait_for_enter();

                free(e);
                break;
            default:
                break;
        }
    } while(selection != 0);
}

void menu(FILE *file, FILE *file_pontos) {
    unsigned int selection = 0;

    do {
        system("cls");
        printf("======= MENU INICIAL =======\n");
        printf("1. Sistema de ponto.\n");
        printf("2. Painel admin\n");
        printf("\n0. Sair\n");
        printf("\n>>> Opcao selecionada: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                menu_ponto(file, file_pontos);
                break;
            case 2:
                admin_menu(file, file_pontos);
                break;
            default:
                break;

        }
    } while(selection != 0);

    fclose(file);
}
