#include <boost/algorithm/string/case_conv.hpp>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <istream>
#include <string>
#include <cstring>
#include <vector>
#include <filesystem>
#include "conf/Parser.h"

#define COL_GREEN    "\033[32m"
#define COL_RED    "\033[31m"
#define COL_RESET    "\e[0;m"

inline bool strprf(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

inline std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

inline bool mintAskOnPkgOperation=true;
inline void mintPkgOperation(std::string data, const char* script) {

        auto repository = split(data, "/")[0];
        auto repositoryData = parseConfFile("/etc/mint/repo.conf");
        std::string repositoryUrl;
        auto package = split(data, "/")[1];
        auto command = std::string("bash ") + script;

        if (repositoryData.find(repository) == repositoryData.end()) { std::cout << "Unknown repository!" << "\n"; exit(1);} else {
            repositoryUrl = repositoryData[repository];
        }

        if (mintAskOnPkgOperation==true) {
            std::string result;
            std::cout << package << " : Install this package? [Y/n]: ";
            std::cin >> result;

            if (boost::algorithm::to_lower_copy(result)=="y" || boost::algorithm::to_lower_copy(result)=="yes") {} else {
                exit(0);
            }
        }

        system(("cd /tmp && git init " + repository).c_str());
        system(("cd /tmp && cd " + repository + " && git remote add -f origin " + repositoryUrl).c_str());
        system(("cd /tmp && cd " + repository + " && git sparse-checkout init --cone").c_str());
        system(("cd /tmp && cd " + repository + " && git sparse-checkout set " + package).c_str());
        system(("cd /tmp && cd " + repository + " && git pull origin main").c_str());
        system(("cd /tmp && cd " + repository + "/" + package + " &&" + command).c_str()); 
        system(("cd /tmp && rm -rf " + repository).c_str());   

        std::ifstream packages("/etc/mint/pkgs.list");
        std::string line;
        bool exists=false;
        while (std::getline(packages, line)) {
            if (line == repository + "/" + package) {
                exists=true;
                break;
            }
        }

        if (!exists) {
            std::ofstream packages_out("/etc/mint/pkgs.list", std::ios::app);
            packages_out << repository << "/" << package << "\n";
            packages_out.close();
        }

        packages.close();
}

namespace Mint {
    inline void Info() {
        std::cout << COL_GREEN << R"(
        ⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣤⣄⣀⣀⡀⠀⠀⠀
        ⠀⠀⠀⠀⢀⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⠶
        ⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀
        ⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀
        ⣠⠞⠋⠉⠛⠻⠿⣿⣿⣿⠿⠟⠋⠀⠀⠀⠀⠀
       ⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
               Mint
 A simple & powerful package manager.
Version BETA-1.00

(C) realbxnnie, 2025
)" << COL_RESET;
exit(0);
}
    inline void Usage() {
        std::cout << R"(
Usage:
    
COMMANDS
    install <category>/<pkgName>     Install a package
    purge   <category>/<pkgName>     Remove a package
    update                           Update a package or update the repositories
    list                             List packages installed on your system
    help                             Display this message
    info                             Display program info
ARGUMENTS
    --yes     -y     Don't ask Y/n
        )";
        exit(0);
    }

    inline void List() {
        std::ifstream packages("/etc/mint/pkgs.list");
        std::string line;
        while (std::getline(packages, line)) {
            std::cout << line << "\n";
        }

        packages.close();
        exit(0);
    }

    inline int Install(std::vector<std::string> packages) {
        for(std::string data : packages) {
            if (data.find("/") == std::string::npos) { Mint::Usage(); exit(1); }
            mintPkgOperation(data, "make.makemint");
        }

        exit(0);
        return 0;
    }

    inline int Update() {
        std::ifstream packages("/etc/mint/pkgs.list");
        std::string data;
        mintAskOnPkgOperation=false;
        while (std::getline(packages, data)) {
            mintPkgOperation(data, "destroy.makemint");
            mintPkgOperation(data, "make.makemint");
        }

        packages.close();
        exit(0);
        return 0;
    }

    inline int Remove(std::vector<std::string> packages) {
        for(std::string data : packages) {
            if (data.find("/") == std::string::npos) { Mint::Usage(); exit(1); }
          mintPkgOperation(data, "destroy.makemint");
        }

        exit(0);
        return 0;
    }
}
