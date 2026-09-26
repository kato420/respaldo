#ifndef PELICULA_H
#define PELICULA_H

#include <string>

struct Pelicula
{
  int id;
  std::string año;
  std::string titulo;
  std::string origen;
  std::string director;
  std::string elenco;
  std::string genero;
  std::string link_wiki;
  std::string sinopsis;
};

#endif
