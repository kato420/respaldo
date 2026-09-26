# AGENTS.md

## Project
LaTeX document (Spanish, `report` class) for a university database implementation project.

## Entrypoint
- `main.tex` — root file; contains preamble, package imports, and `\input{}` calls to sub-files. No prose in this file.

## File structure
Sub-files loaded by `main.tex` via `\input{}`:
- `caratula.tex` — title page, logos, authors
- `indice.tex` — table of contents
- `requisitos.tex` — Chapter 1
- `modelo_ER.tex` — Chapter 2
- `modelo_relacional.tex` — Chapter 3

## Required packages
`inputenc` (utf8), `fontenc` (T1), `babel` (spanish), `graphicx`, `geometry`, `hyperref`, `tabularx`, `multirow`, `booktabs`, `float`, `titlesec`

## Build
No build system is configured. Compile with `pdflatex main.tex` (run twice for ToC cross-references).
