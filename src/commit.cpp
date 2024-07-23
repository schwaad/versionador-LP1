#include "../include/commit.h"

#include <ctime>
#include <iostream>

#include "../include/utils.h"

namespace fs = std::filesystem;

Commit createCommit() {
  Commit newCommit;
  int choice;

  do {
    choice = commitMenu();

    switch (choice) {
      case 1:  // 1 = Adicionar arquivos ao commit
        newCommit.addFileToCommit();
        clearInputBuffer();
        pauseProgram();
        break;

      case 2:  // 2 = Remover arquivos do commit
        std::cout << "Ainda vou implementar" << "\n";
        clearInputBuffer();
        pauseProgram();
        break;

      case 3:  // 3 = Encerrar o Commit
        std::cout << "Insira a mensagem do commit: ";
        std::string str;
        std::cin >> str;
        newCommit.setCommitMessage(str);
        break;
    }

  } while (choice != 3);

  return newCommit;
}
