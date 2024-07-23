#include <ctime>
#include <filesystem>
#include <iostream>
#include <vector>

#include "commit.h"

#ifndef _REPOH_
#define _REPOH_

class Repo {
 public:
  std::string name;
  std::time_t creationDate;
  std::vector<Commit> commits;
};

#endif
