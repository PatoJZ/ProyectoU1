
# The Guardian Tournament | Proyecto U1 Algoritmos y Estructuras de Datos

Este es un programa en C que simula un juego de pelea entre un jugador y una serie de enemigos. El objetivo del jugador es derrotar a todos los enemigos para ganar el juego.

## 📝 Problema y solucion 
La problemática que se nos presenta es acerca de implementar un sistema de combate por turnos, junto con la posibilidad de implementar guardianes previamente escritos en archivo para incorporalos en el juego.

El código utiliza una estructura de datos de Guardianes y una lista enlazada para almacenar los personajes del jugador y los enemigos. El programa lee un archivo de texto que contiene información sobre los personajes, incluyendo su nombre, tipo, salud, puntos de ataque y puntos de defensa, y los agrega a la lista de Guardianes.

## 📃 Instrucciones
Para jugar, simplemente ejecute el programa en una consola de comando junto con el archivo `ListaGuardianes.txt`. El programa le pedirá que seleccione su personaje y le mostrará una lista de enemigos para elegir. Una vez que haya seleccionado a su enemigo, comenzará la pelea.

Durante la pelea, se le pedirá al jugador que seleccione una acción: atacar o defenderse. El jugador lanzará un dado para determinar el éxito de la acción. Dependiendo del resultado del dado, el jugador infligirá daño al enemigo o recuperará puntos de salud.

## 🤔 Aspectos Generales
El menú del juego ofrece varias opciones, como seleccionar un personaje, crear uno nuevo, seleccionar la dificultad del torneo y comenzar la pelea. Si el usuario selecciona la opción de pelear, el programa selecciona enemigos de la lista de personajes y el jugador debe luchar contra ellos.

El código utiliza varias funciones para realizar diversas tareas, como imprimir la lista de personajes, agregar un personaje nuevo, seleccionar un personaje para luchar, seleccionar enemigos y comenzar la pelea. El código también libera la memoria asignada dinámicamente para los personajes después de que se completa el juego.

El programa utiliza la biblioteca de funciones de tiempo estándar para inicializar la semilla de generación de números aleatorios. El código también utiliza la función de limpieza de pantalla de la biblioteca de funciones del sistema para borrar la pantalla en varias ocasiones durante la ejecución del programa.

El archivo de entrada de datos del programa se especifica como un argumento de línea de comandos y se verifica si se ha proporcionado correctamente antes de abrir el archivo para su lectura.

En resumen, el programa es un juego de combate de guardianes simple pero entretenido que permite al usuario seleccionar y crear personajes para luchar contra enemigos en un torneo.



## 💻 Como iniciar el programa

Introduce este comando en la consola

```bash
  proyecto.exe ListaGuardianes.txt
```



