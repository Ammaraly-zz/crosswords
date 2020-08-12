#define CW_DEBUG 1
#if CW_DEBUG == 1
#define LOG(x) std::cout << "[LOG] " << x << '\n'
#define ERROR(x) std::cout << "[ERROR] " << x << '\n'
#else
#define LOG(x)
#define ERROR(x)
#endif

#include<iostream>
#include <unistd.h>
#include<fstream>
#include<vector>

int main(int argc, char* argv[]) {
     bool filecheck = access(argv[1], F_OK);
     std::ifstream wordListFile;
     std::vector<std::string> wordList;
     std::string line;

     if(!filecheck) {
         std::cout << "[LOG] FILE EXISTS\n";
         wordListFile.open(argv[1]);
     }
     else {
         std::cout << "[ERROR] NO SUCH FILE!\n";
         return 69;
     }
     while(std::getline(wordListFile,line)) {
         wordList.push_back(line);
     }

     for(std::string word : wordList) {
         LOG(word);
     }
     return 0;
}