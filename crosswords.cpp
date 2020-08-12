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
         std::cout << "[" << word << "]\n";
     }
     return 0;
}