# Configuración e Integración de Tema GTK en Obsidian

Este documento registra los ajustes realizados para que **Obsidian** se integre visualmente con el tema GTK del sistema (**WhiteSur-Dark-solid**) bajo Linux (XFCE / XFWM4).

---

## 1. Contexto y Diagnóstico

### Arquitectura de Obsidian
Obsidian es una aplicación basada en **Electron** (Chromium + Node.js). A diferencia de las aplicaciones nativas de Linux (como Thunar o Mousepad), su interfaz interna está renderizada con **HTML y CSS**, por lo que no hereda automáticamente los estilos de los temas GTK del sistema.

### El problema con el borde de la ventana
Obsidian mostraba controles de ventana planos y rectangulares (`—`, `▢`, `✕`) a la derecha, en lugar de la barra superior nativa con esquinas redondeadas y los tres botones circulares de colores (*traffic lights*: rojo, amarillo y verde) en la izquierda.

* **Causa técnica**: En el código interno de Obsidian (`/usr/lib/obsidian/obsidian.asar`), la aplicación comprueba la propiedad `frame` directamente en la raíz de su archivo global de configuración:
  ```javascript
  let Ae = D.frame === "native", Ue = Ae ? "default" : "hidden";
  new BrowserWindow({ frame: Ae, titleBarStyle: Ue, ... });
  ```
  En la configuración previa, `"frame": "native"` estaba anidado erróneamente dentro del objeto del vault (`vaults.<id>.frame`) en vez de la raíz. Por lo tanto, `D.frame` era `undefined` y Obsidian arrancaba en modo sin marco (*frameless*), renderizando sus propios controles cuadrados.

---

## 2. Archivos Modificados y Creados

### A. Configuración global: `~/.config/obsidian/obsidian.json`
Se trasladó la propiedad `frame` al nivel raíz:

```json
{
  "frame": "native",
  "vaults": {
    "9e755282d65e530a": {
      "path": "/home/utec/Desktop/OBSIDIAN",
      "ts": 1790368115469,
      "open": true
    }
  }
}
```
* **Resultado**: Electron delega la decoración de la ventana al gestor de ventanas del sistema (XFWM4), obteniendo la barra nativa de **WhiteSur** con esquinas redondeadas y los tres circulitos de colores.

---

### B. Configuración del Vault: `.obsidian/appearance.json`
Ubicación: `/home/utec/Desktop/OBSIDIAN/.obsidian/appearance.json`

```json
{
  "cssTheme": "macOS",
  "theme": "system",
  "enabledCssSnippets": [
    "centrar-mermaid",
    "whitesur-gtk"
  ],
  "baseFontSizeAction": false
}
```

* **`cssTheme: "macOS"`**: Aplica la estructura y estilo visual de macOS/WhiteSur.
* **`theme: "system"`**: Permite que Obsidian responda dinámicamente si el sistema cambia entre modo claro y oscuro.
* **`enabledCssSnippets`**: Activa el fragmento de estilos personalizado `whitesur-gtk`.

---

### C. Snippet CSS personalizado: `.obsidian/snippets/whitesur-gtk.css`
Ubicación: `/home/utec/Desktop/OBSIDIAN/.obsidian/snippets/whitesur-gtk.css`

Este archivo inyecta los valores exactos extraídos del tema `~/.themes/WhiteSur-Dark-solid/`:

* **Colores de la paleta**:
  * `theme_bg_color` (`#333333`): Paneles laterales, barra de título y pestañas inactivas.
  * `theme_base_color` (`#242424`): Fondo del editor principal de notas.
  * `theme_fg_color` (`#dedede`): Texto normal.
  * `selected_bg_color` (`#0860F2`): Acento azul característico de WhiteSur / Apple.
  * Bordes y divisores: `rgba(255, 255, 255, 0.12)`.
* **Scrollbars**: Estilo fino (8px) y redondeado con transparencia.
* **Respaldo de controles de ventana**: Si alguna vez se utiliza el marco integrado en lugar del nativo, incluye reglas CSS para que los botones de ventana se dibujen como círculos de colores en vez de cuadrados.

---

## 3. Mantenimiento y Ajustes Futuros

* **Cambiar el marco desde la interfaz**:
  Ve a **Ajustes** (⚙️) → **Aspecto** → **Estilo del marco de la ventana** y selecciona **Marco de ventana nativo** (*Native frame*).
* **Actualizaciones**:
  Las actualizaciones de Obsidian (mediante `pacman` o `paru`) no sobrescriben estos archivos, ya que están guardados en tu directorio de configuración de usuario (`~/.config/obsidian/`) y en la carpeta del vault (`.obsidian/`).
