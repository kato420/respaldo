#include "Plataforma.h"
#include <algorithm> // para std::min
#include <iostream>
#include <string>
#include <vector>

void mostrar_menu_principal()
{
  std::cout << "\n===================================" << std::endl;
  std::cout << "      PLATAFORMA DE STREAMING      " << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << "[1] Buscar pelicula" << std::endl;
  std::cout << "[2] Ver lista 'Ver mas tarde'" << std::endl;
  std::cout << "[3] Salir" << std::endl;
  std::cout << "Elige una opcion: ";
}

int main()
{
  Plataforma app;

  std::cout << "Cargando base de datos (por favor espere)..." << std::endl;
  app.cargar_datos("wiki_movie_plots_deduped.csv");

  if (app.total_peliculas() == 0)
  {
    std::cout << "No se pudieron cargar peliculas. Revisa la ruta del archivo."
              << std::endl;
    return 1;
  }

  std::cout << "Exito: Se cargaron " << app.total_peliculas() << " peliculas."
            << std::endl;

  bool ejecutando = true;
  std::string entrada_usuario;

  // BUCLE PRINCIPAL Anti-Crash :p
  while (ejecutando)
  {
    mostrar_menu_principal();

    // LEEMOS COMO TEXTO PARA EVITAR BUCLES INFINITOS SI PONEN LETRAS!!! :0
    std::getline(std::cin, entrada_usuario);

    if (entrada_usuario == "1")
    {
      std::cout << "\nIngrese la palabra o frase a buscar: ";
      std::string busqueda;
      std::getline(std::cin, busqueda);

      std::vector<Pelicula *> resultados = app.buscar(busqueda);

      if (resultados.empty())
      {
        std::cout << "No se encontraron peliculas con esa busqueda."
                  << std::endl;
        continue;
      }

      int total = resultados.size();
      int actual = 0;
      bool viendo_resultados = true;

      // SISTEMA DE PAGINACION
      while (viendo_resultados && actual < total)
      {
        std::cout << "\n--- Resultados (" << actual + 1 << " al "
                  << std::min(actual + 5, total) << " de " << total << ") ---"
                  << std::endl;

        // Mostrar hasta 5 peliculas
        for (int i = 0; i < 5 && (actual + i) < total; ++i)
        {
          std::cout << "[" << i + 1 << "] " << resultados[actual + i]->titulo
                    << " (" << resultados[actual + i]->año << ")" << std::endl;
        }

        std::cout << "\nOPCIONES:" << std::endl;
        std::cout << "[1-5] Abrir una pelicula" << std::endl;

        if (actual + 5 < total)
        {
          std::cout << "[S] Siguientes 5 resultados" << std::endl;
        }
        std::cout << "[0] Volver al menu principal" << std::endl;
        std::cout << "Elige una accion: ";

        std::string opc_res;
        std::getline(std::cin, opc_res);

        if (opc_res == "0")
        {
          viendo_resultados = false; // Salir de la busqueda
        }
        else if ((opc_res == "s" || opc_res == "S") && actual + 5 < total)
        {
          actual += 5; // Avanzar la pagina
        }
        else if (opc_res >= "1" && opc_res <= "5")
        {
          int num = std::stoi(opc_res) - 1;
          if (actual + num < total)
          {
            // VISTA DE LA PELICULA SELECCIONADA
            Pelicula *p = resultados[actual + num];
            std::cout << "\n***********************************" << std::endl;
            std::cout << "TITULO: " << p->titulo << " (" << p->año << ")"
                      << std::endl;
            std::cout << "DIRECTOR: " << p->director << std::endl;
            std::cout << "GENERO: " << p->genero << std::endl;
            std::cout << "SINOPSIS: " << p->sinopsis << std::endl;
            std::cout << "***********************************" << std::endl;

            std::cout << "\nAcciones: [1] Dar Like | [2] Ver mas tarde | [0] "
                         "Volver a resultados: ";
            std::string accion;
            std::getline(std::cin, accion);

            if (accion == "1")
            {
              app.dar_like(p);
              std::cout << ">> Le diste Like a esta pelicula! <<" << std::endl;
            }
            else if (accion == "2")
            {
              app.agregar_ver_mas_tarde(p);
              std::cout << ">> Agregada a 'Ver mas tarde' <<" << std::endl;
            }
          }
        }
        else
        {
          std::cout << ">> Opcion no valida. Intentelo de nuevo. <<"
                    << std::endl;
        }
      }
    }
    else if (entrada_usuario == "2")
    {
      std::vector<Pelicula *> lista = app.obtener_ver_mas_tarde();
      std::cout << "\n=== TU LISTA: VER MAS TARDE ===" << std::endl;
      if (lista.empty())
      {
        std::cout << "Tu lista esta vacia." << std::endl;
      }
      else
      {
        for (auto p : lista)
        {
          std::cout << "- " << p->titulo << " (" << p->año << ")" << std::endl;
        }
      }
      std::cout << "\nPresione ENTER para continuar...";
      std::getline(std::cin, entrada_usuario); // Pausa manual
    }
    else if (entrada_usuario == "3")
    {
      std::cout << "Saliendo de la plataforma. ¡Hasta pronto!" << std::endl;
      ejecutando = false;
    }
    else
    {
      std::cout << ">> Opcion invalida. Ingresa 1, 2 o 3. <<" << std::endl;
    }
  }

  return 0;
}
