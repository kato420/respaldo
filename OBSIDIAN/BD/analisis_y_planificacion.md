# Análisis y Planificación: Proyecto de Base de Datos (SpaceTech)

## 1. Análisis de la Estructura del Proyecto Modelo (`bdInforme`)

El proyecto modelo está estructurado de manera profesional utilizando **LaTeX**, con un enfoque modular. Esto significa que el documento no está escrito en un solo bloque enorme, sino dividido en archivos para cada sección, los cuales son unidos por un archivo principal. 

Los archivos detectados y su función son:
*   `main.tex`: Es el archivo maestro. Configura el documento (tipo *report*, carga de paquetes de idioma, geometría, tablas, etc.) y llama al resto de los archivos mediante el comando `\input{}`.
*   `caratula.tex`: Contiene la portada del informe.
*   `indice.tex`: Genera la tabla de contenidos.
*   `requisitos.tex`: Capítulo 1. Contiene la descripción del negocio, el problema, los objetos de información, tipos de usuarios, preguntas de negocio (consultas) y la estimación del tamaño de la base de datos (tablas de crecimiento de bytes).
*   `modelo_ER.tex`: Capítulo 2. Detalla rigurosamente las reglas semánticas de cada entidad agrupadas por módulos, incluye el diagrama Entidad-Relación y las consideraciones de diseño.
*   `modelo_relacional.tex`: Capítulo 3. (Asumido por la estructura). Contiene el paso del E/R a tablas (normalización), especificación de claves primarias (PK) y foráneas (FK), y el diccionario de datos.

## 2. Análisis de los Requerimientos del PDF para el Nuevo Proyecto

Basado en las instrucciones del documento `Proyecto Final-1.pdf`:
*   **Fase Actual**: Se debe completar el **Hito 1**, que incluye: 
    1. Descripción de Requerimientos.
    2. Modelo Entidad/Relación (E/R).
    3. Modelo Relacional.
*   **Tópico Asignado**: Opción 1: **Gestión de Constelaciones y Satélites (SpaceTech)**.
*   **Conceptos Obligatorios a incluir**: satélites, órbitas, telemetría, basura espacial, estaciones terrenas y eventos de conjunción/colisión.
*   **Dimensión exigida**: El diagrama E/R debe tener al menos 5 entidades y un número similar de relaciones (nosotros apuntaremos a **mínimo 8 tablas** para tener un modelo robusto y "razonable").

---

## 3. Instrucciones y Guía para la Construcción del Nuevo Proyecto

A continuación, se establecen las instrucciones paso a paso para redactar la información que posteriormente colocaremos en los archivos LaTeX del nuevo proyecto.

### A. Preparación del Entorno LaTeX (`main.tex`, `caratula.tex`, `indice.tex`)
*   Se replicará la estructura base del proyecto modelo. 
*   **Instrucción**: Mantendremos los paquetes esenciales de LaTeX (`graphicx`, `geometry`, `hyperref`, `tabularx`, `booktabs`) para soportar tablas de estimación de tamaño y diagramas.

### B. Capítulo 1: Requisitos (`requisitos.tex`)
En este archivo deberemos estructurar la narrativa del negocio "SpaceTech".
*   **Introducción**: Redactar el contexto de una empresa aeroespacial que monitorea cientos de satélites (como Starlink).
*   **Problema actual**: Explicar cómo la gestión en hojas de cálculo separadas causa pérdida de telemetría y riesgos de colisión espacial.
*   **Tipos de Usuario**: Definiremos perfiles como: Administrador de Red, Ingeniero de Vuelo, Operador de Estación Terrena e Investigador Astronómico.
*   **Tipos de Consulta (Q1-Q4)**: Definiremos preguntas clave. Ejemplo: *¿Cuáles son los satélites con mayor probabilidad de colisión con basura espacial en las próximas 48 horas?*
*   **Tamaño de Base de Datos**: Crearemos tablas estimando el peso en bytes, considerando que la **Telemetría** crecerá por millones de registros diariamente.

### C. Capítulo 2: Modelo Entidad-Relación (`modelo_ER.tex`)
Aquí definiremos nuestras **8 entidades principales**.
*   **Propuesta de Entidades**:
    1.  **Agencia\_Propietaria**: Empresa u organización dueña de los activos.
    2.  **Constelación**: Grupo de satélites bajo un mismo propósito (Ej. Internet de banda ancha).
    3.  **Satélite**: El activo principal (Atributos: ID, nombre, masa, estado, fecha de lanzamiento).
    4.  **Órbita**: Parámetros orbitales (apogeo, perigeo, inclinación).
    5.  **Estación\_Terrena**: Instalaciones en Tierra que reciben los datos.
    6.  **Telemetría**: Entidad de alto volumen que registra signos vitales del satélite (temperatura, batería, posición) en un timestamp determinado.
    7.  **Basura\_Espacial**: Objetos inactivos rastreados por radar.
    8.  **Evento\_Colisión (Conjunción)**: Registro de riesgo entre un satélite y basura espacial, alertando proximidad.
*   **Instrucción**: Para el documento, se redactarán las "Reglas Semánticas" de cada una de estas entidades, explicando por qué se eligieron sus claves (preferiblemente llaves surrogadas ID autoincrementales, igual que en el modelo). Luego generaremos el diagrama E/R.

### D. Capítulo 3: Modelo Relacional (`modelo_relacional.tex`)
*   **Instrucción**: Convertiremos las entidades en un esquema de tablas. Detallaremos cómo las llaves primarias (PK) se propagan como foráneas (FK). Por ejemplo, `ID_Satelite` pasará como FK a la tabla `Telemetría`.
*   Construiremos el diccionario de datos detallando tipos de datos (`VARCHAR`, `TIMESTAMP`, `DECIMAL`, `INTEGER`).

---
**Siguiente Paso:** Una vez revises esta estructura y estemos de acuerdo, procederemos a crear la estructura de carpetas y escribir el contenido del primer archivo (`requisitos.tex`) enfocándonos en la narrativa de SpaceTech.
