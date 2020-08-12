#define CW_DEBUG 1
#if CW_DEBUG == 1
#define LOG(x) std::cout << "[LOG] " << x << '\n'
#define ERROR(x) std::cout << "[ERROR] " << x << '\n'
#else
#define LOG(x)
#define ERROR(x)
#endif

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <array>

namespace crosswords
{
    class wordList
    {
    public:
        std::array<std::array<std::vector<std::string>, 26>, 4> lists;
        wordList(std::ifstream &file)
        {
            std::string line;
            while (std::getline(file, line))
            {
                for (int i = 0; i < 4; i++)
                {
                    lists[i][line[i] - 65].push_back(line);
                }
            }
        }
                ~wordList()
        {
            LOG("wordList Destroyed!");
        }

        const std::vector<std::string> &fetch(int listNo, char Letter) const
        {
            return lists[(listNo - 1) % 4][(Letter - 65) % 26];
        }
    };

    class puzzle
    {
        char board[4][4];

    public:
        puzzle()
        {
            reset();
        }

        ~puzzle()
        {
            LOG("Puzzle Destroyed!");
        }

        void reset()
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    board[i][j] = ' ';
                }
            }
        }

        void setRow(int R, std::string S)
        {
            for (int i = 0; i < 4; i++)
            {
                board[R][i] = S[i];
            }
        }
        void setColumn(int C, std::string S)
        {
            for (int i = 0; i < 4; i++)
            {
                board[i][C] = S[i];
            }
        }
    };
}; // namespace crosswords

int main(int argc, char *argv[])
{
    bool filecheck = access(argv[1], F_OK);
    std::ifstream wordListFile;
    std::string line;

    if (!filecheck)
    {
        std::cout << "[LOG] FILE EXISTS\n";
        wordListFile.open(argv[1]);
    }
    else
    {
        std::cout << "[ERROR] NO SUCH FILE!\n";
        return 69;
    }
    crosswords::wordList splitWordList(wordListFile);
    crosswords::puzzle FourCross; 
    return 0;
}