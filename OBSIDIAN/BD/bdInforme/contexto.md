**Objetivo:**
Generar el código LaTeX completo para el archivo `modelo_relacional.tex`, correspondiente al Capítulo 3 del documento. Debes transcribir el texto y las tablas exactas que te proporciono al final, respetando estrictamente la jerarquía y el formato.

**Estructura Jerárquica y Formato General:**

- Inicia el documento directamente con `\chapter{Modelo Relacional}`.
- Utiliza `\section{}` para "3.1. Modelo Relacional", "3.2. Especificaciones de transformación" y "3.3. Diccionario de datos".
- Utiliza `\subsection{}` para los ítems de la sección 3.2 (ej. "3.2.1. Entidades").
- **Listas:** Transforma cada símbolo "■" en un ítem dentro de un entorno `\begin{itemize}`.

**Instrucciones Críticas para las Tablas (Sección 3.3 - Diccionario de datos):**

- Esta sección contiene 26 tablas.
- Usa el entorno `\begin{table}[H] \centering` para cada una.
- Utiliza un formato tabular que permita salto de línea en la última columna, ya que las descripciones son largas. Te sugiero usar `\begin{tabular}{|l|l|c|c|p{5cm}|}`.
- Añade su respectivo `\caption{Tabla [Nombre]}` debajo de cada tabla, tal como se indica en el texto fuente.
- Elimina cualquier etiqueta `` si la encuentras.

---

**TEXTO FUENTE PARA TRANSCRIBIR:**

3.1. Modelo Relacional
A continuación se presentan los esquemas relacionales finales del sistema. Las llaves primarias se indican subrayadas y las llaves foráneas con la etiqueta (FK). Las llaves únicas alternativas se marcan con (UK).
Nota sobre las relaciones: Todas las relaciones del modelo son de cardinalidad 1:N o 1:1, por lo que ninguna genera una tabla intermedia adicional; en su lugar, la llave foránea se inyecta en el lado "N" o en la entidad dependiente. Las entidades transaccionales (Resultado_Diagnóstico, Insumo_Utilizado, Procedimiento_Aplicado, Receta_Médica y Detalle_Factura) resuelven asociaciones semánticamente N:M entre entidades fuertes, pero se modelan como entidades fuertes con PK surrogada y no como tablas de intersección puras.

Módulo 1 Jerarquía de Personas
■ Persona (ID_Persona, DNI (UK), Nombres, Apellidos, Teléfono, Email (UK))
■ Cliente (ID_Persona (FK), Dirección_Principal, Contacto_Emergencia)
■ Empleado (ID_Persona (FK), Código_Empleado (UK), Fecha_Contratación, Salario)
■ Veterinario (ID_Persona (FK), CMPV (UK), Especialidad)
■ Personal_Apoyo (ID_Persona (FK), Rol, Licencia_Conducir)
Relaciones absorbidas como FK no generan tabla propia:
■ Persona -> Cliente (1:1): ID_Persona es PK y FK en Cliente.
■ Persona -> Empleado (1:1): ID_Persona es PK y FK en Empleado.
■ Empleado -> Veterinario (1:1): ID_Persona es PK y FK en Veterinario.
■ Empleado -> Personal_Apoyo (1:1): ID_Persona es PK y FK en Personal_Apoyo.

Módulo 2 Pacientes (Core Biológico)
■ Especie (ID_Especie, Nombre_Especie (UK))
■ Raza (ID_Raza, Nombre_Raza, ID_Especie (FK))
■ Mascota (ID_Mascota, Nombre, Fecha_Nacimiento, Sexo, ID_Raza (FK), ID_Cliente (FK))
■ Historial_Médico (ID_Historial, ID_Mascota (FK, UK), Fecha_Creación, Grupo_Sanguíneo, Alergias_Conocidas)
Relaciones absorbidas como FK no generan tabla propia:
■ Especie -> Raza Clasifica (1:N): ID_Especie como FK en Raza.
■ Cliente -> Mascota Posee (1:N): ID_Cliente como FK en Mascota.
■ Mascota -> Historial Médico Tiene (1:1): ID_Mascota como FK+UK en Historial_Médico.

Módulo 3 Catálogos e Inventario Especializado
■ Item_Catálogo (ID_Item, Nombre, Precio_Base, Tipo_Item)
■ Servicio (ID_Item (FK), Requiere_Veterinario, Tiempo_Estimado_Min)
■ Artículo_Petshop (ID_Item (FK), Marca, Categoría, Stock_General)
■ Medicamento (ID_Item (FK), Principio_Activo, Concentración, Presentación, Requiere_Receta)
■ Lote_Inventario (ID_Lote, ID_Medicamento (FK), Fecha_Caducidad, Cantidad_Inicial, Stock_Actual)
Relaciones absorbidas como FK no generan tabla propia:
■ Item Catálogo -> Servicio (1:1 herencia JOINED): ID_Item es PK y FK en Servicio.
■ Item_Catálogo -> Artículo_Petshop (1:1 herencia JOINED): ID_Item es PK y FK en Artículo_Petshop.
■ Item_Catálogo -> Medicamento (1:1 herencia JOINED): ID_Item es PK y FK en Medicamento.
■ Medicamento -> Lote_Inventario Almacena (1:N): ID_Medicamento como FK en Lote_Inventario.

Módulo 4 Flujo Médico (Corazón Clínico)
■ Cita (ID_Cita, Fecha, Hora, Motivo, Estado, ID_Cliente (FK), ID_Mascota (FK), Código_Empleado (FK))
■ Atención_Clínica (ID_Atención, ID_Historial (FK), Código_Empleado (FK), Fecha_Hora, Motivo_Real, Peso_Kg, Temp_C, Frecuencia_Cardíaca, Anamnesis)
■ Enfermedad_Diagnóstico (ID_Enfermedad, Código_CIE (UK), Nombre_Enfermedad)
■ Resultado_Diagnóstico (ID_Resultado, ID_Atención (FK), ID_Enfermedad (FK), Tipo, Observaciones)
■ Procedimiento_Aplicado (ID_Procedimiento, ID_Atención (FK), ID_Item (FK), Resultados_Notas)
■ Insumo_Utilizado (ID_Insumo_Uso, ID_Atención (FK), ID_Lote (FK), Cantidad_Usada)
■ Receta_Médica (ID_Receta, ID_Atención (FK), ID_Medicamento (FK), Dosis_Frecuencia, Duración_Días)
Relaciones absorbidas como FK no generan tabla propia:
■ Cliente/Mascota/Empleado → Cita Involucra (1:N desde cada uno): FKs en Cita.
■ Historial Médico -> Atención Clínica Registra (1:N): ID_Historial como FK en Atención Clínica.
■ Veterinario -> Atención Clínica Realiza (1:N): Código_Empleado como FK en Atención_Clínica.
Entidades que resuelven asociaciones N:M tienen tabla propia por atributos propios:
■ Resultado_Diagnóstico: resuelve Atención Clínica -> Enfermedad_Diagnóstico (con atributo Tipo).
■ Procedimiento_Aplicado: resuelve Atención_Clínica -> Servicio (con atributo Resultados_Notas).
■ Insumo_Utilizado: resuelve Atención_Clínica -> Lote_Inventario (con atributo Cantidad_Usada).
■ Receta_Médica: resuelve Atención_Clínica -> Medicamento (con atributos Dosis_Frecuencia, Duración Días).

Módulo 5 Operativo Anexo
■ Registro_Estancia (ID_Estancia, ID_Mascota (FK), Tipo, Fecha_Ingreso, Fecha_Salida, Nro_Jaula, Instrucciones_Cuidado)
■ Transporte_Logística (ID_Transporte, ID_Cita (FK), Código_Empleado (FK), Tipo_Ruta, Dirección_Destino, Estado)
Relaciones absorbidas como FK no generan tabla propia:
■ Mascota -> Registro_Estancia Se hospeda (1:N): ID_Mascota como FK en Registro_Estancia.
■ Cita -> Transporte_Logística Requiere (1:1): ID_Cita como FK en Transporte_Logística.

Módulo 6 Facturación y Finanzas
■ Factura (ID_Factura, Fecha_Emisión, Subtotal, IGV, Total, ID Cliente (FK), ID_Atención (FK), ID Cita (FK))
■ Detalle_Factura (ID_Detalle, ID_Factura (FK), ID_Item (FK), ID_Lote (FK), ID_Estancia (FK), Cantidad, Precio_Unitario, Subtotal_Linea)
■ Pago (ID_Pago, ID_Factura (FK), Fecha_Pago, Monto_Abonado, Método_Pago)
Relaciones absorbidas como FK no generan tabla propia:
■ Cliente → Factura Paga (1:N): ID_Cliente como FK en Factura.
■ Atención/Cita -> Factura Origina (1:1 opcional, mutuamente excluyente): FKs nullables con CHECK en Factura.
■ Factura -> Pago Abona (1:N): ID_Factura como FK en Pago.
Entidad que resuelve asociación N:M tiene tabla propia por atributos propios:
■ Detalle_Factura: resuelve Factura -> Item_Catálogo (con atributos Cantidad, Precio_Unitario, Subtotal_Línea, y FKs opcionales a Lote y Estancia).

3.2. Especificaciones de transformación
A continuación se describen las decisiones tomadas para transformar cada elemento del modelo conceptual Entidad-Relación al modelo relacional físico en PostgreSQL.

3.2.1. Entidades
Para transformar las entidades fuertes del modelo se han tenido en cuenta las siguientes especificaciones:
■ Persona: Su llave primaria es ID_Persona, una clave surrogada autoincremenal de tipo INT. El DNI actúa como clave única alternativa (UK) dado que es un identificador de negocio sujeto a correcciones. Tiene como atributos los nombres, apellidos, teléfono y correo electrónico, siendo el email también UNIQUE.
■ Especie: Su llave primaria es ID_Especie (surrogada). El atributo Nombre_Especie es UNIQUE y NOT NULL para garantizar que no se registren duplicados de clasificaciones biológicas (ej. dos registros de "Canino").
■ Raza: Su llave primaria es ID_Raza (surrogada). Tiene como atributos Nombre_Raza y la llave foránea ID_Especie. Se optó por PK surrogada en lugar de llave compuesta (Nombre_Raza, ID_Especie) para simplificar los JOINS.
■ Mascota: Su llave primaria es ID_Mascota (surrogada). Tiene como atributos el nombre, fecha de nacimiento (nullable), y sexo. Incluye las llaves foráneas ID_Raza e ID_Cliente.
■ Historial_Médico: Su llave primaria es ID_Historial (surrogada). El atributo ID_Mascota actúa como llave foránea y a la vez como clave única (FK, UK), lo que garantiza la relación 1:1 con Mascota a nivel de esquema. Almacena el grupo sanguíneo y alergias conocidas del paciente, ambos nullable.
■ Item_Catálogo: Su llave primaria es ID_Item (surrogada). Tiene como atributos el nombre del ítem, el precio base y un discriminador Tipo_Item que indica si es un servicio, artículo de petshop o medicamento. Es la superclase de la jerarquía de catálogo.
■ Lote_Inventario: Su llave primaria es ID_Lote (surrogada). Almacena la fecha de caducidad, la cantidad inicial del lote y el stock actual. La FK ID_Medicamento vincula el lote a su medicamento genérico.
■ Cita: Su llave primaria es ID_Cita (surrogada). Tiene como atributos la fecha, hora, motivo de la visita y el estado actual. Las llaves foráneas ID_Cliente, ID_Mascota y Código_Empleado son todas NOT NULL.
■ Atención_Clínica: Su llave primaria es ID_Atención (surrogada). Registra la fecha y hora del acto médico, el motivo real de la consulta y los signos vitales del triaje (peso, temperatura y frecuencia cardíaca), todos nullable. Las llaves foráneas ID_Historial y Código_Empleado son NOT NULL.
■ Enfermedad_Diagnóstico: Su llave primaria es ID_Enfermedad (surrogada). El Código_CIE actúa como clave única alternativa para estandarizar la nomenclatura médica. El Nombre Enfermedad es NOT NULL.
■ Registro_Estancia: Su llave primaria es ID_Estancia (surrogada). Almacena el tipo de estadía, la fecha de ingreso, la fecha de salida (nullable), el número de jaula asignado y las instrucciones de cuidado (nullable). La FK ID_Mascota es NOT NULL.
■ Transporte_Logística: Su llave primaria es ID_Transporte (surrogada). Tiene como atributos el tipo de ruta, la dirección de destino y el estado del servicio. El campo Estado acepta los valores controlados Pendiente, En curso, Completado y Cancelado (CHECK constraint). Las llaves foráneas ID_Cita y Código_Empleado son NOT NULL.
■ Factura: Su llave primaria es ID_Factura (surrogada). Almacena la fecha de emisión, el subtotal, el IGV calculado y el total a pagar. La FK ID_Cliente es NOT NULL; las FKS ID_Atención e ID_Cita son nullables y mutuamente excluyentes (CHECK constraint).
■ Pago: Su llave primaria es ID_Pago (surrogada). Registra la fecha del pago, el monto abonado y el método de pago utilizado. La FK ID_Factura es NOT NULL, habilitando pagos fraccionados (múltiples pagos por factura).

3.2.2. Entidades débiles
En el modelo conceptual original no se identificaron entidades débiles en sentido estricto (es decir, entidades cuya existencia y unicidad dependan completamente de una entidad propietaria mediante una llave parcial). Todas las entidades que en un diseño tradicional podrían haberse modelado como débiles como Atención_Clínica respecto a Historial_Médico, o Detalle_Factura respecto a Factura fueron convertidas intencionalmente en entidades fuertes con PK surrogada autoincremenal. Esta decisión de diseño elimina la necesidad de llaves compuestas derivadas de la entidad propietaria, simplifica las operaciones de JOIN y mejora el rendimiento transaccional en tablas con alto volumen de inserciones.

3.2.3. Entidades superclase / subclases
El modelo contempla dos jerarquías de herencia implementadas mediante el patrón Table Per Subclass (JOINED) de PostgreSQL:
■ Jerarquía de Personas: La superclase Persona se divide en las subclases Cliente y Empleado. A su vez, Empleado se subdivide en Veterinario y Personal_Apoyo. En todos los casos, la PK de la subclase es ID_Persona, que actúa simultáneamente como FK hacia la tabla padre. No se genera una nueva clave en las subclases. Se permite el solapamiento entre Cliente y Empleado (un empleado puede también ser cliente de la clínica). La cobertura es total para Empleado: todo empleado debe ser Veterinario o Personal_Apoyo.
■ Jerarquía de Ítems de Catálogo: La superclase Item_Catálogo se divide en las subclases Servicio, Artículo_Petshop y Medicamento. Siguiendo el mismo patrón JOINED, la PK de cada subclase es ID_Item, que actúa también como FK hacia Item_Catálogo. El atributo Tipo_Item en la superclase actúa como discriminador para identificar la subclase concreta de cada registro. La cobertura es total: todo ítem del catálogo debe pertenecer a exactamente una de las tres subclases.

3.2.4. Relaciones binarias
Para transformar las relaciones binarias del modelo conceptual al esquema relacional se aplicaron las siguientes reglas, en función de la cardinalidad de cada relación:
■ Relaciones 1:1 La llave primaria del lado participante total (o de la entidad dependiente) recibe la FK de la entidad referenciada. En este modelo:
• Mascota -> Historial Médico (Tiene): ID_Mascota se incluye como FK + UK en Historial_Médico. La restricción UNIQUE garantiza que no puedan existir dos historiales para la misma mascota.
• Cita -> Transporte_Logística (Requiere): ID_Cita se incluye como FK en Transporte_Logística, que es el lado de participación total.
• Atención/Cita -> Factura (Origina): Ambas FKs son nullables en Factura y se controlan mediante un CHECK de exclusión mutua.
■ Relaciones 1:N La llave primaria del lado "1" se inyecta como FK en el lado "N". En este modelo todas las relaciones estructurales y de flujo siguen este patrón:
• Especie -> Raza: ID_Especie como FK en Raza.
• Cliente -> Mascota: ID Cliente como FK en Mascota.
• Medicamento -> Lote_Inventario: ID_Medicamento como FK en Lote_Inventario.
• Historial Médico -> Atención_Clínica: ID_Historial como FK en Atención_Clínica.
• Atención Clínica -> Resultado_Diagnóstico, Procedimiento_Aplicado, Insumo_Utilizado, Receta_Médica: ID_Atención como FK en cada tabla transaccional.
• Mascota -> Registro_Estancia: ID_Mascota como FK en Registro_Estancia.
• Cliente -> Factura: ID_Cliente como FK en Factura.
• Factura -> Detalle_Factura: ID_Factura como FK en Detalle_Factura.
• Factura -> Pago: ID_Factura como FK en Pago.
■ Relaciones N:M resueltas como entidades fuertes Dado que todas las asociaciones semánticamente N:M del modelo presentan atributos propios relevantes, fueron modeladas como entidades fuertes con PK surrogada en lugar de tablas de intersección puras. Esto aplica a: Resultado_Diagnóstico, Procedimiento_Aplicado, Insumo_Utilizado, Receta_Médica y Detalle_Factura.

3.2.5. Relaciones ternarias
Para la elaboración del modelo no se consideraron relaciones ternarias. Todas las asociaciones que involucran a tres entidades simultáneamente como la relación Involucra entre Cliente, Mascota y Empleado hacia Cita fueron resueltas incorporando múltiples llaves foráneas directamente en la entidad resultante (Cita), tratándolas como tres relaciones binarias independientes 1:N convergentes. Este enfoque simplifica el esquema y evita la complejidad que conlleva una tabla ternaria pura.

3.3. Diccionario de datos
A continuación se presenta el diccionario de datos del sistema, con una tabla por cada entidad del modelo relacional. Se detallan el nombre de cada campo, su tipo de dato en PostgreSQL, si actúa como llave primaria (PK) y/o foránea (FK), y una descripción funcional del atributo.

Cuadro 3.1: Tabla Persona

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Persona | INT (SERIAL) | X | | Identificador surrogado autoincremenal |
| DNI | VARCHAR(8) | | | Documento Nacional de Identidad (UK) |
| Nombres | VARCHAR(50) | | | Nombres de pila de la persona |
| Apellidos | VARCHAR(50) | | | Apellidos de la persona |
| Teléfono | VARCHAR(15) | | | Número de teléfono de contacto |
| Email | VARCHAR(100) | | | Correo electrónico (UK) |

Cuadro 3.2: Tabla Cliente

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Persona | INT | X | X | FK Persona. Herencia JOINED |
| Dirección_Principal | VARCHAR(150) | | | Dirección fiscal del cliente |
| Contacto_Emergencia | VARCHAR(100) | | | Contacto alternativo (nullable) |

Cuadro 3.3: Tabla Empleado

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Persona | INT | X | X | FK Persona. Herencia JOINED |
| Código_Empleado | VARCHAR(20) | | | Código interno de RRHH (UK) |
| Fecha_Contratación | DATE | | | Fecha de inicio del vínculo laboral |
| Salario | DECIMAL(10,2) | | | Salario base mensual (referencial) |

Cuadro 3.4: Tabla Veterinario

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Persona | INT | X | X | FK Empleado. Herencia JOINED |
| CMPV | VARCHAR(15) | | | Nro. de colegiatura CMPV (UK) |
| Especialidad | VARCHAR(50) | | | Especialidad médica veterinaria |

Cuadro 3.5: Tabla Personal_Apoyo

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Persona | INT | X | X | FK Empleado. Herencia JOINED |
| Rol | VARCHAR(30) | | | Función: groomer, chofer, recepcionista |
| Licencia_Conducir | VARCHAR(20) | | | Nro. licencia de conducir (nullable) |

Cuadro 3.6: Tabla Especie

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Especie | INT (SERIAL) | X | | Identificador surrogado |
| Nombre_Especie | VARCHAR(50) | | | Nombre de la especie (UK) |

Cuadro 3.7: Tabla Raza

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Raza | INT (SERIAL) | X | | Identificador surrogado |
| Nombre_Raza | VARCHAR(50) | | | Nombre de la raza |
| ID_Especie | INT | | X | FK Especie. Clasificación biológica |

Cuadro 3.8: Tabla Mascota

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Mascota | INT (SERIAL) | X | | Identificador surrogado |
| Nombre | VARCHAR(50) | | | Nombre de la mascota |
| Fecha_Nacimiento | DATE | | | Fecha de nacimiento (nullable) |
| Sexo | CHAR(1) | | | Sexo del paciente: M o H |
| ID_Raza | INT | | X | FK Raza |
| ID_Cliente | INT | | X | FK Cliente. Dueño responsable |

Cuadro 3.9: Tabla Historial_Médico

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Historial | INT (SERIAL) | X | | Identificador surrogado |
| ID_Mascota | INT | | X | FK Mascota (UK: relación 1:1) |
| Fecha_Creación | TIMESTAMP | | | Fecha de apertura del expediente |
| Grupo_Sanguíneo | VARCHAR(20) | | | Grupo sanguíneo (nullable) |
| Alergias_Conocidas | TEXT | | | Alergias registradas (nullable) |

Cuadro 3.10: Tabla Item_Catálogo

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Item | INT (SERIAL) | X | | Identificador surrogado |
| Nombre | VARCHAR(100) | | | Nombre del ítem de catálogo |
| Precio_Base | DECIMAL(10,2) | | | Precio unitario base en soles |
| Tipo_Item | VARCHAR(20) | | | Discriminador: Servicio, Articulo, Medicamento |

Cuadro 3.11: Tabla Servicio

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Item | INT | X | X | FK Item_Catálogo. Herencia JOINED |
| Requiere_Veterinario | BOOLEAN | | | ¿Requiere médico habilitado? |
| Tiempo_Estimado_Min | INT | | | Duración estimada en minutos (nullable) |

Cuadro 3.12: Tabla Artículo_Petshop

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Item | INT | X | X | FK Item_Catálogo. Herencia JOINED |
| Marca | VARCHAR(50) | | | Marca comercial (nullable) |
| Categoría | VARCHAR(50) | | | Categoría del artículo |
| Stock_General | INT | | | Unidades disponibles (DEFAULT 0) |

Cuadro 3.13: Tabla Medicamento

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Item | INT | X | X | FK Item_Catálogo. Herencia JOINED |
| Principio_Activo | VARCHAR(100) | | | Compuesto farmacológico principal |
| Concentración | VARCHAR(50) | | | Concentración del principio activo |
| Presentación | VARCHAR(50) | | | Forma farmacéutica (tableta, jarabe, etc.) |
| Requiere_Receta | BOOLEAN | | | ¿Dispensación con receta obligatoria? |

Cuadro 3.14: Tabla Lote_Inventario

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Lote | INT (SERIAL) | X | | Identificador surrogado del lote |
| ID_Medicamento | INT | | X | FK Medicamento. Fármaco del lote |
| Fecha_Caducidad | DATE | | | Fecha de vencimiento del lote |
| Cantidad_Inicial | INT | | | Unidades ingresadas al recibir el lote |
| Stock_Actual | INT | | | Unidades disponibles actualmente |

Cuadro 3.15: Tabla Cita

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Cita | INT (SERIAL) | X | | Identificador surrogado |
| Fecha | DATE | | | Fecha programada de la cita |
| Hora | TIME | | | Hora programada de la cita |
| Motivo | TEXT | | | Razón de la visita declarada por el cliente |
| Estado | VARCHAR(20) | | | Estado: Pendiente, Confirmada, Completada, Cancelada |
| ID_Cliente | INT | | X | FK Cliente. Solicitante de la cita |
| ID_Mascota | INT | | X | FK Mascota. Paciente de la cita |
| Código_Empleado | VARCHAR(20) | | X | FK Empleado (UK). Profesional asignado |

Cuadro 3.16: Tabla Atención_Clínica

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Atención | INT (SERIAL) | X | | Identificador surrogado |
| ID_Historial | INT | | X | FK Historial_Médico |
| Código_Empleado | VARCHAR(20) | | X | FK Empleado (UK). Veterinario responsable |
| Fecha_Hora | TIMESTAMP | | | Fecha y hora del acto médico |
| Motivo_Real | TEXT | | | Motivo real detectado en consulta |
| Peso_Kg | DECIMAL(5,2) | | | Peso del paciente en kg (nullable) |
| Temp_C | DECIMAL(4,1) | | | Temperatura corporal en °C (nullable) |
| Frecuencia_Cardíaca | INT | | | Latidos por minuto (nullable) |
| Anamnesis | TEXT | | | Relato clínico del dueño (nullable) |

Cuadro 3.17: Tabla Enfermedad_Diagnóstico

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Enfermedad | INT (SERIAL) | X | | Identificador surrogado |
| Código_CIE | VARCHAR(15) | | | Código CIE estandarizado (UK) |
| Nombre_Enfermedad | VARCHAR(100) | | | Nombre completo de la patología |

Cuadro 3.18: Tabla Resultado_Diagnóstico

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Resultado | INT (SERIAL) | X | | Identificador surrogado |
| ID_Atención | INT | | X | FK Atención_Clínica |
| ID_Enfermedad | INT | | X | FK Enfermedad_Diagnóstico |
| Tipo | VARCHAR(20) | | | Presuntivo o Definitivo |
| Observaciones | TEXT | | | Notas adicionales del médico (nullable) |

Cuadro 3.19: Tabla Procedimiento_Aplicado

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Procedimiento | INT (SERIAL) | X | | Identificador surrogado |
| ID_Atención | INT | | X | FK Atención_Clínica |
| ID_Item | INT | | X | FK Servicio (subclase de Item_Catálogo) |
| Resultados_Notas | TEXT | | | Hallazgos del procedimiento (nullable) |

Cuadro 3.20: Tabla Insumo_Utilizado

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Insumo_Uso | INT (SERIAL) | X | | Identificador surrogado |
| ID_Atención | INT | | X | FK Atención_Clínica |
| ID_Lote | INT | | X | FK Lote_Inventario. Lote consumido |
| Cantidad_Usada | INT | | | Unidades consumidas del lote |

Cuadro 3.21: Tabla Receta_Médica

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Receta | INT (SERIAL) | X | | Identificador surrogado |
| ID_Atención | INT | | X | FK Atención_Clínica |
| ID_Medicamento | INT | | X | FK Medicamento (genérico) |
| Dosis_Frecuencia | VARCHAR(100) | | | Posología: dosis y frecuencia |
| Duración_Días | INT | | | Días de tratamiento indicados |

Cuadro 3.22: Tabla Registro_Estancia

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Estancia | INT (SERIAL) | X | | Identificador surrogado |
| ID_Mascota | INT | | X | FK Mascota |
| Tipo | VARCHAR(20) | | | Guardería o Internamiento |
| Fecha_Ingreso | TIMESTAMP | | | Fecha y hora de ingreso a instalaciones |
| Fecha_Salida | TIMESTAMP | | | Fecha y hora de alta (nullable) |
| Nro_Jaula | VARCHAR(10) | | | Identificador alfanumérico de la jaula o espacio asignado |
| Instrucciones_Cuidado | TEXT | | | Indicaciones especiales (nullable) |

Cuadro 3.23: Tabla Transporte_Logística

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Transporte | INT (SERIAL) | X | | Identificador surrogado |
| ID_Cita | INT | | X | FK Cita |
| Código_Empleado | VARCHAR(20) | | X | FK Empleado (UK). Chofer asignado |
| Tipo_Ruta | VARCHAR(20) | | | Recojo o Entrega |
| Dirección_Destino | VARCHAR(150) | | | Dirección de recojo o entrega |
| Estado | VARCHAR(20) | | | Pendiente, En curso, Completado, Cancelado |

Cuadro 3.24: Tabla Factura

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Factura | INT (SERIAL) | X | | Identificador surrogado |
| Fecha_Emisión | TIMESTAMP | | | Fecha y hora de emisión |
| Subtotal | DECIMAL(10,2) | | | Monto antes de impuestos |
| IGV | DECIMAL(10,2) | | | Impuesto General a las Ventas |
| Total | DECIMAL(10,2) | | | Monto total a pagar |
| ID_Cliente | INT | | X | FK Cliente. Titular de la factura |
| ID_Atención | INT | | X | FK Atención_Clínica (nullable) |
| ID_Cita | INT | | X | FK Cita (nullable, CHECK exclusión mutua) |

Cuadro 3.25: Tabla Detalle_Factura

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Detalle | INT (SERIAL) | X | | Identificador surrogado |
| ID_Factura | INT | | X | FK Factura |
| ID_Item | INT | | X | FK Item_Catálogo |
| ID_Lote | INT | | X | FK Lote_Inventario (nullable) |
| ID_Estancia | INT | | X | FK Registro_Estancia (nullable) |
| Cantidad | INT | | | Unidades cobradas |
| Precio_Unitario | DECIMAL(10,2) | | | Precio unitario vigente al facturar |
| Subtotal_Línea | DECIMAL(10,2) | | | Precio Unitario \* Cantidad |

Cuadro 3.26: Tabla Pago

| Nombre Campo | Tipo de Dato | PK | FK | Descripción |
| :--- | :--- | :---: | :---: | :--- |
| ID_Pago | INT (SERIAL) | X | | Identificador surrogado |
| ID_Factura | INT | | X | FK Factura |
| Fecha_Pago | TIMESTAMP | | | Fecha y hora del abono |
| Monto_Abonado | DECIMAL(10,2) | | | Monto pagado en esta transacción |
| Método_Pago | VARCHAR(20) | | | Efectivo, Tarjeta, Yape, Plin, etc. |
