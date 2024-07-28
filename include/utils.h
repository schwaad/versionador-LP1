#include <filesystem>
#include <iostream>

#include "repo.h"

namespace fs = std::filesystem;

#ifndef _UTILSH_
#define _UTILSH_

void clearInputBuffer();
void clearTerminal();
int menu();
int commitMenu();
void pauseProgram();
bool isDirectory(const std::string& path);
std::string getRepoNamefromInfos(fs::path infosPath);
std::string getCommitCountfromInfos(fs::path infosPath);
std::string getCreationDatefromInfos(fs::path infosPath);
void rewriteCommitCount(fs::path filename, std::string newCommitCount);
bool isRepo(const std::string& dirPath);
void repoMenu(Repo repositorie);
std::string getCurrentDate();
std::string filterDirPath(const std::string& dirPath);
void readCommitInfos(const std::string& commitInfosPath);
#endif
