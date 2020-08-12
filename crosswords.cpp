#include<iostream>
#include <unistd.h>
#include<fstream>

int main(int argc, char* argv[]) {
     bool filecheck = access(argv[1], F_OK);
     if(!filecheck) {
         std::cout << "[LOG] FILE EXISTS\n";
     }
     else {
         std::cout << "[ERROR] NO SUCH FILE!\n";
         return 69;
     }
     return 0;
}