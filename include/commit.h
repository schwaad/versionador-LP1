#include <ctime>
#include <filesystem>
#include <iostream>
#include <vector>

#ifndef _COMMITH_
#define _COMMITH_

namespace fs = std::filesystem;

class Commit {
 public:
  std::string commitMessage;
  std::time_t creationDate;
  std::vector<std::string> commitFiles;

 public:
  std::string getCommitMessage() { return commitMessage; }
  std::time_t getCreationDate() { return creationDate; }
  std::vector<std::string> getCommitFiles() { return commitFiles; }
  void setCommitMessage(std::string message) { commitMessage = message; }
  void setCreationDate(std::time_t date) { creationDate = date; }

  void addFileToCommit() {
    fs::path fileName;
    std::cout << "Insira a seguir o arquivo que você deseja adicionar ao "
                 "commit."
              << std::endl;
    try {
      std::cin >> fileName;

    } catch (const fs::filesystem_error& e) {
      std::cerr << "Ocorreu um Erro: " << e.what() << std::endl;
    }
    commitFiles.push_back(fileName);
  }

  void removeFileFromCommit() {
    fs::path fileName;
    std::cout << "Digite o nome do arquivo que você deseja remover do Commit"
              << std::endl;
    try {
      std::cin >> fileName;

    } catch (const fs::filesystem_error& e) {
      std::cerr << "Ocorreu um Erro: " << e.what() << std::endl;
    }
    for (int i = 0; i < size(commitFiles); i++) {
      if (commitFiles.at(i) == fileName) {
        commitFiles.erase(commitFiles.begin() + i);
      }
    }
  }
};

Commit createCommit();

#endif
