#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[]) {
  uid_t euid = geteuid();
  if (euid == 0) {
    std::string query;
    if (argc == 2) {
      std::string arg1 = argv[1];
      if (arg1 == "-i") {
        query = "xbps-query -Rs '*' | awk '{print $2}' | fzf --prompt=\"Select "
                "package(s) to install: \" --multi "
                "--border | xargs -ro xbps-install -Sy";
      } else if (arg1 == "-r") {
        query = "xbps-query -m | xargs -n1 xbps-uhelper getpkgname | fzf "
                "--prompt=\"Select package(s) to remove: \" --multi "
                "--border | xargs -ro doas xbps-remove -Ro";
      }
    } else {
      std::cerr << "Usage: sudo fzxbps -i (install) or -r (remove)\n";
      return 1;
    }
    std::system(query.c_str());
  } else {
    std::cerr << "Must be run with root privileges\n";
    return 1;
  }

  return 0;
}
