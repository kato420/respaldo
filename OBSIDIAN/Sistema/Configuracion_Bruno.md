# Configuración e Integración de Tema GTK en Bruno

Este documento registra los ajustes realizados en **Bruno** para su integración con el tema GTK del sistema (**WhiteSur-Dark-solid**) y la resolución de problemas en Linux (Arch / XFCE).

---

## 1. Ubicación de Archivos de Bruno

* **Ejecutable del sistema**: `/usr/bin/bruno` (enlace simbólico a `/opt/Bruno/bruno`).
* **Código de la aplicación (Electron)**: `/opt/Bruno/resources/app.asar`.
* **Configuración del usuario**: `~/.config/bruno/`
  * `preferences.json`: Preferencias de red, fuentes, visualización y actualización.
  * `ui-state-snapshot.json`: Estado de paneles y pestañas.
  * `bruno.db`: Base de datos de workspaces y colecciones.
  * `enable-native-frame.py`: Script para activar el marco nativo de WhiteSur.

---

## 2. Problemas Identificados

### A. Ausencia del marco nativo y controles tipo WhiteSur
A diferencia de Obsidian, Bruno **no ofrece en su interfaz una opción para activar el marco de ventana nativo**. En su código (`/opt/Bruno/resources/app.asar`), los desarrolladores forzaron:
```javascript
frame: isLinux ? false : true  // Desactiva el marco en Linux
```
Además, su cabecera en React incluía controles de ventana propios con iconos planos estilo Windows (`—`, `▢`, `✕`) a la derecha.

### B. Solicitud de contraseña de administrador al cerrar Bruno
Al intentar cerrar la aplicación, aparecía una ventana emergente de autenticación (`pkexec` / polkit) pidiendo contraseña de superusuario para ejecutar:
```bash
dpkg -i /home/utec/.cache/bruno-updater/pending/bruno_*.deb || apt-get install -f -y
```
* **Causa técnica**: Bruno tiene un servicio de actualización automática en segundo plano. Al detectar una nueva versión, descargaba un paquete `.deb` (diseñado para Debian/Ubuntu) en `~/.cache/bruno-updater/` y programaba su instalación en el evento de cierre (`quitAndInstall()`). Como el sistema es Arch Linux (donde los paquetes se gestionan mediante `paru` / `pacman`), este comportamiento causaba el molesto cuadro de autenticación en cada salida.

---

## 3. Soluciones y Ajustes Aplicados

### A. Configuración de Usuario: `~/.config/bruno/preferences.json`

Se modificaron los siguientes parámetros:

1. **Desactivación del auto-updater**:
   ```json
   "autoupdate": {
       "downloadUpdates": false
   }
   ```
   *Evita que Bruno descargue paquetes `.deb` y pida contraseña al cerrar.*

2. **Tipografía GTK del sistema**:
   ```json
   "font": {
       "codeFont": "JetBrainsMono Nerd Font",
       "codeFontSize": 13
   }
   ```
   *Alinea el editor de peticiones y respuestas con la fuente monoespaciada de XFCE.*

3. **Color base y modo de tema**:
   ```json
   "themeMode": "system",
   "themeBg": "#242424"
   ```
   *Usa `#242424` (el color de fondo exacto de WhiteSur-Dark) y sincroniza el modo claro/oscuro con el escritorio.*

---

### B. Limpieza de paquetes pendientes
Se eliminó la caché del actualizador para cancelar cualquier instalación pendiente:
```bash
rm -rf ~/.cache/bruno-updater
```

---

### C. Activación del marco nativo: `~/.config/bruno/enable-native-frame.py`
Se creó un script de parcheo binario seguro que actúa sobre `/opt/Bruno/resources/app.asar`:
1. Crea un respaldo automático en `/opt/Bruno/resources/app.asar.bak`.
2. Sustituye `frame: isLinux ? false : true` por `frame: true/* native frame */` (habilita la barra superior de WhiteSur con los tres circulitos de colores).
3. Oculta los botones planos internos de la cabecera en React para que no queden duplicados.
4. Mantiene la misma longitud exacta de bytes para evitar cualquier inestabilidad.

#### Comando de ejecución:
```bash
sudo ~/.config/bruno/enable-native-frame.py
```

#### Comando de reversión (si alguna vez se desea volver al estado original):
```bash
sudo ~/.config/bruno/enable-native-frame.py --revert
```

---

## 4. Comportamiento frente a Actualizaciones del Sistema (`paru -Syu`)

* **Preferencias**: `~/.config/bruno/preferences.json` **nunca se sobrescribe** con `paru`. La tipografía, colores y la desactivación del auto-updater se mantienen de forma permanente.
* **Marco de ventana tras actualizar**: Cuando `paru` actualiza el paquete `bruno-bin`, reemplaza `app.asar` por la nueva versión oficial. Para volver a activar los circulitos de WhiteSur en la nueva versión, simplemente vuelve a ejecutar:
  ```bash
  sudo ~/.config/bruno/enable-native-frame.py
  ```
