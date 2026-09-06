# Presentacioón FreeRTOS


## Objetivo del experimento

Evidenciar la diferencia entre:

- Superloop con `delay()`.
- Ejecución de un programa con `millis()`.

Etender que cuando una tarea consume demasiado tiempo, puede retrasar a todas las demás,incluso teniendo un enfoque de estados finitos.

FreeRTOS permite separar estas actividades en tareas independientes y asignar prioridades para proteger aquellas que tienen mayores restricciones temporales.



## Plataforma utilizada

### Hardware

- ESP32-WROOM-32
- Pantalla OLED I2C 
- ONBOARD LED
- UART principal
- Segunda UART del ESP32

### Software

- PlatformIO
- Arduino Framework
- Librerías especializadas para pantalla OLED

---

# Estructura del experimento

El repositorio contiene tres implementaciones principales.

## 1. Implementación con `millis()` sin sobrecarga

Esta primera versión ejecuta diferentes actividades periódicas utilizando `millis()`.

Entre las tareas se encuentran:

- Actualización de un LED.
- Actualización de una pantalla OLED.
- Envío periódico de información por el puerto Serial (UART1).

En este escenario, la carga del sistema es suficientemente baja para que todas las tareas puedan ejecutarse aproximadamente dentro de los periodos establecidos.

Esta implementación sirve como punto de referencia para observar que `millis()` puede ser una solución adecuada cuando el número de tareas y el tiempo de ejecución de cada una son pequeños.

## 2. Implementación con `millis()` bajo sobrecarga

La segunda versión mantiene la misma estructura basada en `millis()`, pero introduce una tarea adicional que genera una carga considerable sobre el sistema mediante la segunda UART del ESP32.

Esta tarea intenta transmitir una cantidad de datos muy superior a la que la UART puede procesar dentro del periodo solicitado.

Como consecuencia, una parte importante del tiempo de ejecución queda ocupada por esta tarea.

Esto provoca que las demás actividades empiecen a ejecutarse fuera de sus tiempos esperados.

Entre los efectos observables se encuentran:

- Retrasos en el parpadeo del LED.
- Actualizaciones irregulares de la OLED.
- Variaciones en los tiempos de envío por Serial.
- Incumplimiento de los periodos definidos inicialmente.

Este experimento permite demostrar una limitación importante de una arquitectura basada únicamente en un `loop()`:

> Aunque se utilice `millis()` para controlar los tiempos, todas las actividades siguen dependiendo del mismo flujo de ejecución.

**Si una tarea tarda demasiado, el resto debe esperar.**


## 3. Implementación con FreeRTOS

La tercera versión implementa las mismas actividades utilizando **tareas independientes de FreeRTOS**.

Cada actividad se ejecuta como una tarea separada y cuenta con:

- Su propio periodo de ejecución.
- Su propio contexto.
- Una prioridad asignada.
- Tiempo de CPU gestionado por el scheduler de FreeRTOS.

La tarea que genera la mayor carga se mantiene deliberadamente en el sistema, pero se configura con una prioridad menor.

Las tareas más importantes, como el control del LED o las actividades que deben cumplir periodos más estrictos, reciben prioridades superiores.

De esta manera, el scheduler puede interrumpir temporalmente una tarea de menor prioridad para ejecutar otra más importante.

---

# Comparación

| Característica | `millis()` | FreeRTOS |
|---|---|---|
| Organización de tareas periódicas | Sí | Sí |
| Prioridades | No | Sí |
| Tareas independientes | No | Sí |
| Manejo de tareas bloqueantes | No | Mejor aislamiento |
| Complejidad | Baja | Mayor |
| Adecuado para sistemas simples | Sí | Sí, aunque puede ser innecesario |



