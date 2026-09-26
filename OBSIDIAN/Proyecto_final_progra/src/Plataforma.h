#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "LectorCSV.h"
#include "Pelicula.h"
#include <string>
#include <vector>

class Plataforma
{
private:
  std::vector<Pelicula> base_datos;
  std::vector<Pelicula *> ver_mas_tarde;
  std::vector<Pelicula *> likes;

  // Funcion auxiliar para convertir texto a minusculas
  std::string a_minusculas(std::string texto)
  {
    std::string res = texto;
    for (char &c : res)
    {
      c = std::tolower(c);
    }
    return res;
  }

public:
  void cargar_datos(const std::string &ruta_csv)
  {
    base_datos = LectorCSV::leer_peliculas(ruta_csv);
  }

  int total_peliculas() { return base_datos.size(); }

  // Busqueda simple para la presentacion de hoy.
  // Ojito: El arbol Trie se implementara y explicara por separado como pide la
  // rubrica
  std::vector<Pelicula *> buscar(const std::string &texto_buscado)
  {
    std::vector<Pelicula *> resultados;
    std::string buscar_min = a_minusculas(texto_buscado);

    for (auto &p : base_datos)
    {
      std::string titulo_min = a_minusculas(p.titulo);
      std::string sinopsis_min = a_minusculas(p.sinopsis);

      // Si encuentra el texto en titulo o sinopsis :V
      if (titulo_min.find(buscar_min) != std::string::npos ||
          sinopsis_min.find(buscar_min) != std::string::npos)
      {
        resultados.push_back(&p);
      }
    }
    return resultados;
  }

  void dar_like(Pelicula *p) { likes.push_back(p); }

  void agregar_ver_mas_tarde(Pelicula *p) { ver_mas_tarde.push_back(p); }

  std::vector<Pelicula *> obtener_ver_mas_tarde() { return ver_mas_tarde; }

  std::vector<Pelicula *> obtener_likes() { return likes; }
};

#endif
