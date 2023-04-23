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
typedef struct ColaEnemigosDerrotados {
    Guardian *enemigo;
    struct ColaEnemigosDerrotados *siguiente;
} ColaEnemigosDerrotados;


void encolarEnemigoDerrotado(Guardian *enemigo, ColaEnemigosDerrotados **cabezaColaDerrotados) {
    ColaEnemigosDerrotados *nuevoNodo = (ColaEnemigosDerrotados*) malloc(sizeof(ColaEnemigosDerrotados));
    nuevoNodo->enemigo = enemigo;
    nuevoNodo->siguiente = NULL;

    if (*cabezaColaDerrotados == NULL) {
        *cabezaColaDerrotados = nuevoNodo;
    } else {
        ColaEnemigosDerrotados *nodoActual = *cabezaColaDerrotados;
        while (nodoActual->siguiente != NULL) {
            nodoActual = nodoActual->siguiente;
        }
        nodoActual->siguiente = nuevoNodo;
    }
}
void getResult(ColaEnemigosDerrotados *cabezaColaDerrotados) 
{
    printf("Enemigos derrotados:\n");

    ColaEnemigosDerrotados *nodoActual = cabezaColaDerrotados;
    while (nodoActual != NULL) {
        printf(" Derrotaste a %s\n", nodoActual->enemigo->name);
        nodoActual = nodoActual->siguiente;
    }
}
void SelectCharacter(Guardian **listaGuardianes, Guardian **listaGuardianJugador)
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
            printf("El Personaje n%d ha sido seleccionado.\n", IdGuerrero);
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
    newGuardian -> health = (rand()% (550 - 450 + 1)) + 450; //genera un numero entre 450 y 550
    newGuardian -> AttackPoints = (rand()% (200 - 100 + 1)) + 100;
    newGuardian -> DefPoints = (rand()% (100 - 30 + 1)) + 100;
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
void SelectEnemyGuardians(Guardian **listaGuardianes, Guardian **listaGuardianesEnemigo, int dificultad)
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

    for (int i = 0; i < dificultad; i++)
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
void printCharacterStatus(Guardian *personaje, Guardian *Enemigos)
{
        printf("---------------------\n");
        printf("Enfrentando a %s\n", Enemigos->name);
        printf("Salud del jugador: %d\n",personaje->health);
        printf("Salud del enemigo: %d\n", Enemigos->health);
}
void StartFight(Guardian *jugador, Guardian *enemigos)
{
    int turno = 1;
    ColaEnemigosDerrotados *cabezaColaDerrotados = NULL;
    Guardian *JugadorCopia = jugador;
    Guardian *actual = enemigos;
    Guardian *previo = NULL;
    double factor = 1.0;
    int dados = 0;
    int accion1, accion2 = 0;
    while (JugadorCopia->health > 0 && actual != NULL)
    { 
        while (JugadorCopia->health > 0 && actual->health > 0)
        {      
            printf("--------------------------------------------------------\n");
            if (turno == 1)
            {
                system("cls");
                printCharacterStatus(JugadorCopia, actual);
                printf("Es tu turno:\n");
                printf("1 - Atacar\n");
                printf("2 - Defenderte\n");
                printf("Seleccione una opcion: ");
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
                        
                        else
                        {
                            printf("Te has defendido y has ganado %d puntos de salud.\n", (int)(jugador->DefPoints * factor));
                            JugadorCopia->health += (int)(jugador->DefPoints * factor);
                        }
                    
                    }else{
                        printf("El enemigo ha aplicado desgaste sobre tus puntos de defensa.\n");
                        jugador->DefPoints -= (int)(jugador->DefPoints * 0.1);   
                    }
                }
                if (dados == 6)
                {
                    printf("Te has salido un 6, tienes un turno adicional\n");
                    printf("1 - Atacar\n");
                    printf("2 - Defenderte\n");
                    printf(" Seleccione una opcion: ");
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
                        }else{
                            printf("El enemigo ha bloqueado tu ataque.\n");
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
                                JugadorCopia->health += (int)(jugador->DefPoints * factor);
                            }
                        }else{                           
                                printf("El enemigo ha aplicado desgaste sobre tus puntos de defensa.\n");
                                jugador->DefPoints -= (int)(jugador->DefPoints * 0.1);                            
                        }
                    
                    }
                }
                sleep(2);
            }

            // Turno del Bot
            if (turno == -1 && actual -> health > 0)
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
                            JugadorCopia->health -= (int)(actual->AttackPoints * factor);
                        }
                    }else{
                        printf("Has bloqueado su ataque.\n");
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
                            printf("se ha aplicado desgaste sobre sus puntos de defensa.\n");
                            actual->DefPoints -= (int)(actual->DefPoints * 0.1);
                        }
                        else
                        {
                            printf("El bot se ha defendido y ha ganado %d puntos de salud.\n", (int)(actual->DefPoints * factor));
                            actual->health += (int)(actual->DefPoints * factor);
                        }
                    }else{
                        printf("El enemigo ha aplicado desgaste sobre sus puntos de defensa.\n");
                        actual->DefPoints -= (int)(actual->DefPoints * 0.1);
                    }
                }
                sleep(2);
                // Turno Adicional del Bot
                if (dados == 6)
                {
                    printf("Turno Extra del enemigo del enemigo:\n");
                    accion2 = rand() % 2 + 1;
                    dados = getRollResult();
                    printf("Al bot le ha salido un %d\n", dados);
                    if (accion2 == 1)
                    {
                        printf("El bot ha elegido atacar\n");
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
                                printf("Has bloqueado su ataque.\n");
                            }
                            else
                            {
                                printf("Te han atacado con %d puntos de ataque.\n", (int)(actual->AttackPoints * factor));
                                JugadorCopia->health -= (int)(actual->AttackPoints * factor);
                            }
                        }else{
                            printf("Has bloqueado su ataque.\n");
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
                        }else{
                            printf("El enemigo ha aplicado desgaste sobre sus puntos de defensa.\n");
                            actual->DefPoints -= (int)(actual->DefPoints * 0.1);
                        }
                    }
                    sleep(2);
                }
            }
            
            turno *= -1;
            if (actual->health <= 0)
            {
                // el jugador ha derrotado al enemigo actual
                printf("Has derrotado a %s!\n", actual->name);
                sleep(3);
                // Encolar para tener un historial de enemigos
                encolarEnemigoDerrotado(actual, &cabezaColaDerrotados);
                // Actualiza los punteros "actual" y "previo"
                if (previo == NULL)
                {
                    enemigos = actual->next; // el primer enemigo de la lista cambia
                }
                else
                {
                    previo->next = actual->next; // el enemigo anterior apunta al siguiente enemigo
                }
                JugadorCopia = jugador;         // Reestablece las estidisticas del jugador
                Guardian *enemigo_temp = actual; // guarda el enemigo actual en una variable temporal
                actual = actual->next;           // actualiza el enemigo actual
                free(enemigo_temp);              // libera la memoria del enemigo derrotado
                turno = 1;   //reestablece el turno para el jugador
                if (actual == NULL)
                {
                    
                    printf("Has derrotado a todos los enemigos!\n"); // se han derrotado a todos los enemigos de la lista
                    getResult(cabezaColaDerrotados); //se guarda en un "historial"
                    sleep(3);
                    break; // sale del bucle interno si no hay más enemigos en la lista
                }
                else
                {
                    // actualiza el enemigo actual
                    printf("Prepárate para el siguiente enemigo!\n");
                    sleep(3);
                }
            }
        }
        if (jugador-> health <= 0)
        {
            printf("Te han derrotado\n");
            sleep(3);
        }
    }
}
int selectTournament()
{   
    int dificultad = 0;
        printf("Seleccione Dificultad\n");
        printf("[1] Principiante (3 Enemigos a derrotar)\n");
        printf("[2] Intermedio   (5 Enemigos a derrotar)\n");
        printf("[3] Experto      (7 Enemigos a derrotar)\n");
        scanf("%d", &dificultad);
        while (dificultad < 1 || dificultad > 3)
        {
            system("cls");
            printf("OPCION NO VALIDA, INGRESE UNA OPCION CORRECTA\n");
            printf("Seleccione Dificultad\n");
            printf("[1] Principiante (3 Enemigos a derrotar)\n");
            printf("[2] Intermedio   (5 Enemigos a derrotar)\n");
            printf("[3] Experto      (7 Enemigos a derrotar)\n");
            scanf("%d", &dificultad);
        }
        switch (dificultad)
        {
        case 1:
            printf("--------------------------------------------------------\n");
            printf("Has seleccionado la dificultad Principiante\n");
            sleep(2);
            break;
        case 2:
            printf("--------------------------------------------------------\n");
            printf("Has seleccionado la dificultad Intermedia\n");
            sleep(2);
            break;
        case 3:
            printf("--------------------------------------------------------\n"); 
            printf("Has seleccionado la dificultad Experto\n");
            sleep(2);
            break;
        default:
            break;
        }
        if (dificultad == 1 || dificultad == 2 ||  dificultad == 3)
        {
            dificultad += dificultad + 1;
        }
        
    return dificultad;
}

int main(int argc, char *argv[])
{
    Guardian *listaGuardianes = NULL;
    Guardian *ListaGuardianJugador = NULL;
    Guardian *ListaGuardianesEnemigo = NULL;
    
    int id = 0;
    int dificultad = 0;
    int opcion = 0;
    int personajeCreado = 0;
    int personaje_Elegido = 0;
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
    // Menu de opciones 
    do
    {   
        system("cls");
        printf("---------------------- BIENVENIDO A The Guardians Tournament --------------------------------\n");
        printf("1. Seleccionar un Personaje para pelear\n");
        printf("2. Cree su propio Personaje\n");
        printf("3. Seleccione Dificultad\n");
        printf("4. Iniciar Torneo\n");
        printf("5. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            if(personajeCreado == 0)
            {
                system("cls");
                printGuardian(listaGuardianes);
                printf("^^^^Lista De Personajes disponibles^^^^^\n");
                SelectCharacter(&listaGuardianes, &ListaGuardianJugador);
                system("cls");
                printf("------- Tu Guardian -------\n");
                printGuardian(ListaGuardianJugador);
                sleep(3);
                personajeCreado = 1;
                personaje_Elegido = 1;
            }else{
                system("cls");
                printf("Ya tienes un personaje\n");
                sleep(2);  
            }
            break;
        case 2:
            if(personajeCreado == 0)
            {
                addGuardian_Manual(&ListaGuardianJugador);
                printGuardian(ListaGuardianJugador);
                personajeCreado = 1;
                personaje_Elegido = 1;
            }else{
                system("cls");
                printf("Ya tienes un personaje\n");  
                sleep(2);
            }
            break;
        case 3:
            dificultad = selectTournament();
            break;
        case 4:
            if (personaje_Elegido == 1)
            {
                if (dificultad != 0)
                {
                SelectEnemyGuardians(&listaGuardianes, &ListaGuardianesEnemigo, dificultad);
                printf("------- LISTA Enemigos -------\n");
                printGuardian(ListaGuardianesEnemigo);
                StartFight(ListaGuardianJugador, ListaGuardianesEnemigo);
                }else{
                    printf("No has seleccionado dificultad, seleccione una");
                    sleep(2);
                }
            }else{
                system("cls");
                printf("No tienes un guardian en tu equipo para combatir, seleccione o cree uno\n");
                sleep(2);
            }
            break;
        case 5:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 5);
    freeGuardian(&ListaGuardianJugador);
    freeGuardian(&listaGuardianes);
    return 0;
}
