#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Guardian{
    int id; 
    char name[50];
    char type[50];
    int health;
    int AttackPoints;
    int DefPoints;
    struct Guardian* next;
}Guardian;

void SelectGuardian(Guardian** listaGuardianes, Guardian** listaGuardianJugador) {
    int IdGuerrero;
    printf("Seleccione un personaje para Jugar: ");
    scanf("%d", &IdGuerrero);
    
    Guardian* current = *listaGuardianes;
    Guardian* prev = NULL;
    while (current != NULL) {
        if (current->id == IdGuerrero) { // Encontró el personaje
            if (prev == NULL) { // Es el primer elemento de la lista original
                *listaGuardianes = current->next;
            } else {
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

void addGuardian(Guardian** head, int id, char *name, char *type, int health, int AttackPoints, int DefPoints) {
    Guardian* newGuardian = malloc(sizeof(Guardian));
    strcpy(newGuardian->name, name);
    strcpy(newGuardian->type, type);
    newGuardian-> id = id;
    newGuardian->health = health;
    newGuardian->AttackPoints = AttackPoints;
    newGuardian->DefPoints = DefPoints;
    newGuardian->next = *head;
    *head = newGuardian;
}
void printGuardian(Guardian* head){
    Guardian* current = head;
    while(current != NULL){
        printf("|ID: %d|, |Nombre: %s|, |Tipo:%s|, |Health:%d|, |AttackPoints:%d|, |DefPoints:%d| \n",current -> id ,current ->name,current ->type,current ->health,current ->AttackPoints, current -> DefPoints);
        current = current -> next;
    }
}
void freeGuardian(Guardian** listaGuardianes){
    Guardian* current = *listaGuardianes;
    while (current!= NULL) {
        Guardian* next = current -> next;
        free(current);
        current = next;
    }
}
void SelectEnemyGuardians(Guardian** listaGuardianes, Guardian** listaGuardianesEnemigo) {
    Guardian* listaGuardianesAux = NULL;
    int numGuardianes = 0;
    int Elegido = 0;
    Guardian* current = *listaGuardianes;
    while (current != NULL) {
        numGuardianes++;
        current = current->next;
    }
    
    for (int i = 0; i < 3; i++) {
        int randomIndex = rand()%numGuardianes + 1;
        current = *listaGuardianes;
        for (int j = 1; j < randomIndex; j++) {
            current = current->next;
        }
        Guardian* chosenGuardian = current;
        Guardian* auxCurrent = listaGuardianesAux;
        
        while (auxCurrent != NULL) {
            if (auxCurrent->id == chosenGuardian->id) {
                Elegido = 1;
                break;
            }
            auxCurrent = auxCurrent->next;
        }
        if (Elegido == 1) {
            i--;
            continue;
        }
        addGuardian(listaGuardianesEnemigo, chosenGuardian->id, chosenGuardian->name, chosenGuardian->type, chosenGuardian->health, chosenGuardian->AttackPoints, chosenGuardian->DefPoints);
    }
    freeGuardian(&listaGuardianesAux);
}
void combat(Guardian* jugador, Guardian* enemigo) {
    int jugador_turno = 1;
    while (jugador->health > 0 && enemigo->health > 0) {
        int accion;
        if (jugador_turno) {
            printf("Es tu turno:\n");
            printf("1 - Atacar\n");
            printf("2 - Defenderte\n");
            scanf("%d", &accion);
        } else {
            printf("Turno del enemigo:\n");
            accion = rand() % 6 + 1;
            printf("El enemigo ha elegido la accion %d\n", accion);
        }
        if ((jugador_turno && (accion == 1 || accion == 3 || accion == 5)) ||(!jugador_turno && (accion == 2 || accion == 4 || accion == 6))) {
            // Atacar
            if (jugador_turno) {
                printf("Has atacado al enemigo con %d puntos de ataque.\n", jugador->AttackPoints);
                enemigo->health -= jugador->AttackPoints;
            } else {
                printf("El enemigo te ha atacado con %d puntos de ataque.\n", enemigo->AttackPoints);
                jugador->health -= enemigo->AttackPoints;
            }
        } else {
            // Defenderse
            if (jugador_turno) {
                printf("Te has defendido y has ganado %d puntos de salud.\n", jugador->DefPoints);
                jugador->health += jugador->DefPoints;
            } else {
                printf("El enemigo se ha defendido y ha ganado %d puntos de salud.\n", enemigo->DefPoints);
                enemigo->health += enemigo->DefPoints;
            }
        }
        printf("Salud del jugador: %d\n", jugador->health);
        printf("Salud del enemigo: %d\n", enemigo->health);
        jugador_turno = !jugador_turno;
    }
    if (jugador->health <= 0) {
        printf("Has perdido el combate. El enemigo ha ganado.\n");
    } else {
        printf("Has ganado el combate. El enemigo ha sido derrotado.\n");
    }

}
int main(int argc, char *argv[]){
    Guardian* listaGuardianes = NULL;
    Guardian* ListaGuardianJugador = NULL;
    Guardian* ListaGuardianesEnemigo = NULL;
    int id = 0;
    srand(time(NULL));
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }
    char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", file_name);
        return 1;
    }
    char line[100];
    while (fgets(line, 100, file) != NULL) {
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
        printf("|ID: %d|,|Nombre: %s|, |Tipo:%s|, |Health:%d|, |AttackPoints:%d|, |DefPoints:%d| \n",id,name, type, health, AttackPoints, DefPoints);
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
    freeGuardian(&ListaGuardianJugador);
    freeGuardian(&listaGuardianes);

    return 0;
}
