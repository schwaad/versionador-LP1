#include <iostream>

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
            << "Digite o comando que deseja:" << "\n";
  std::cout << "1: Criar um Repositório\n";
  std::cout << "2: Acessar um Repositório\n";
  std::cout << "3: Apagar um Repositório\n";
  std::cin >> n;
  return 0;
}

int main() { menu(); }
