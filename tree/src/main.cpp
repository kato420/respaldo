#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// 1. Estructura de Película
struct Movie
{
  int id;
  std::string title;
  std::string plot;
};

// 2. Nodo del Trie
struct TrieNode
{
  std::unordered_map<char, TrieNode *> children;
  std::vector<int> word_ids;
};

// 3. El Motor Principal (Trie + Índice Invertido)
class InvertedSuffixTrie
{
private:
  TrieNode *root;
  std::unordered_map<int, std::vector<int>>
      inverted_index; // WordID -> Lista de MovieIDs
  int next_word_id = 1;
  std::unordered_map<std::string, int> word_to_id; // Para no repetir WordIDs

  void insertSuffixes(const std::string &word, int word_id)
  {
    for (size_t i = 0; i < word.length(); ++i)
    {
      std::string suffix = word.substr(i);
      TrieNode *current = root;
      for (char c : suffix)
      {
        if (current->children.find(c) == current->children.end())
        {
          current->children[c] = new TrieNode();
        }
        current = current->children[c];
      }
      // Evitar duplicar el mismo WordID en el nodo
      if (std::find(current->word_ids.begin(), current->word_ids.end(),
                    word_id) == current->word_ids.end())
      {
        current->word_ids.push_back(word_id);
      }
    }
  }
  void recolectarIDs(TrieNode *nodo, std::vector<int> &ids_recolectados)
  {
    if (!nodo)
      return;

    // Guardamos los IDs que encontremos en este nodo
    for (int id : nodo->word_ids)
    {
      if (std::find(ids_recolectados.begin(), ids_recolectados.end(), id) ==
          ids_recolectados.end())
      {
        ids_recolectados.push_back(id);
      }
    }

    // Viajamos recursivamente por todas las ramas que le sigan
    for (auto &par : nodo->children)
    {
      recolectarIDs(par.second, ids_recolectados);
    }
  }

public:
  InvertedSuffixTrie() { root = new TrieNode(); }

  // Procesa una película, separa palabras y construye la estructura
  void indexMovie(const Movie &movie)
  {
    std::stringstream ss(movie.plot + " " + movie.title);
    std::string word;

    while (ss >> word)
    {
      // Convertir a minúsculas simple para el ejemplo
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);

      int word_id;
      if (word_to_id.find(word) == word_to_id.end())
      {
        word_id = next_word_id++;
        word_to_id[word] = word_id;
        insertSuffixes(word, word_id); // Al árbol
      }
      else
      {
        word_id = word_to_id[word];
      }

      // Al índice invertido
      auto &movie_list = inverted_index[word_id];
      if (std::find(movie_list.begin(), movie_list.end(), movie.id) ==
          movie_list.end())
      {
        movie_list.push_back(movie.id);
      }
    }
  }

  // 2. La función de búsqueda corregida
  std::vector<int> searchSubWord(const std::string &query)
  {
    TrieNode *current = root;
    // Navegamos hasta donde termina el texto ingresado (ej. hasta la 'c' de
    // "arc")
    for (char c : query)
    {
      if (current->children.find(c) == current->children.end())
      {
        return {}; // No existe la sub-cadena en absoluto
      }
      current = current->children[c];
    }

    // ¡Magia aplicada! Hacemos el DFS hacia abajo para atrapar todos los
    // sufijos
    std::vector<int> collected_word_ids;
    recolectarIDs(current, collected_word_ids);

    // Finalmente, vamos al índice invertido a traer las películas
    std::vector<int> result_movie_ids;
    for (int w_id : collected_word_ids)
    {
      for (int m_id : inverted_index[w_id])
      {
        if (std::find(result_movie_ids.begin(), result_movie_ids.end(), m_id) ==
            result_movie_ids.end())
        {
          result_movie_ids.push_back(m_id);
        }
      }
    }
    return result_movie_ids;
  }
};

int main()
{
  // Simulamos la base de datos de películas
  std::vector<Movie> database = {
      {1, "titanic", "el enorme barco se hunde"},
      {2, "piratas", "un barco fantasma ataca"},
      {3, "arqueros", "competicion de tiro con arco"}};

  InvertedSuffixTrie motor_busqueda;

  std::cout << "Indexando base de datos...\n";
  for (const auto &movie : database)
  {
    motor_busqueda.indexMovie(movie);
  }

  // Interfaz de consola
  std::string query;
  while (true)
  {
    std::cout << "\n-------------------\n";
    std::cout << "Ingresa una busqueda (o 'salir'): ";
    std::cin >> query;

    if (query == "salir")
      break;

    std::vector<int> resultados = motor_busqueda.searchSubWord(query);

    if (resultados.empty())
    {
      std::cout << "No se encontraron coincidencias.\n";
    }
    else
    {
      std::cout << "Encontrado en " << resultados.size() << " peliculas:\n";
      for (int m_id : resultados)
      {
        // Buscamos la peli en la DB por su ID
        for (const auto &m : database)
        {
          if (m.id == m_id)
          {
            std::cout << "- [" << m.id << "] " << m.title
                      << " | Sinopsis: " << m.plot << "\n";
          }
        }
      }
    }
  }
  return 0;
}
