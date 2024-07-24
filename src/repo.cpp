#include "../include/repo.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "../include/commit.h"
#include "../include/utils.h"

namespace fs = std::filesystem;

Repo createCommit(Repo repositorie) {
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
        // Declara como string o caminho até a pasta .versionadorLP1
        std::string dotFilePath =
            repositorie.getRepoLocation() + "/" + ".versionadorLP1";
        // Declara como string o nome da pasta do commit, que sempre é
        // commit<algum número>, com base em quantos commits o repositório tem.
        std::string commitCount =
            std::to_string(repositorie.getRepoCommits().size() + 1);
        std::string newCommitDir = dotFilePath + "/" + "commit" + commitCount;
        fs::create_directories(newCommitDir);
        // Itera pelos arquivos do commit, até que todos sejam copiados para a
        // pasta commit<número>. Copia recursivamente os arquivos se for um
        // diretório ou apenas copia o arquivo se for um arquivo simples.
        for (int i = 0; i < newCommit.getCommitFiles().size(); i++) {
          if (isDirectory(newCommit.getCommitFiles().at(i))) {
            fs::copy(newCommit.getCommitFiles().at(i), newCommitDir,
                     fs::copy_options::recursive |
                         fs::copy_options::overwrite_existing);

            fs::copy(newCommit.getCommitFiles().at(i),
                     repositorie.getRepoLocation(),
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
  } while (choice != 5);

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
    // Declara como string o caminho até o repositório que está sendo criado
    std::string repoPath = directoryPath + "/" + newRepoName;
    // Registra a localização do repositório e cria o diretório .versionadorLP1
    // bem como o arquivo repoInfos.txt dentro dele.
    newRepo.setRepoLocation(repoPath);
    fs::create_directories(repoPath);
    fs::create_directories(repoPath + "/" + ".versionadorLP1");
    std::ofstream outFile(repoPath + "/" + ".versionadorLP1" + "/" +
                          "repoInfos.txt");
    if (outFile.is_open()) {
      outFile << "repoNameIs: " << newRepoName;
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
  if (fs::exists(repoPath) && fs::is_directory(repoPath)) {
    Repo acessedRepo;
    std::string infosPath =
        str + "/" + ".versionadorLP1" + "/" + "repoInfos.txt";
    acessedRepo.setRepoName(getRepoNamefromInfos(infosPath));
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
