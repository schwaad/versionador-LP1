#include "../include/utils.h"

#include <iostream>
#include <limits>

void clearInputBuffer() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearTerminal() {
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
            << "3: Encerrar Commit" << "\n";
  std::cin >> n;
  return n;
}

void pauseProgram() {
  std::cout << "Insira qualquer tecla para continuar...";
  getchar();
}
