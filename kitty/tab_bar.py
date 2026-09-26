import datetime
import platform
from collections.abc import Sequence
from functools import partial

from kitty.boss import get_boss
from kitty.fast_data_types import Screen, get_options
from kitty.tab_bar import (
    DrawData,
    ExtraData,
    TabBar,
    TabBarData,
    as_rgb,
    color_as_int,
    draw_title,
)

# =============================================================================
# Paleta de Colores Oh-My-Posh "Montys"
# =============================================================================
MONTYS_DARK_TEAL  = as_rgb(0x003543)  # Fondo segmento OS / Host
MONTYS_EMERALD    = as_rgb(0x00C983)  # Texto segmento OS / Host
MONTYS_RASPBERRY  = as_rgb(0xDA627D)  # Fondo segmento Path / Pestaña Activa
MONTYS_PEACH      = as_rgb(0xFCA17D)  # Salmón segmento Git / Alertas
MONTYS_SAGE       = as_rgb(0x76B367)  # Verde segmento Node
MONTYS_PURPLE     = as_rgb(0x83769C)  # Lavanda segmento ExecutionTime
MONTYS_STEEL_BLUE = as_rgb(0x33658A)  # Azul pizarra segmento Time
MONTYS_CYAN_TEAL  = as_rgb(0x2E9599)  # Turquesa segmento Status
MONTYS_MINT       = as_rgb(0x45F1C2)  # Menta brillante
MONTYS_WHITE      = as_rgb(0xFFFFFF)  # Blanco puro

_CACHED_OS_INFO = None


def _get_os_info() -> tuple[str, str]:
    global _CACHED_OS_INFO
    if _CACHED_OS_INFO is not None:
        return _CACHED_OS_INFO

    system = platform.system()
    hostname = platform.node().split(".")[0]
    icon = ""

    if system == "Darwin":
        icon = "󰀵"
    elif system == "Linux":
        try:
            with open("/etc/os-release", encoding="utf-8") as f:
                content = f.read().lower()
                if "cachyos" in content or "arch" in content:
                    icon = "󰣇"
                elif "fedora" in content:
                    icon = ""
                elif "ubuntu" in content:
                    icon = ""
                elif "debian" in content:
                    icon = ""
                elif "void" in content:
                    icon = ""
                elif "manjaro" in content:
                    icon = ""
        except Exception:
            pass

    _CACHED_OS_INFO = (icon, hostname)
    return _CACHED_OS_INFO


def _draw_left_bubble(text: str, screen: Screen, default_bg: int) -> int:
    bubble_bg = MONTYS_DARK_TEAL
    bubble_fg = MONTYS_EMERALD
    bar_bg = as_rgb(int(default_bg))

    # Borde redondeado izquierdo ()
    screen.cursor.fg = bubble_bg
    screen.cursor.bg = bar_bg
    screen.draw("")

    # Contenido con fondo teal oscuro y texto verde esmeralda montys
    screen.cursor.fg = bubble_fg
    screen.cursor.bg = bubble_bg
    screen.cursor.bold = True
    screen.draw(text)
    screen.cursor.bold = False

    # Borde redondeado derecho ()
    screen.cursor.fg = bubble_bg
    screen.cursor.bg = bar_bg
    screen.draw("")

    return screen.cursor.x


def _draw_right_bubble(text: str, screen: Screen, default_bg: int) -> int:
    bubble_bg = MONTYS_STEEL_BLUE
    bubble_fg = MONTYS_WHITE
    bar_bg = as_rgb(int(default_bg))

    # Borde redondeado izquierdo ()
    screen.cursor.fg = bubble_bg
    screen.cursor.bg = bar_bg
    screen.draw("")

    # Contenido con fondo azul montys y texto blanco
    screen.cursor.fg = bubble_fg
    screen.cursor.bg = bubble_bg
    screen.cursor.bold = False
    screen.draw(text)

    # Borde redondeado derecho ()
    screen.cursor.fg = bubble_bg
    screen.cursor.bg = bar_bg
    screen.draw("")

    return screen.cursor.x


def _draw_tab(
    draw_data: DrawData,
    screen: Screen,
    tab: TabBarData,
    before: int,
    max_tab_length: int,
    index: int,
    is_last: bool,
    extra_data: ExtraData,
) -> int:
    left_sep = ""
    right_sep = ""
    bar_bg = as_rgb(color_as_int(draw_data.default_bg))
    tab_bg = as_rgb(draw_data.tab_bg(tab))
    tab_fg = as_rgb(draw_data.tab_fg(tab))

    orig_fg = screen.cursor.fg
    orig_bg = screen.cursor.bg

    # Caso en que el ancho disponible es muy reducido
    if max_tab_length <= 3:
        screen.cursor.fg = tab_bg
        screen.cursor.bg = bar_bg
        screen.draw(left_sep)
        screen.cursor.fg = tab_fg
        screen.cursor.bg = tab_bg
        screen.draw("…")
        screen.cursor.fg = tab_bg
        screen.cursor.bg = bar_bg
        screen.draw(right_sep)
        if not is_last:
            screen.cursor.bg = bar_bg
            screen.draw(" ")
        screen.cursor.fg = orig_fg
        screen.cursor.bg = orig_bg
        return screen.cursor.x

    # 1. Borde redondeado inicial de la burbuja ()
    screen.cursor.fg = tab_bg
    screen.cursor.bg = bar_bg
    screen.draw(left_sep)

    # 2. Contenido interno de la pestaña
    screen.cursor.fg = tab_fg
    screen.cursor.bg = tab_bg
    if tab.is_active:
        screen.cursor.bold = True
    else:
        screen.cursor.bold = False

    draw_title(draw_data, screen, tab, index, max_tab_length)

    # Truncado elegante con elipsis si excede el tamaño máximo
    extra = screen.cursor.x - before - max_tab_length
    if extra >= 0:
        if screen.cursor.x > before + 3:
            screen.cursor.x = max(before + 2, screen.cursor.x - extra - 1)
            screen.draw("…")

    # 3. Borde redondeado final de la burbuja ()
    screen.cursor.fg = tab_bg
    screen.cursor.bg = bar_bg
    screen.cursor.bold = False
    screen.draw(right_sep)

    # 4. Separación entre burbujas independientes
    if not is_last:
        screen.cursor.fg = bar_bg
        screen.cursor.bg = bar_bg
        screen.draw(" ")

    screen.cursor.fg = orig_fg
    screen.cursor.bg = orig_bg
    return screen.cursor.x


class WeirdTabBar(TabBar):
    def __init__(self, tab_bar: TabBar):
        self.inner = tab_bar

    def __getattr__(self, attr):
        return getattr(self.inner, attr)

    def __setattr__(self, attr, value):
        if attr == "draw_data":
            return self.inner.__setattr__(attr, value)
        else:
            return super().__setattr__(attr, value)

    def destroy(self) -> None:
        self.inner.screen.reset_callbacks()
        del self.inner.screen

    def update(self, data: Sequence[TabBarData]) -> None:
        opts = get_options()
        screen = self.inner.screen
        orig_align = self.inner.align

        # Preparar widgets montys
        os_icon, hostname = _get_os_info()
        left_text = f" {os_icon} {hostname} "
        left_total_len = len(left_text) + 2

        time_str = datetime.datetime.now().strftime("%H:%M")
        right_text = f"  {time_str} "
        right_total_len = len(right_text) + 2

        # Desplazamiento si las pestañas están ancladas a un lateral
        match opts.tab_bar_align:
            case "left":
                self.inner.align = partial(self.pad_left, left_total_len + 1)
            case "right":
                self.inner.align = partial(self.pad_right, right_total_len + 1)

        # Renderizar pestañas
        self.inner.update(data)

        default_bg = self.draw_data.default_bg

        # Evitar colisiones entre widgets y pestañas centradas
        if self.inner.cell_ranges:
            first_tab_x = self.inner.cell_ranges[0][0]
            last_tab_x = self.inner.cell_ranges[-1][1]
        else:
            first_tab_x = screen.columns
            last_tab_x = 0

        # Dibujar widget izquierdo si hay suficiente margen
        if first_tab_x > left_total_len + 1:
            screen.cursor.x = 0
            _draw_left_bubble(left_text, screen, default_bg)

        # Dibujar widget derecho si hay suficiente margen
        right_start = screen.columns - right_total_len
        if last_tab_x + 1 < right_start and right_start >= 0:
            screen.cursor.x = right_start
            _draw_right_bubble(right_text, screen, default_bg)

        self.inner.align = orig_align

    def pad_left(self, padding: int) -> None:
        self.screen.cursor.x = 0
        self.screen.insert_characters(padding)
        self.inner.cell_ranges = [
            (s + padding, e + padding) for (s, e) in self.inner.cell_ranges
        ]

    def pad_right(self, padding: int) -> None:
        if not self.inner.cell_ranges:
            return
        end = self.inner.cell_ranges[-1][1]
        if end < self.screen.columns - padding - 1:
            shift = self.screen.columns - end - padding
            self.screen.cursor.x = 0
            self.screen.insert_characters(shift)
            self.inner.cell_ranges = [
                (s + shift, e + shift) for (s, e) in self.inner.cell_ranges
            ]


def draw_tab(
    draw_data: DrawData,
    screen: Screen,
    tab: TabBarData,
    before: int,
    max_title_length: int,
    index: int,
    is_last: bool,
    extra_data: ExtraData,
) -> int:
    tm = get_boss().active_tab_manager
    if type(tm.tab_bar) is not WeirdTabBar:
        tm.tab_bar = WeirdTabBar(tm.tab_bar)

    return _draw_tab(
        draw_data, screen, tab, before, max_title_length, index, is_last, extra_data
    )
