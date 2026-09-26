#ifndef LECTOR_CSV_H
#define LECTOR_CSV_H

#include "Pelicula.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class LectorCSV
{
public:
  /////// PRIMERO
  static std::vector<Pelicula> leer_peliculas(const std::string &ruta_archivo)
  {
    std::vector<Pelicula> lista_peliculas;
    std::ifstream archivo(ruta_archivo);

    if (!archivo.is_open())
    {
      std::cout << "Error: No se pudo abrir el archivo CSV." << std::endl;
      return lista_peliculas;
    }

    ///// SEGUNDO
    std::string linea_temp;
    std::string fila_completa = "";
    bool en_comillas = false;
    int id_contador = 1;

    std::getline(archivo, linea_temp);

    //// TERCERO
    while (std::getline(archivo, linea_temp))
    {
      fila_completa += linea_temp;

      for (char letra : linea_temp)
      {
        if (letra == '"')
        {
          en_comillas = !en_comillas;
        }
      }

      if (en_comillas)
      {
        fila_completa += "\n";
        continue;
      }

      //// CUARTO
      std::vector<std::string> campos;
      std::string campo_actual = "";
      bool dentro_de_comillas_campo = false;

      for (char letra : fila_completa)
      {
        if (letra == '"')
        {
          dentro_de_comillas_campo = !dentro_de_comillas_campo;
        }
        else if (letra == ',' && !dentro_de_comillas_campo)
        {
          campos.push_back(campo_actual);
          campo_actual = "";
        }
        else
        {
          campo_actual += letra;
        }
      }
      campos.push_back(campo_actual);
      //// QUINTO

      if (campos.size() >= 8)
      {
        Pelicula p;
        p.id = id_contador++;
        p.año = campos[0];
        p.titulo = campos[1];
        p.origen = campos[2];
        p.director = campos[3];
        p.elenco = campos[4];
        p.genero = campos[5];
        p.link_wiki = campos[6];
        p.sinopsis = campos[7];

        lista_peliculas.push_back(p);
      }

      fila_completa = "";
    }

    archivo.close();
    return lista_peliculas;
  }
};

#endif
