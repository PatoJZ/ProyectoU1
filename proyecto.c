#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Guardian
{
    int id;
    char name[50];
    char type[50];
    int health;
    int AttackPoints;
    int DefPoints;
    struct Guardian *next;
} Guardian;

void SelectGuardian(Guardian **listaGuardianes, Guardian **listaGuardianJugador)
{
    int IdGuerrero;
    printf("Seleccione un personaje para Jugar: ");
    scanf("%d", &IdGuerrero);

    Guardian *current = *listaGuardianes;
    Guardian *prev = NULL;
    while (current != NULL)
    {
        if (current->id == IdGuerrero)
        { // Encontró el personaje
            if (prev == NULL)
            { // Es el primer elemento de la lista original
                *listaGuardianes = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            current->next = *listaGuardianJugador;
            *listaGuardianJugador = current;
            printf("El Personaje n°%d ha sido seleccionado.\n", IdGuerrero);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("El Personaje N %d no fue encontrado\n", IdGuerrero);
}

void addGuardian(Guardian **head, int id, char *name, char *type, int health, int AttackPoints, int DefPoints)
{
    Guardian *newGuardian = malloc(sizeof(Guardian));
    strcpy(newGuardian->name, name);
    strcpy(newGuardian->type, type);
    newGuardian->id = id;
    newGuardian->health = health;
    newGuardian->AttackPoints = AttackPoints;
    newGuardian->DefPoints = DefPoints;
    newGuardian->next = *head;
    *head = newGuardian;
}
void addGuardian_Manual(Guardian** head) {
    Guardian* newGuardian = malloc(sizeof(Guardian));
    int opcion = 1;
    newGuardian->id = 1;
    printf("Introduce el nombre de tu Guardian: ");
    scanf("%s", newGuardian->name);
    printf("Introduce el tipo de Guardian: \n");
    printf("[1] Mago \n");
    printf("[2] Vikingo \n");
    printf("[3] Nigromante \n");
    printf("[4] Bestia \n");
    printf("Selecciona tu opcion \n");
    scanf("%d", &opcion);
    while (opcion < 1 || opcion > 4)
    {
        system("cls");
        printf("OPCION NO VALIDA, INGRESE UNA OPCION CORRECTA\n");
        printf("Introduce el tipo de Guardian: \n");
        printf("[1] Mago \n");
        printf("[2] Vikingo \n");
        printf("[3] Nigromante \n");
        printf("[4] Bestia \n");
        printf("Selecciona tu opcion \n");
        scanf("%d", &opcion);
    }
    switch (opcion)
    {
    case 1:
        strcpy(newGuardian->type, "Mago");
        break;
    case 2: 
        strcpy(newGuardian->type, "Vikingo");
        break;
    case 3: 
        strcpy(newGuardian->type, "Nigromante");
        break;
    case 4: 
        strcpy(newGuardian->type, "Bestia");
        break;
    default:
        break;
    }
    newGuardian -> health = rand()% 550 + 450;
    newGuardian -> AttackPoints = rand()% 200 + 100;
    newGuardian -> DefPoints = rand()% 100 + 30;
    newGuardian -> next = *head;
    *head = newGuardian;
}
void printGuardian(Guardian *head)
{
    Guardian *current = head;
    while (current != NULL)
    {
        printf("|ID: %d|, |Nombre: %s|, |Tipo:%s|, |Health:%d|, |AttackPoints:%d|, |DefPoints:%d| \n", current->id, current->name, current->type, current->health, current->AttackPoints, current->DefPoints);
        current = current->next;
    }
}
void freeGuardian(Guardian **listaGuardianes)
{
    Guardian *current = *listaGuardianes;
    while (current != NULL)
    {
        Guardian *next = current->next;
        free(current);
        current = next;
    }
}
void SelectEnemyGuardians(Guardian **listaGuardianes, Guardian **listaGuardianesEnemigo)
{
    Guardian *listaGuardianesAux = NULL;
    int numGuardianes = 0;
    int Elegido = 0;
    Guardian *current = *listaGuardianes;
    while (current != NULL)
    {
        numGuardianes++;
        current = current->next;
    }

    for (int i = 0; i < 3; i++)
    {
        int randomIndex = rand() % numGuardianes + 1;
        current = *listaGuardianes;
        for (int j = 1; j < randomIndex; j++)
        {
            current = current->next;
        }
        Guardian *chosenGuardian = current;
        Guardian *auxCurrent = listaGuardianesAux;

        while (auxCurrent != NULL)
        {
            if (auxCurrent->id == chosenGuardian->id)
            {
                Elegido = 1;
                break;
            }
            auxCurrent = auxCurrent->next;
        }
        if (Elegido == 1)
        {
            i--;
            continue;
        }
        addGuardian(listaGuardianesEnemigo, chosenGuardian->id, chosenGuardian->name, chosenGuardian->type, chosenGuardian->health, chosenGuardian->AttackPoints, chosenGuardian->DefPoints);
    }
    freeGuardian(&listaGuardianesAux);
}
int getRollResult()
{
    int dado = rand() % 6 + 1;
    return dado;
}
void combat(Guardian *jugador, Guardian *enemigos)
{
    int turno = 1;
    Guardian JugadorCopia = *jugador;
    Guardian *actual = enemigos;
    Guardian *previo = NULL;
    double factor = 1.0;
    int dados = 0;
    int accion1, accion2 = 0;
    while (jugador->health > 0 && actual != NULL)
    {
        system("cls");
        printf("Enfrentando a %s\n", actual->name);
        printf("Salud del jugador: %d\n", jugador->health);
        printf("Salud del enemigo: %d\n", actual->health);
        while (jugador->health > 0 && actual->health > 0)
        {
            if (turno == 1)
            {
                printf("Es tu turno:\n");
                printf("1 - Atacar\n");
                printf("2 - Defenderte\n");
                scanf("%d", &accion1);
                dados = getRollResult();
                printf("Te ha salido un %d\n", dados);
                if (accion1 == 1)
                {
                    if (dados == 1 || dados == 3 || dados == 5)
                    {

                        if (dados == 1)
                        {
                            factor = 0.8;
                        }
                        if (dados == 3)
                        {
                            factor = 1;
                        }
                        if (dados == 5)
                        {
                            factor = 1.3;
                        }
                        if (dados % 2 == 0)
                        {
                            printf("El enemigo ha bloqueado tu ataque.\n");
                        }
                        else
                        {
                            printf("Has atacado al enemigo con %d puntos de ataque.\n", (int)(jugador->AttackPoints * factor));
                            actual->health -= (int)(jugador->AttackPoints * factor);
                        }
                    }
                    else
                    {
                        printf("Tu ataque no tuvo efecto.\n");
                    }
                }

                if (accion1 == 2)
                {
                    if (dados == 2 || dados == 4 || dados == 6)
                    {
                        factor = 1.0;
                        if (dados == 2)
                        {
                            factor = 0.5;
                        }
                        else if (dados == 6)
                        {
                            factor = 1.2;
                        }
                        if (dados % 2 == 1)
                        {
                            printf("El enemigo ha aplicado desgaste sobre tus puntos de defensa.\n");
                            jugador->DefPoints -= (int)(jugador->DefPoints * 0.1);
                        }
                        else
                        {
                            printf("Te has defendido y has ganado %d puntos de salud.\n", (int)(jugador->DefPoints * factor));
                            jugador->health += (int)(jugador->DefPoints * factor);
                        }
                    }
                }
                if (dados == 6)
                {
                    printf("Te has salido un 6, tienes un turno adicional\n");
                    printf("1 - Atacar\n");
                    printf("2 - Defenderte\n");
                    scanf("%d", &accion1);
                    dados = getRollResult();
                    printf("Te ha salido un %d\n", dados);
                    if (accion1 == 1)
                    {
                        if (dados == 1 || dados == 3 || dados == 5)
                        {

                            if (dados == 1)
                            {
                                factor = 0.8;
                            }
                            if (dados == 3)
                            {
                                factor = 1;
                            }
                            if (dados == 5)
                            {
                                factor = 1.3;
                            }
                            if (dados % 2 == 0)
                            {
                                printf("El enemigo ha bloqueado tu ataque.\n");
                            }
                            else
                            {
                                printf("Has atacado al enemigo con %d puntos de ataque.\n", (int)(jugador->AttackPoints * factor));
                                actual->health -= (int)(jugador->AttackPoints * factor);
                            }
                        }
                    }

                    if (accion1 == 2)
                    {
                        if (dados == 2 || dados == 4 || dados == 6)
                        {
                            factor = 1.0;
                            if (dados == 2)
                            {
                                factor = 0.5;
                            }
                            else if (dados == 6)
                            {
                                factor = 1.2;
                            }
                            if (dados % 2 == 1)
                            {
                                printf("El enemigo ha aplicado desgaste sobre tus puntos de defensa.\n");
                                jugador->DefPoints -= (int)(jugador->DefPoints * 0.1);
                            }
                            else
                            {
                                printf("Te has defendido y has ganado %d puntos de salud.\n", (int)(jugador->DefPoints * factor));
                                jugador->health += (int)(jugador->DefPoints * factor);
                            }
                        }
                    }
                }
            }
#pragma region bot
            // Turno del Bot
            if (turno == -1)
            {
                printf("--------------------------------------------------------\n");
                printf("Turno del enemigo:\n");
                accion2 = rand() % 2 + 1;
                dados = getRollResult();
                printf("Al bot le ha salido un %d\n", dados);
                if (accion2 == 1)
                {
                    printf("El bot ha elegido Atacar\n");
                    if (dados == 1 || dados == 3 || dados == 5)
                    {

                        if (dados == 1)
                        {
                            factor = 0.8;
                        }
                        if (dados == 5)
                        {
                            factor = 1.3;
                        }
                        if (dados % 2 == 0)
                        {
                            printf("Has bloqueado su ataque.\n");
                        }
                        else
                        {
                            printf("El enemigo te ha atacado con %d puntos de ataque.\n", (int)(actual->AttackPoints * factor));
                            jugador->health -= (int)(actual->AttackPoints * factor);
                        }
                    }
                }

                if (accion2 == 2)
                {
                    printf("El bot ha elegido Defenderse\n");
                    if (dados == 2 || dados == 4 || dados == 6)
                    {
                        factor = 1.0;
                        if (dados == 2)
                        {
                            factor = 0.5;
                        }
                        else if (dados == 6)
                        {
                            factor = 1.2;
                        }
                        if (dados % 2 == 1)
                        {
                            printf("El enemigo ha aplicado desgaste sobre sus puntos de defensa.\n");
                            actual->DefPoints -= (int)(actual->DefPoints * 0.1);
                        }
                        else
                        {
                            printf("El bot se ha defendido y ha ganado %d puntos de salud.\n", (int)(actual->DefPoints * factor));
                            actual->health += (int)(actual->DefPoints * factor);
                        }
                    }
                }
                // Turno Adicional del Bot
                if (dados == 6)
                {
                    printf("Turno Extra del enemigo del enemigo:\n");
                    accion2 = rand() % 2 + 1;
                    dados = getRollResult();
                    printf("Al bot le ha salido un %d\n", dados);
                    if (accion2 == 1)
                    {
                        printf("El bot ha elegido atacar");
                        if (dados == 1 || dados == 3 || dados == 5)
                        {

                            if (dados == 1)
                            {
                                factor = 0.8;
                            }
                            if (dados == 3)
                            {
                                factor = 1;
                            }
                            if (dados == 5)
                            {
                                factor = 1.3;
                            }
                            if (dados % 2 == 0)
                            {
                                printf("El enemigo ha bloqueado tu ataque.\n");
                            }
                            else
                            {
                                printf("Te han atacado con %d puntos de ataque.\n", (int)(actual->AttackPoints * factor));
                                jugador->health -= (int)(actual->AttackPoints * factor);
                            }
                        }
                    }

                    if (accion1 == 2)
                    {
                        printf("El bot ha elegido Defenderse\n");
                        if (dados == 2 || dados == 4 || dados == 6)
                        {
                            factor = 1.0;
                            if (dados == 2)
                            {
                                factor = 0.5;
                            }
                            else if (dados == 6)
                            {
                                factor = 1.2;
                            }
                            if (dados % 2 == 1)
                            {
                                printf("El enemigo ha aplicado desgaste sobre sus puntos de defensa.\n");
                                actual->DefPoints -= (int)(actual->DefPoints * 0.1);
                            }
                            else
                            {
                                printf("El bot se ha defendido y ha ganado %d puntos de salud.\n", (int)(actual->DefPoints * factor));
                                actual->health += (int)(actual->DefPoints * factor);
                            }
                        }
                    }
                }
            }
        #pragma endregion
            printf("--------------------------------------------------------\n");
            printf("Enfrentando a %s\n", actual->name);
            printf("Salud del jugador: %d\n", jugador->health);
            printf("Salud del enemigo: %d\n", actual->health);
            printf("--------------------------------------------------------\n");
            turno *= -1;
            if (actual->health <= 0)
            {
                // el jugador ha derrotado al enemigo actual
                printf("¡Has derrotado a %s!\n", actual->name);

                // actualiza los punteros "actual" y "previo"
                if (previo == NULL)
                {
                    enemigos = actual->next; // el primer enemigo de la lista cambia
                }
                else
                {
                    previo->next = actual->next; // el enemigo anterior apunta al siguiente enemigo
                }
                *jugador = JugadorCopia;         // Reestablece las estidisticas del jugador
                Guardian *enemigo_temp = actual; // guarda el enemigo actual en una variable temporal
                actual = actual->next;           // actualiza el enemigo actual
                free(enemigo_temp);              // libera la memoria del enemigo derrotado

                if (actual == NULL)
                {
                    // se han derrotado a todos los enemigos de la lista
                    printf("Has derrotado a todos los enemigos!\n");
                    break; // sale del bucle interno si no hay más enemigos en la lista
                }
                else
                {
                    // actualiza el enemigo actual
                    printf("Prepárate para el siguiente enemigo!\n");
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    Guardian *listaGuardianes = NULL;
    Guardian *ListaGuardianJugador = NULL;
    Guardian *ListaGuardianesEnemigo = NULL;
    int id = 0;
    srand(time(NULL));
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }
    char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", file_name);
        return 1;
    }
    char line[100];
    while (fgets(line, 100, file) != NULL)
    {
        char *token;
        token = strtok(line, ",");
        char name[50];
        char type[50];
        strcpy(name, token);
        token = strtok(NULL, ",");
        strcpy(type, token);
        int health = atoi(strtok(NULL, ","));
        int AttackPoints = atoi(strtok(NULL, ","));
        int DefPoints = atoi(strtok(NULL, ","));
        id++;
        //printf("|ID: %d|,|Nombre: %s|, |Tipo:%s|, |Health:%d|, |AttackPoints:%d|, |DefPoints:%d| \n", id, name, type, health, AttackPoints, DefPoints);
        addGuardian(&listaGuardianes, id, name, type, health, AttackPoints, DefPoints);
    }
    fclose(file);
    int opcion = 0;
    int personajeCreado = 0;
    int personaje_Elegido = 0;
    do
    {
        printf("Selecciona una opcion:\n");
        printf("1. Seleccionar un Personaje para pelear\n");
        printf("2. Cree su propio Personaje\n");
        printf("3. Iniciar Torneo\n");
        printf("4. Salir\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            if(personajeCreado == 0)
            {
                SelectGuardian(&listaGuardianes, &ListaGuardianJugador);
                printf("------- LISTA Jugador 1-------\n");
                printGuardian(ListaGuardianJugador);
                personaje_Elegido = 1;
            }else{
              printf("Ya tienes un personaje\n");  
            }
            break;
        case 2:
            if(personajeCreado == 0)
            {
                addGuardian_Manual(&ListaGuardianJugador);
                printGuardian(ListaGuardianJugador);
                personaje_Elegido = 1;
            }else{
                printf("Ya tienes un personaje\n");  
            }
            break;
        case 3:
            if (personaje_Elegido == 1)
            {
                SelectEnemyGuardians(&listaGuardianes, &ListaGuardianesEnemigo);
                printf("------- LISTA Enemigos -------\n");
                printGuardian(ListaGuardianesEnemigo);
                combat(ListaGuardianJugador, ListaGuardianesEnemigo);
            }else{
                printf("No tiene personajes en tu equipo para combatir, seleccione o cree uno\n");
            }
            break;
        case 4:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 3);
    freeGuardian(&ListaGuardianJugador);
    freeGuardian(&listaGuardianes);
    return 0;
}
