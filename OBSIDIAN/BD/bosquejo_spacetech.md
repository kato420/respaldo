# Bosquejo y Esquema del Proyecto: SpaceTech

## 1. Índice del Proyecto y Guía de Trabajo (Estructura Completa)

Tomando como referencia exacta la estructura del proyecto modelo (`bdInforme`), nuestro proyecto se estructurará de la siguiente manera. Aquí defino las **instrucciones** de cómo atacaremos cada punto.

*   **1. Requisitos**
    *   **1.1. Introducción:** *Instrucción:* Redactar el contexto general del sector espacial comercial y el crecimiento de las constelaciones de satélites en Órbita Baja (LEO).
    *   **1.2. Descripción general de la empresa:** *Instrucción:* Definir "SpaceTech" como un operador satelital centralizado con áreas de monitoreo orbital, control de vuelo y estaciones terrenas.
    *   **1.3. Necesidad / usos de la base de datos:** *Instrucción:* Explicar la problemática central: la imposibilidad de cruzar datos de telemetría en tiempo real con las alertas de basura espacial.
    *   **1.4. ¿Cómo resuelve el problema hoy?**
        *   *1.4.1. Cómo se almacenan los datos hoy:* *Instrucción:* Describir un escenario ineficiente (Excels desconectados o logs de texto separados por cada estación).
        *   *1.4.2. Flujo de datos:* *Instrucción:* Describir la latencia actual y cómo la pérdida de trazabilidad impide predecir colisiones a tiempo.
    *   **1.5. Descripción detallada del sistema**
        *   *1.5.1. Objetos de información actuales:* *Instrucción:* Mapear los registros en papel o Excel que serán migrados.
        *   *1.5.2. Características esperadas:* *Instrucción:* Alta disponibilidad, procesamiento eficiente de altos volúmenes, uso de claves surrogadas.
        *   *1.5.3. Tipos de usuarios:* *Instrucción:* Administrador, Ingeniero de Vuelo, Operador de Estación Terrena, Analista de Seguridad.
        *   *1.5.4. Tipos de consulta (Q1-Q4):* *Instrucción:* Plantear preguntas complejas de negocio (ej. riesgo inminente, satélites con batería crítica).
        *   *1.5.5. Tamaño estimado de la base de datos:* *Instrucción:* Proyectar el tamaño (bytes), calculando el peso gigantesco de la tabla `Telemetria` (millones de filas) versus tablas de catálogo.
    *   **1.6. Objetivos del proyecto:** *Instrucción:* Definir metas técnicas como centralizar la información y unificar el rastreo orbital.
    *   **1.7. Referencias:** *Instrucción:* Proveer referencias de manuales, estándares espaciales o empresas similares.
    *   **1.8. Eventualidades**
        *   *1.8.1. Problemas que pudieran encontrarse:* *Instrucción:* Manejo de "zonas muertas" de señal (latencia en recepción de telemetría).
        *   *1.8.2. Límites y alcances:* *Instrucción:* Aclarar qué queda fuera de la BD (ej. procesamiento del *payload* o imágenes del satélite, contabilidad financiera).

*   **2. Modelo Entidad-Relación**
    *   *2.1. Reglas semánticas:* Detalle narrativo de cada entidad.
    *   *2.2. Modelo Entidad-Relación:* El diagrama gráfico.
    *   *2.3. Especificaciones y consideraciones:* Decisiones de diseño justificadas.
    *   **Instrucción de Trabajo:** Como acordamos, **dejaremos este punto en pausa** hasta que el Modelo Relacional esté sólido. El ER se dibujará luego de que tengamos las tablas claras.

*   **3. Modelo Relacional**
    *   *3.1. Modelo Relacional, 3.2 Transformaciones y 3.3 Diccionario de Datos:* Tablas, PK, FK y tipos de dato exactos.
    *   **Instrucción de Trabajo:** Lo definimos en borrador a continuación para tener las bases técnicas listas.

---

## 2. Borrador de Requisitos (El Planteamiento en Bruto a Desarrollar)

### Contexto y Problema (Puntos 1.1 al 1.4)
**SpaceTech** gestiona una inmensa constelación de satélites LEO (Low Earth Orbit). Actualmente, cada estación terrena guarda la **Telemetría** recibida (voltaje, temperatura, posición) en silos de datos (archivos CSV aislados). Al mismo tiempo, la información de radares sobre **Basura Espacial** llega en un sistema totalmente diferente. 
Como el flujo actual es desarticulado y manual, existe una alta latencia. Esto es inaceptable, ya que no permite cruzar trayectorias a tiempo para predecir colisiones inminentes, arriesgando activos millonarios.

### Solución y Sistema (Puntos 1.5 al 1.7)
La nueva base de datos PostgreSQL centralizará todo. Cada vez que un satélite pase sobre una **Estación Terrena** (Contacto), inyectará su telemetría directamente a la base de datos.
*   **Usuarios:** Administrador (gestiona satélites), Ingeniero de Vuelo (monitorea salud/telemetría), Operador de Estación (coordina conexiones), Analista de Seguridad (evalúa colisiones).
*   **Consultas Clave (Q1-Q4):** Buscaremos optimizar consultas críticas como: "Top 5 satélites con mayor probabilidad de colisión en las próximas 24 horas", o "Fallas recurrentes de batería por órbita".
*   **Crecimiento:** La tabla de *Telemetría* crecerá por millones de registros semanales, mientras que tablas como *Órbita* o *Agencia* serán estáticas.

### Límites y Eventualidades (Punto 1.8)
*   **Problema anticipado:** La pérdida de paquetes. Si un satélite pierde conexión o atraviesa una anomalía geomagnética, habrá huecos en los timestamps de telemetría.
*   **Límites:** La base de datos guardará **telemetría operativa** (salud del satélite) y datos de control de vuelo. **NO** almacenará la "carga útil" o payload (por ejemplo, petabytes de imágenes fotográficas o tráfico de internet de clientes). Tampoco verá temas de contabilidad, planillas o facturación de la empresa.

---

## 3. Borrador del Modelo Relacional (Esquema de Tablas)

A continuación, planteamos la estructura lógica. Se proponen **9 tablas** conectadas, logrando las relaciones necesarias para el sistema.

### 1. Agencia
Representa la corporación u organismo dueño de los satélites.
*   **PK:** `ID_Agencia`
*   **Atributos:** `Nombre`, `Pais_Sede`.
*   **Relación:** 1 a N con *Constelacion*. (1 agencia gestiona múltiples misiones/constelaciones).

### 2. Constelacion
Agrupación de satélites con una misión conjunta (ej. "SpaceTech EarthObservation").
*   **PK:** `ID_Constelacion`
*   **FK:** `ID_Agencia` (Referencia a Agencia)
*   **Atributos:** `Nombre_Mision`, `Proposito`.
*   **Relación:** 1 a N con *Satelite*.

### 3. Orbita
Los parámetros orbitales estandarizados.
*   **PK:** `ID_Orbita`
*   **Atributos:** `Apogeo_km`, `Perigeo_km`, `Inclinacion_grados`.
*   **Relación:** 1 a N con *Satelite*. (Varios satélites pueden compartir la misma órbita objetivo).

### 4. Satelite
El activo principal físico en el espacio.
*   **PK:** `ID_Satelite`
*   **FK:** `ID_Constelacion`, `ID_Orbita`
*   **Atributos:** `Nombre_Identificador`, `Masa_kg`, `Fecha_Lanzamiento`, `Estado_Actual` (Activo, Mantenimiento, Destruido).
*   **Relaciones:** 1 a N con *Telemetria*, 1 a N con *Contacto_Estacion*, 1 a N con *Evento_Colision*.

### 5. Estacion_Terrena
Instalaciones en tierra con antenas parabólicas.
*   **PK:** `ID_Estacion`
*   **Atributos:** `Nombre_Ubicacion`, `Latitud`, `Longitud`, `Banda_Frecuencia`.
*   **Relación:** N a M con *Satelite*, resuelta a través de la tabla intermedia *Contacto_Estacion*.

### 6. Contacto_Estacion (Tabla Intermedia de Operación)
Registro de la ventana de tiempo en la que un satélite descarga datos a una antena.
*   **PK:** `ID_Contacto`
*   **FK:** `ID_Satelite`, `ID_Estacion`
*   **Atributos:** `Fecha_Hora_Inicio`, `Fecha_Hora_Fin`, `Calidad_Senal_dB`.
*   **Relación:** 1 estación atiende a N satélites a lo largo del día. 1 satélite se conecta a N estaciones a lo largo de su órbita. Esta tabla resuelve la relación N a M original.

### 7. Telemetria
Signos vitales de cada satélite (la tabla de mayor volumen y frecuencia de inserción).
*   **PK:** `ID_Telemetria`
*   **FK:** `ID_Satelite`
*   **Atributos:** `Timestamp_Lectura`, `Temperatura_C`, `Bateria_Pct`, `Altitud_Real_km`.
*   **Relación:** N a 1 con *Satelite*. (Millones de registros pertenecen a 1 satélite).

### 8. Basura_Espacial
Objetos inertes detectados por radar (restos de cohetes, satélites muertos).
*   **PK:** `ID_Basura`
*   **Atributos:** `Descripcion_Origen`, `Tamaño_mts`, `Nivel_Riesgo`.
*   **Relación:** N a M con *Satelite* (por el riesgo de choque), resuelta a través de *Evento_Colision*.

### 9. Evento_Colision (Tabla Intermedia de Alerta)
Cruce de trayectoria entre un activo y basura espacial, generando una alerta formal.
*   **PK:** `ID_Evento`
*   **FK:** `ID_Satelite`, `ID_Basura`
*   **Atributos:** `Timestamp_Estimado_Impacto`, `Probabilidad_Choque_Pct`, `Distancia_Minima_mts`, `Estado_Alerta` (Emitida, Maniobra Ejecutada, Falsa Alarma).
*   **Relación:** Vincula exactamente 1 Satélite y 1 Basura en un evento (resolviendo la relación N a M).
