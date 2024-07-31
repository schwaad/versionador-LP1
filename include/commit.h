#include <ctime>
#include <filesystem>
#include <iostream>
#include <string>
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
    std::string fileName;
    std::cout << "Insira a seguir o arquivo que você deseja adicionar ao "
                 "commit."
              << std::endl;
    // Verifica se o arquivo  existe e o adiciona ao atributo commitFiles se
    // positivo.
    try {
      std::cin >> fileName;
      if (fs::exists(fileName)) {
        commitFiles.push_back(fileName);
      } else {
        std::cout << "Ocorreu um Erro: Arquivo não encontrado." << "\n";
      }
    } catch (const fs::filesystem_error& e) {
      std::cerr << "Ocorreu um Erro: " << e.what() << std::endl;
    }
  }

  void removeFileFromCommit() {
    std::string fileName;
    std::cout << "Digite o nome do arquivo que você deseja remover do Commit"
              << std::endl;
    try {
      std::cin >> fileName;
    } catch (const fs::filesystem_error& e) {
      std::cerr << "Ocorreu um Erro: " << e.what() << std::endl;
    }
    // Itera sobre o vetor commitFiles até que encontre o arquivo
    for (int i = 0; i < size(commitFiles); i++) {
      if (commitFiles.at(i) == fileName) {
        commitFiles.erase(commitFiles.begin() + i);
      }
    }
  }

  void checkCommitStatus() {
    std::cout << "Arquivos que serão inseridos no commit:" << "\n";
    // Itera sobre o vetor commitFiles exibindo cada arquivo dentro dele,
    for (int i = 0; i < getCommitFiles().size(); i++) {
      std::cout << "  " << getCommitFiles().at(i) << "\n";
    }
  }
};

#endif
