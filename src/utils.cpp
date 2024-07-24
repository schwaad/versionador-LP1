#include "../include/utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

namespace fs = std::filesystem;

void clearInputBuffer() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearTerminal() {
  // Utiliza comandos diferentes dependendo do sistema operacional.
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int menu() {
  int n;
  clearTerminal();
  std::cout
      << R"( _   _               _                       _              _     ______  __  
| | | |             (_)                     | |            | |    | ___ \/  | 
| | | | ___ _ __ ___ _  ___  _ __   __ _  __| | ___  _ __  | |    | |_/ /`| | 
| | | |/ _ \ '__/ __| |/ _ \| '_ \ / _` |/ _` |/ _ \| '__| | |    |  __/  | | 
\ \_/ /  __/ |  \__ \ | (_) | | | | (_| | (_| | (_) | |    | |____| |    _| |_
 \___/ \___|_|  |___/_|\___/|_| |_|\__,_|\__,_|\___/|_|    \_____/\_|    \___/
                                                                              )"
      << std::endl;
  std::cout << "Bem vindo ao Versionador LP1!\n"
            << "Digite o comando que deseja:" << "\n"
            << "1: Criar um Repositório" << "\n"
            << "2: Acessar um Repositório" << "\n"
            << "3: Apagar um Repositório" << "\n";
  std::cin >> n;
  return n;
}

int commitMenu() {
  int n;
  clearTerminal();
  std::cout << "Criando um novo commit..." << "\n"
            << "Digite a opção que você deseja:" << "\n"
            << "1: Adicionar arquivos ao commit" << "\n"
            << "2: Remover arquivos do commit" << "\n"
            << "3: Visualizar status do commit" << "\n"
            << "4: Encerrar Commit" << "\n";
  std::cin >> n;
  return n;
}

void pauseProgram() {
  std::cout << "Insira qualquer tecla para continuar...";
  getchar();
}

bool isDirectory(const std::string& path) {
  fs::directory_entry entry(path);
  return entry.exists() && entry.is_directory();
}

std::string getRepoNamefromInfos(fs::path infosPath) {
  std::string repoName;
  std::ifstream file(infosPath);

  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << infosPath << "\n";
    return "notfound";
  }

  std::string line;
  size_t lineNumber = 0;

  // Percorre todo o arquivo repoInfos.txt procurando pela linha que contenha
  // "repoNameIs:". Após isso, registra o nome do repositório, que está
  // exatamente 11 caracteres (é o tamanho da palavra "repoNameIs:") depois do
  // início da linha.
  while (std::getline(file, line)) {
    lineNumber++;
    if (line.find("repoNameIs:") != std::string::npos) {
      repoName = line.substr(line.find("repoNameIs:") + 11);
    } else {
      std::cout << "Ocorreu um erro: não foi possível encontrar o nome do "
                   "repositório.";
      return "notfound";
    }
  }
  return repoName;
}
