#include "../include/commit.h"
#include "../include/repo.h"
#include "../include/utils.h"

int main() {
  do {
    switch (menu()) {
      case 1:
        createRepo();
        pauseProgram();
        break;
      case 2:
        repoMenu(accessRepo());
        clearInputBuffer();
        break;
      case 3:
        removeRepo();
        pauseProgram();
        break;
      case 0:
        std::cout << "Saindo...\n";
        return 0;
    }
  } while (menu() != 0);
  return 0;
}
