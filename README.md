# Philosophers (42 Project)

## Introducción

**Philosophers** es un proyecto de la escuela 42 basado en el clásico problema de concurrencia de Edsger Dijkstra: **“The Dining Philosophers Problem”**.

El objetivo principal es diseñar un sistema multihilo y multiproceso eficiente, logrando un control absoluto sobre el ciclo de vida del hardware para evitar colapsos del sistema.

### Objetivos Técnicos Alcanzados:
- Gestión avanzada de **concurrencia y paralelismo**.
- Eliminación absoluta de **Data Races** (condiciones de carrera).
- Prevención activa de **Deadlocks** (bloqueos mutuos) y **Starvation** (inanición).
- Sincronización precisa mediante **Threads, Mutexes, Procesos (fork) y Semáforos**.

El proyecto se divide en dos arquitecturas completamente diferentes:
1. **Parte obligatoria (`philo`)** → Memoria compartida mediante Threads + Mutex.
2. **Parte bonus (`philo_bonus`)** → Memoria aislada mediante Procesos + Semáforos POSIX.

---

## El Problema y sus Reglas

- **N Filósofos** se sientan en una mesa redonda con un cuenco de espaguetis en el centro.
- Hay exactamente **un tenedor entre cada filósofo** (N filósofos = N tenedores).
- Para comer, un filósofo necesita obligatoriamente **dos tenedores** (el izquierdo y el derecho).
- Ciclo de vida: **Tomar tenedores ➔ Comer ➔ Dormir ➔ Pensar**.
- Si un filósofo pasa más de `time_to_die` milisegundos sin empezar a comer desde su última comida (o desde el inicio de la simulación), **muere por inanición** y el programa debe finalizar inmediatamente.

---

## Parámetros de Ejecución

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```

---

## Parte Obligatoria — `philo` (Threads & Mutex)

### Modelo de Concurrencia

Cada filósofo se ejecuta de forma independiente en su propio **hilo (`pthread`)**. Al compartir el mismo espacio de memoria, todos los accesos a variables críticas se encuentran protegidos magnéticamente por **Mutexes** para evitar corrupción de datos (*Data Races*).

### Estrategia anti-Deadlock

Para evitar el escenario fatal donde todos los filósofos levantan el tenedor izquierdo al mismo tiempo y se quedan esperando eternamente el derecho, implementé una estrategia de **desfase temporal e inversión de prioridad de hilos**:

* Los filósofos con ID impar retrasan sutilmente su rutina inicial con un breve `usleep`.
* Los filósofos pares e impares toman sus tenedores en orden invertido (izquierdo-derecho / derecho-izquierdo), rompiendo la condición de espera circular.

### Arquitectura de Monitoreo

* **Hilos de simulación:** 1 hilo por cada filósofo ejecutando la rutina de manera asíncrona.
* **Hilo Monitor Global:** Un hilo dedicado exclusivamente a supervisar la mesa. Realiza un bucle de alta frecuencia comprobando si `tiempo_actual - tiempo_ultima_comida > time_to_die`. Si detecta una muerte, activa de forma segura un flag protegido por Mutex que detiene instantáneamente la impresión y ejecución del resto de hilos.

---

## Parte Bonus — `philo_bonus` (Procesos & Semáforos)

### Modelo de Concurrencia

En esta arquitectura, cada filósofo es un **proceso hijo independiente (`fork`)**. Al no compartir memoria, los tenedores dejan de ser individuales y se gestionan como un recurso global centralizado en el sistema operativo mediante un **Semáforo POSIX**.

### Arquitectura de Monitoreo Distribuido

* **Proceso Padre:** Se encarga de spawnear los procesos de los filósofos, monitorizar los códigos de salida y realizar una limpieza masiva mediante señales (`kill`) si la simulación acaba.
* **Monitores Locales:** Cada proceso hijo (cada filósofo) levanta internamente **un hilo monitor propio**. Si el filósofo muere, su monitor local captura el evento de forma inmediata, imprime el deceso y ejecuta un `exit(1)` que es recogido por el padre.

### Semáforos Utilizados

| Semáforo | Tipo | Función Principal |
| --- | --- | --- |
| `sem_forks` | Contador | Representa el total de tenedores libres en la mesa. |
| `sem_print` | Binario | Mutex para evitar que los mensajes de la terminal se solapen. |
| `sem_eat` | Binario | Protege la lectura/escritura de los tiempos de comida individuales. |
| `sem_room` | Contador | Limitador de entrada a la mesa (permite un máximo de $N-1$ filósofos compitiendo por tenedores para mitigar bloqueos). |

---

## Diferencias Clave: Mutex vs Semáforos

| Característica | `philo` (Obligatoria) | `philo_bonus` (Bonus) |
| --- | --- | --- |
| **Aislamiento** | Hilos (Comparten Memoria) | Procesos (Memoria Propia/Aislada) |
| **Sincronización** | `pthread_mutex_t` | Semáforos con nombre (`sem_open`) |
| **Ubicación Monitor** | Hilo externo centralizado | Hilo dedicado dentro de cada proceso |
| **Mecanismo de Parada** | Flag booleano en Mutex | Señal de salida `exit()` capturada por `waitpid` |
| **Liberación** | `pthread_join` & `pthread_mutex_destroy` | `kill` de procesos & `sem_close/unlink` |

---

## Compilación y Uso

Ambas secciones incluyen un `Makefile` optimizado con flags estrictos de compilación (`-Wall -Wextra -Werror`).

```bash
# Para compilar la versión de hilos (obligatoria)
cd philo && make
./philo 5 800 200 200

# Para compilar la versión de procesos (bonus)
cd ../philo_bonus && make
./philo_bonus 5 800 200 200

```