## Philosophers

**Philosophers** es un proyecto desarrollado en **42 Madrid** que consiste en la implementación de una simulación basada en el problema clásico de los filósofos comensales. Se debe gestionar la concurrencia utilizando **hilos (threads)** y **mutexes** para evitar condiciones de carrera y bloqueos.

![Logo 42 Madrid](42-Madrid.jpeg)

### 🏛️ Descripción del Proyecto

El programa simula una mesa donde varios filósofos alternan entre **comer, pensar y dormir**, siguiendo reglas estrictas para el uso de los tenedores compartidos. Cada filósofo representa un **hilo**, y los tenedores están protegidos por **mutexes** para evitar problemas de concurrencia.

#### Características Principales

- **Gestión de hilos** con `pthread_create`, `pthread_join`, y `pthread_detach`.
- **Sincronización con mutexes** para evitar condiciones de carrera.
- **Simulación en tiempo real** con `gettimeofday()` y `usleep()`.
- **Gestión de memoria eficiente** sin fugas.
- **Control de finalización** basado en reglas de inanición o límite de comidas.

### 📁 Archivos Incluidos

- `main.c` → Función principal que valida los argumentos y gestiona la simulación.
- `utils.c` → Funciones auxiliares, como medición de tiempo y validación de números.
- `parsing.c` → Procesamiento de los argumentos de entrada.
- `init.c` → Inicialización de estructuras y asignación de recursos.
- `actions.c` → Implementación de las acciones de los filósofos (comer, pensar, dormir).
- `dinner.c` → Gestión de la simulación y creación de hilos.
- `death.c` → Monitorización de la muerte de los filósofos.
- `handle.c` → Gestión de mutexes y operaciones sobre hilos.
- `safe_malloc.c` → Asignación segura de memoria con manejo de errores.
- `synchro.c` → Funciones para sincronización de los hilos y verificación del estado de la simulación.
- `values.c` → Funciones para gestionar valores protegidos por mutexes.
- `write.c` → Función para imprimir estados de los filósofos con control de concurrencia.
- `philosophers.h` → Cabecera con estructuras y prototipos de funciones.
- `Makefile` → Compila el proyecto y gestiona reglas como `all`, `clean`, `fclean`, `re`.

### 🚀 Cómo Usarlo

1. **Compilación:**
   ```bash
   make
   ```

2. **Ejecución:**
   ```bash
   ./philo <num_philos> <time_to_die> <time_to_eat> <time_to_sleep> [num_meals]
   ```
   Ejemplo:
   ```bash
   ./philo 5 800 200 200 5
   ```
   - `num_philos` → Número de filósofos (y tenedores).
   - `time_to_die` → Tiempo en milisegundos antes de morir si no come.
   - `time_to_eat` → Tiempo en milisegundos que tarda en comer.
   - `time_to_sleep` → Tiempo en milisegundos que tarda en dormir.
   - `num_meals` (opcional) → Si se especifica, la simulación termina cuando todos los filósofos han comido al menos esta cantidad de veces.

3. **Salida esperada:**
   - El programa imprimirá los eventos de los filósofos, por ejemplo:
     ```plaintext
     150 1 has taken a fork
     152 1 has taken a fork
     155 1 is eating
     355 1 is sleeping
     555 1 is thinking
     ```
   - Si un filósofo muere, se imprimirá:
     ```plaintext
     900 2 died
     ```

### 🔧 Operaciones Implementadas

Cada filósofo puede ejecutar las siguientes acciones:

- `TAKE_FIRST_FORK` → Toma el primer tenedor.
- `TAKE_SECOND_FORK` → Toma el segundo tenedor.
- `EATING` → Come durante `time_to_eat` ms.
- `SLEEPING` → Duerme durante `time_to_sleep` ms.
- `THINKING` → Piensa antes de volver a intentar comer.
- `DIED` → Un filósofo muere si supera `time_to_die` sin comer.

### 🛠️ Estrategias de Sincronización

El programa implementa varias estrategias para garantizar un correcto funcionamiento:

- **Mutexes** para sincronizar el acceso a los tenedores.
- **Estrategia de asignación de tenedores** para minimizar bloqueos.
- **Uso de `usleep` y `gettimeofday`** para controlar tiempos de espera precisos.
- **Monitorización de la muerte de los filósofos** para finalizar la simulación a tiempo.

### ⚠️ Reglas de Evaluación

- **Sin fugas de memoria**: Todo recurso asignado debe liberarse.
- **No debe haber "data races"**: Se deben usar mutexes correctamente.
- **Debe funcionar con cualquier cantidad de filósofos**.

Este proyecto sigue los estándares de la **Norma de 42** y debe ejecutarse sin errores inesperados.
