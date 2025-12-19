# Philosophers (42 Project)

## 📌 Introducción

**Philosophers** es un proyecto de la escuela 42 basado en el clásico problema de concurrencia  
**“The Dining Philosophers Problem”**.

El objetivo es aprender a:
- Gestionar **concurrencia**
- Evitar **data races**
- Prevenir **deadlocks**
- Trabajar con **threads**, **mutexes**, **procesos** y **semáforos**
- Controlar correctamente la **vida y muerte** de procesos/hilos

El proyecto se divide en dos partes:
- **Parte obligatoria (`philo`)** → Threads + Mutex
- **Parte bonus (`philo_bonus`)** → Procesos + Semáforos

---

## 🧠 El problema de los filósofos

- Hay **N filósofos** sentados alrededor de una mesa.
- Entre cada filósofo hay **un tenedor**.
- Para comer, un filósofo necesita **dos tenedores**.
- Cada filósofo repite el ciclo:
  1. Tomar los tenedores
  2. Comer
  3. Dormir
  4. Pensar
- Si un filósofo no come en `time_to_die`, **muere** y la simulación termina.

---

## ⚙️ Argumentos del programa

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]



## Parte obligatoria — philo

### Modelo de concurrencia
Cada filósofo es un thread.  
Los recursos compartidos (tenedores, impresión, estado) se protegen con mutexes.

### Arquitectura
- 1 thread por filósofo
- 1 thread monitor global

Cada filósofo:
- Bloquea mutexes para coger tenedores
- Actualiza su último tiempo de comida
- Libera mutexes tras comer

### Control de la muerte
El monitor comprueba periódicamente:


Cuando un filósofo muere:
- Se imprime "is dead"
- Se detiene toda la simulación

### Sincronización
- Mutex por tenedor
- Mutex para imprimir
- Mutex para estado global (dead / finished)

---

## Parte bonus — philo_bonus

### Modelo de concurrencia
Cada filósofo es un proceso independiente.  
Se utilizan semáforos POSIX en lugar de mutexes.

### Arquitectura
- 1 proceso por filósofo
- 1 thread monitor dentro de cada proceso

El proceso padre se encarga de:
- Crear filósofos
- Detectar muertes
- Finalizar todos los procesos

### Semáforos utilizados
| Semáforo   | Función |
|------------|---------|
| sem_forks  | Controla el número de tenedores |
| sem_print  | Protege la impresión por pantalla |
| sem_eat    | Protege last_meal y contadores |
| sem_room   | Evita deadlocks |
| sem_dead   | Garantiza un solo mensaje de muerte |

### Rutina de un filósofo (Bonus)
El proceso hijo entra en `philo_routine` y crea un thread monitor.  

El filósofo repite:
- Tomar tenedores (`sem_wait`)
- Comer
- Dormir
- Pensar

El monitor:
- Comprueba si ha muerto
- Si muere:
  - Imprime "is dead"
  - Llama a `exit(1)`

El proceso padre:
- Detecta el `exit(1)`
- Mata al resto de filósofos
- Limpia recursos

### Diferencias clave entre philo y philo_bonus
| Característica      | philo (obligatoria) | philo_bonus      |
|---------------------|---------------------|------------------|
| Concurrencia        | Threads             | Procesos         |
| Sincronización      | Mutex               | Semáforos        |
| Monitor             | Global              | Por proceso      |
| Control muerte      | Variable compartida | `exit()`         |
| Limpieza            | `pthread_join`      | `kill + waitpid` |
