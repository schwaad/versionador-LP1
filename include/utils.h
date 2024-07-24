#include <filesystem>
#include <iostream>

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

#endif
