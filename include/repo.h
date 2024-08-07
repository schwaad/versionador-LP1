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
  std::string location;
  std::string creationDate;
  std::vector<Commit> commits;

 public:
  std::string getRepoName() { return name; };
  std::string getRepoDate() { return creationDate; };
  std::string getRepoLocation() { return location; }
  std::vector<Commit> getRepoCommits() { return commits; };
  void setRepoName(std::string newname) { name = newname; };
  void setRepoDate(std::string newdate) { creationDate = newdate; };
  void setRepoLocation(std::string repoLocation) { location = repoLocation; };

  void addCommit(Commit addedCommit) { commits.push_back(addedCommit); }
};

Repo createCommit(Repo repositorie);
Repo createRepo();
Repo accessRepo();
void removeRepo();
void checkRepoStatus(Repo repositorie);
void changeRepoVersion(const std::string& repoDir);

#endif
