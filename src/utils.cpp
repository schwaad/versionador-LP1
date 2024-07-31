#include "../include/utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../include/repo.h"

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
            << "Digite a opção que você deseja:" << "\n"
            << "1: Criar um Repositório" << "\n"
            << "2: Acessar um Repositório" << "\n"
            << "3: Apagar um Repositório" << "\n"
            << "0: Sair" << "\n";
  std::cin >> n;
  return n;
}

int commitMenu() {
  clearTerminal();
  int n;
  std::cout << "Criando um novo commit..." << "\n"
            << "Digite a opção que você deseja:" << "\n"
            << "1: Adicionar arquivos ao commit" << "\n"
            << "2: Remover arquivos do commit" << "\n"
            << "3: Visualizar status do commit" << "\n"
            << "4: Encerrar Commit" << "\n"
            << "0: Voltar ao menu de repositório" << "\n";
  std::cin >> n;
  return n;
}

// Menu exibido após escolher a opção "Acessar repositório" no menu principal
void repoMenu(Repo repositorie) {
  int choice;
  do {
    clearTerminal();
    std::cout << "Digite a opção que deseja:\n"
              << "1: Criar um novo Commit\n"
              << "2: Verificar status do repositório\n"
              << "3: Voltar para uma versão anterior\n"
              << "0: Voltar ao menu principal\n";
    std::cin >> choice;

    switch (choice) {
      case 1:
        createCommit(repositorie);
        pauseProgram();
        break;
      case 2:
        checkRepoStatus(repositorie);
        pauseProgram();
        break;
      case 3:
        changeRepoVersion(repositorie.getRepoLocation());
        pauseProgram();
        break;
      case 0:
        break;
      default:
        std::cout << "Opção inválida, tente novamente.\n";
        pauseProgram();
        break;
    }
  } while (choice != 0);
}

void pauseProgram() {
  std::cout << "Insira qualquer tecla para continuar...";
  getchar();
  clearInputBuffer();
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

  // Percorre todo o arquivo repoInfos.txt procurando pela linha que contenha
  // "repoNameIs:". Após isso, registra o nome do repositório, que está
  // exatamente 11 caracteres (é o tamanho da palavra "repoNameIs:") depois do
  // início da linha.
  while (std::getline(file, line)) {
    if (line.find("repoNameIs:") != std::string::npos) {
      repoName = line.substr(line.find("repoNameIs:") + 11);
      return repoName;
    }
  }

  std::cerr
      << "Ocorreu um erro: não foi possível encontrar o nome do repositório.\n";
  return "notfound";
}

std::string getCommitCountfromInfos(fs::path infosPath) {
  std::string commitCount;
  std::ifstream file(infosPath);

  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << infosPath << "\n";
    return "notfound";
  }

  std::string line;
  size_t lineNumber = 0;

  // Percorre todo o arquivo repoInfos.txt procurando pela linha que contenha
  // "commits: ". Após isso, registra o nome do repositório, que está
  // exatamente 9 caracteres (é o tamanho da palavra "commits: ") depois do
  // início da linha.
  while (std::getline(file, line)) {
    lineNumber++;
    if (line.find("commits: ") != std::string::npos) {
      commitCount = line.substr(line.find("commits: ") + 9);
      return commitCount;
      break;
    }
  }
  return "notfound";
}

std::string getCreationDatefromInfos(fs::path infosPath) {
  std::string creationDate;
  std::ifstream file(infosPath);

  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << infosPath << "\n";
    return "notfound";
  }

  std::string line;
  size_t lineNumber = 0;

  // Percorre todo o arquivo repoInfos.txt procurando pela linha que contenha
  // "commits: ". Após isso, registra o nome do repositório, que está
  // exatamente 14 caracteres (é o tamanho da palavra "creationdate: ") depois
  // do início da linha.
  while (std::getline(file, line)) {
    lineNumber++;
    if (line.find("creationdate: ") != std::string::npos) {
      creationDate = line.substr(line.find("creationdate: ") + 14);
      return creationDate;
      break;
    }
  }
  return "notfound";
}

// Reescreve o número de commits no arquivo repoInfos.txt
void rewriteCommitCount(fs::path filename, std::string newCommitCount) {
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Ocorreu um erro, não foi possível abrir o arquivo: "
              << filename << std::endl;
    return;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(infile, line)) {
    if (line.find("commits:") != std::string::npos) {
      std::stringstream ss;
      ss << "commits: " << newCommitCount;
      line = ss.str();
    }
    lines.push_back(line);
  }
  infile.close();

  std::ofstream outfile(filename);
  if (!outfile) {
    std::cerr << "Ocorreu um erro, não foi possível abrir o arquivo: "
              << filename << std::endl;
    return;
  }

  for (const auto& l : lines) {
    outfile << l << std::endl;
  }
  outfile.close();
}

// Verifica se um diretório possui a pasta .versionadorLP1, se tiver, retorna
// true.
bool isRepo(const std::string& dirPath) {
  if (fs::exists(dirPath + "/" + ".versionadorLP1") && isDirectory(dirPath)) {
    return true;
  }
  return false;
}

std::string getCurrentDate() {
  std::time_t now = std::time(nullptr);
  std::tm* localTime = std::localtime(&now);

  char buffer[100];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

  return std::string(buffer);
}

// Filtra apenas o último nome em um caminho.
std::string filterDirPath(const std::string& dirPath) {
  std::size_t found = dirPath.find_last_of("/\\");
  return dirPath.substr(found + 1);
}

void processCommitInfo(const fs::path& commitInfoPath,
                       std::vector<std::string>& committedFiles) {
  std::ifstream file(commitInfoPath);
  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << commitInfoPath << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("commitedFiles:") == 0) {
      while (std::getline(file, line) && !line.empty()) {
        committedFiles.push_back(line);
      }
    }
  }

  file.close();
}

void clearDirectory(const fs::path& path) {
  for (const auto& entry : fs::directory_iterator(path)) {
    if (entry.path().filename() != ".versionadorLP1") {
      fs::remove_all(entry);
    }
  }
}

void copyFiles(const fs::path& srcDir, const fs::path& destDir,
               const std::vector<std::string>& files) {
  for (const auto& file : files) {
    fs::path srcFilePath = srcDir / file;
    fs::path destFilePath = destDir / file;
    fs::create_directories(destFilePath.parent_path());
    fs::copy_file(srcFilePath, destFilePath,
                  fs::copy_options::overwrite_existing);
  }
}
