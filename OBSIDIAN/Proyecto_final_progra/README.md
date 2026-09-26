# Plataforma de Streaming - Proyecto Programación III (2026-2)

## Integrantes

* Alexis Huamán Yay
* Avelina Luque Jayttara
* Castro Gomez Sandra Carolina
* Miguel Angel Flores Cardenas

---

## Avance de Proyecto (Presentación Semana 8)

Para esta primera entrega, nos hemos centrado en la **estabilidad de la interfaz**, la **integridad de los datos** y en el diseño arquitectónico de los algoritmos que respaldarán el sistema en su versión final.

### 1. Preprocesamiento de Datos (Parser CSV Manual)

El mayor desafío con el dataset `wiki_movie_plots_deduped.csv` (78 MB, ~35,000 registros) fue la inconsistencia estructural: los campos de "Sinopsis" (`Plot`) contienen comas, comillas anidadas y **saltos de línea internos** que corrompen la lectura tradicional línea por línea (`std::getline`).

**Solución Implementada (`LectorCSV.h`):**
Hemos desarrollado un *parser* o máquina de estados desde cero, sin dependencias externas.

* El lector lleva un registro del estado utilizando un flag booleano (`en_comillas`).
* Si se encuentra un salto de línea pero el estado de comillas sigue abierto, el algoritmo asume que el texto de la sinopsis continúa. En ese caso, inserta un salto de línea manual (`\n`) y concatena la siguiente línea del archivo antes de intentar separar las columnas.
* Este enfoque garantiza una extracción perfecta de los metadatos y crea los objetos `Pelicula` de forma segura.

### 2. Interfaz en Consola y Funcionalidad Básica

Implementamos un menú interactivo a prueba de fallos (*crash-proof*). Toda la entrada se lee como `std::string` para evitar bucles infinitos si el usuario ingresa caracteres inválidos.

* **Búsqueda (Fase 1):** Actualmente implementada de forma secuencial iterativa para asegurar estabilidad en la demo de hoy, devolviendo resultados coincidentes tanto en título como en sinopsis.
* **Paginación:** Los resultados se presentan en bloques de 5 en 5, permitiendo al usuario avanzar dinámicamente o seleccionar una obra.
* **Interacción:** El usuario puede dar *Like* o añadir a *Ver más tarde*. La Opción 2 del menú principal recupera e imprime esta última lista.

---

## Arquitectura y Algoritmos (Diseño Teórico)

Para cumplir con los requisitos de eficiencia, búsqueda por sub-palabras y ordenamiento, el equipo ha documentado la siguiente arquitectura que será el motor de la versión final (Semana 16):

### Estructura de Datos: Inverted Suffix Trie

Construir un Suffix Tree ingenuo sobre 78 MB de texto requeriría demasiada memoria RAM. Por ello, la propuesta técnica elegida es el **Trie de Sufijos sobre un Índice Invertido de Vocabulario**:

1. Extraeremos todas las palabras únicas del dataset (vocabulario).
2. Insertaremos en un `Trie<Payload>` genérico todos los **sufijos** de cada palabra única.
3. Al buscar una sub-palabra (ej. *"bar"*), el árbol descenderá por los nodos en tiempo $O(k)$ y recolectará todas las palabras que la contienen (ej. *"barco"*, *"embarcación"*), uniendo finalmente las películas asociadas a esos términos.

### Algoritmo de Ranking y Relevancia

Los resultados no se mostrarán aleatoriamente. Implementaremos una función de puntuación que pondera:

* Coincidencia en título (Mayor peso).
* Exactitud de la coincidencia (Palabra completa vs. sub-cadena).
* Frecuencia amortiguada (TF) en la sinopsis.
* Año de estreno (factor de desempate).

### Algoritmo de Recomendación

Al abrir la plataforma, se recomendarán títulos nuevos basándose en las películas que tienen *Like*, utilizando el **Coeficiente de Similitud de Jaccard** para comparar la superposición de géneros, y bonificaciones por directores y actores compartidos.

---

## Cómo compilar y ejecutar

El proyecto utiliza CMake y Ninja para una compilación rápida. Contamos con un script automatizado para facilitar la ejecución.

**Requisitos:**

* C++20
* CMake (>= 3.20)
* Ninja

**Ejecución:**

```bash
# Otorgar permisos al script si es necesario
chmod +x run

# Compilar y ejecutar
./run
```

[VIDEO PRESENTACION I](https://youtu.be/Cc5GwMqcGD8)
