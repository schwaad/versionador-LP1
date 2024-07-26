#include "../include/repo.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../include/commit.h"
#include "../include/utils.h"

namespace fs = std::filesystem;

Repo createCommit(Repo repositorie) {
  Commit newCommit;
  std::string dotFilePath =
      repositorie.getRepoLocation() + "/" + ".versionadorLP1";
  fs::path infosPath = dotFilePath + "/" + "repoInfos.txt";
  int choice;

  do {
    choice = commitMenu();

    switch (choice) {
      case 0:
        break;

      case 1:  // 1 = Adicionar arquivos ao commit
        newCommit.addFileToCommit();
        clearInputBuffer();
        pauseProgram();
        break;

      case 2:  // 2 = Remover arquivos do commit
        newCommit.removeFileFromCommit();
        clearInputBuffer();
        pauseProgram();
        break;

      case 3:  // 3 = Verificar status do commit
        newCommit.checkCommitStatus();
        clearInputBuffer();
        pauseProgram();
        break;

      case 4:  // 4 = Encerrar o Commit
        std::cout << "Insira a mensagem do commit: ";
        std::string str;
        clearInputBuffer();
        std::getline(std::cin, str);

        // Verifica o número de commits no repositório e sobrescreve adicionando
        // +1 após o novo commit.
        std::string commitCount = getCommitCountfromInfos(infosPath);
        if (commitCount == "notfound") {
          std::cerr << "Erro ao obter o número de commits." << std::endl;
          std::cout << repositorie.getRepoLocation();
          break;
        }
        int newCommitCount = std::stoi(commitCount) + 1;
        rewriteCommitCount(infosPath, std::to_string(newCommitCount));

        std::string prevCommitDir = dotFilePath + "/" + "commit" + commitCount;
        std::string newCommitDir =
            dotFilePath + "/" + "commit" + std::to_string(newCommitCount);
        fs::create_directories(newCommitDir);
        // Se for não for o primeiro commit do repositório, copia todos os
        // arquivos do commit anterior, para que as atualizações que foram
        // feitas no commit anterior sejam mantidas.
        if (commitCount != "0") {
          fs::copy(prevCommitDir, newCommitDir, fs::copy_options::recursive);
          fs::remove_all(".versionadorLP1");
        }
        // Percorre o vetor de arquivos do commit adicionando cada arquivo á
        // pasta do commit recém criado e à pasta principal do repositório. Se o
        // arquivo for um diretório, cria um diretório de mesmo nome em ambas as
        // pastas e copia todo o seu conteúdo recursivamente.
        for (int i = 0; i < newCommit.getCommitFiles().size(); i++) {
          if (isDirectory(newCommit.getCommitFiles().at(i))) {
            fs::path commitToCommitDirectory =
                newCommitDir + "/" +
                filterDirPath(newCommit.getCommitFiles().at(i));
            fs::path commitToMainDirectory =
                repositorie.getRepoLocation() + "/" +
                filterDirPath(newCommit.getCommitFiles().at(i));
            fs::copy(newCommit.getCommitFiles().at(i), commitToCommitDirectory,
                     fs::copy_options::recursive |
                         fs::copy_options::overwrite_existing);

            fs::copy(newCommit.getCommitFiles().at(i), commitToMainDirectory,
                     fs::copy_options::recursive |
                         fs::copy_options::overwrite_existing);
          } else {
            fs::copy(newCommit.getCommitFiles().at(i), newCommitDir,
                     fs::copy_options::overwrite_existing);
            fs::copy(newCommit.getCommitFiles().at(i),
                     repositorie.getRepoLocation(),
                     fs::copy_options::overwrite_existing);
          }
        }
        newCommit.setCommitMessage(str);
        repositorie.addCommit(newCommit);
        break;
    }

  } while (choice != 0);
  return repositorie;
}

Repo createRepo() {
  Repo newRepo;
  std::cout << "Informe o nome do repositório: ";
  std::string newRepoName;
  std::cin >> newRepoName;
  newRepo.setRepoName(newRepoName);
  std::cout
      << "Informe o caminho do diretório onde o repositório será criado: ";
  std::string directoryPath;
  std::cin >> directoryPath;
  if (isDirectory(directoryPath)) {
    std::cout << "Criando repositório...\n";
    std::string repoPath = directoryPath + "/" + newRepoName;
    newRepo.setRepoDate(getCurrentDate());
    newRepo.setRepoLocation(repoPath);
    // Cria o diretório do repositório e preenche o arquivo repoInfos.txt com as
    // informações do repositório.
    fs::create_directories(repoPath);
    fs::create_directories(repoPath + "/" + ".versionadorLP1");
    std::ofstream outFile(repoPath + "/" + ".versionadorLP1" + "/" +
                          "repoInfos.txt");
    if (outFile.is_open()) {
      outFile << "creationdate: " << newRepo.getRepoDate() << "\n";
      outFile << "repoNameIs: " << newRepoName << "\n";
      outFile << "commits: 0" << "\n";
    }
    std::cout << "Repositório " << newRepoName << " criado com sucesso em "
              << repoPath << std::endl;
    return newRepo;
  } else {
    std::cout << "Ocorreu um erro: caminho inválido\n";
    return createRepo();
  }
}

Repo accessRepo() {
  std::cout
      << "Insira o caminho do repositório (ex.: Desktop/nome_do_repositorio): ";
  std::string str;
  std::cin >> str;
  fs::path repoPath = str;
  if (isRepo(repoPath)) {
    Repo acessedRepo;
    std::string infosPath =
        str + "/" + ".versionadorLP1" + "/" + "repoInfos.txt";
    acessedRepo.setRepoName(getRepoNamefromInfos(infosPath));
    acessedRepo.setRepoLocation(repoPath);
    std::cout << "Acessando repositório" + acessedRepo.getRepoName() + "...\n";
    return acessedRepo;
  } else {
    std::cout
        << "Ocorreu um erro: não foi encontrado um repositório no caminho "
           "informado. OBS.: Diretórios de repositórios possuem a pasta "
           "'.versionadorLP1' dentro deles.\n";
    return accessRepo();
  }
}

void removeRepo() {
  std::cout << "Insira o caminho do repositório que deseja remover:\n";
  fs::path repoPath;
  std::cin >> repoPath;
  if (isRepo(repoPath)) {
    fs::remove_all(repoPath);
    std::cout << "Repositório removido com sucesso.\n";
  } else {
    std::cout << "Ocorreu um erro: repositório não encontrado\n";
  }
}

void checkRepoStatus(Repo repositorie) {
  fs::path infosPath = repositorie.getRepoLocation() + "/" + ".versionadorLP1" +
                       "/" + "repoInfos.txt";
  std::cout << "Data de criação do repositório: "
            << getCreationDatefromInfos(infosPath) << "\n"
            << "Nome do repositório: " << getRepoNamefromInfos(infosPath)
            << "\n"
            << "Quantidade de commits até então: "
            << getCommitCountfromInfos(infosPath) << "\n";
}
