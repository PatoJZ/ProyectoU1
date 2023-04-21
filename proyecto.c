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
    printf("El Personaje N°%d no fue encontrado\n", IdGuerrero);
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
void combat(Guardian *jugador, Guardian *enemigos, int num_enemigos)
{
    int jugador_turno = 1;
    Guardian *actual = enemigos;
    Guardian *previo = NULL;

    while (jugador->health > 0 && actual != NULL)
    {
        printf("Enfrentando a %s\n", actual->name);
        printf("Salud del jugador: %d\n", jugador->health);
        printf("Salud del enemigo: %d\n", actual->health);
        while (jugador->health > 0 && actual->health > 0)
        {
            int accion1, accion2 = -1;
            if (jugador_turno == 1)
            {
                printf("Es tu turno:\n");
                printf("1 - Atacar\n");
                printf("2 - Defenderte\n");
                scanf("%d", &accion1);
                if (accion1 == 6)
                {
                    printf("Lanzando dados para acción adicional...\n");
                    accion2 = rand() % 6 + 1;
                    printf("Has obtenido un %d\n", accion2);
                }
            }
            else
            {
                printf("Turno del enemigo:\n");
                accion1 = rand() % 6 + 1;
                printf("El enemigo ha elegido la accion %d\n", accion1);
                if (accion1 == 6)
                {
                    printf("Lanzando dados para acción adicional...\n");
                    accion2 = rand() % 6 + 1;
                    printf("El enemigo ha obtenido un %d\n", accion2);
                }
            }
            if (accion1 == 1 || accion1 == 3 || accion1 == 5)
            {
                float factor = 1.0;
                if (accion1 == 1)
                {
                    factor = 0.8;
                }
                else if (accion1 == 5)
                {
                    factor = 1.3;
                }
                if (accion2 % 2 == 0)
                {
                    printf("El enemigo ha bloqueado tu ataque.\n");
                }
                else
                {
                    printf("Has atacado al enemigo con %d puntos de ataque.\n", (int)(jugador->AttackPoints * factor));
                    actual->health -= (int)(jugador->AttackPoints * factor);
                }
            }
            else if (accion1 == 2 || accion1 == 4 || accion1 == 6)
            {
                float factor = 1.0;
                if (accion1 == 2)
                {
                    factor = 0.5;
                }
                else if (accion1 == 6)
                {
                    factor = 1.2;
                }
                if (accion2 % 2 == 1)
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
            printf("--------------------------------------------------------\n");
            printf("Enfrentando a %s\n", actual->name);
            printf("Salud del jugador: %d\n", jugador->health);
            printf("Salud del enemigo: %d\n", actual->health);
            printf("--------------------------------------------------------\n");
            jugador_turno = !jugador_turno;
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
                Guardian *enemigo_temp = actual; // guarda el enemigo actual en una variable temporal
                actual = actual->next;   // actualiza el enemigo actual
                free(enemigo_temp);                      // libera la memoria del enemigo derrotado

                // aumenta la cantidad de enemigos derrotados
                num_enemigos++;

                if (actual == NULL)
                {
                    // se han derrotado a todos los enemigos de la lista
                    printf("¡Has derrotado a todos los enemigos!\n");
                    break; // sale del bucle interno si no hay más enemigos en la lista
                }
                else
                {
                    // actualiza el enemigo actual
                    printf("¡Prepárate para el siguiente enemigo!\n");
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
        printf("|ID: %d|,|Nombre: %s|, |Tipo:%s|, |Health:%d|, |AttackPoints:%d|, |DefPoints:%d| \n", id, name, type, health, AttackPoints, DefPoints);
        addGuardian(&listaGuardianes, id, name, type, health, AttackPoints, DefPoints);
    }
    fclose(file);
    printf("------- LISTA -------\n");
    printGuardian(listaGuardianes);
    SelectGuardian(&listaGuardianes, &ListaGuardianJugador);
    printf("------- LISTA Jugador 1-------\n");
    printGuardian(ListaGuardianJugador);
    SelectEnemyGuardians(&listaGuardianes, &ListaGuardianesEnemigo);
    printf("------- LISTA Enemigos -------\n");
    printGuardian(ListaGuardianesEnemigo);
    combat(ListaGuardianJugador, ListaGuardianesEnemigo, 3);
    freeGuardian(&ListaGuardianJugador);
    freeGuardian(&listaGuardianes);
    return 0;
}
