#include "../include/commit.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "../include/utils.h"

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

void listCommitInfo(const std::string& commitInfoFilePath) {
  std::ifstream commitInfosFile(commitInfoFilePath);
  if (!commitInfosFile.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << commitInfoFilePath << "\n";
    return;
  }

  std::string line;
  std::string commitMessage;
  std::vector<std::string> commitFiles;
  bool readingFiles = false;

  while (std::getline(commitInfosFile, line)) {
    if (line.rfind("commitMessage:", 0) == 0) {
      commitMessage = line.substr(14);  // Remove o prefixo "commitMessage: "
    } else if (line == "commitedFiles:") {
      readingFiles = true;
    } else if (readingFiles) {
      commitFiles.push_back(line);
    }
  }

  commitInfosFile.close();

  std::cout << "Commit Message: " << commitMessage << "\n";
  std::cout << "Committed Files:\n";
  for (const auto& file : commitFiles) {
    std::cout << file << "\n";
  }
}
