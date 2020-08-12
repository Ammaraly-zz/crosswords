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
        int puzzleSeed;

    public:
        puzzle(int P) : puzzleSeed(P)
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

        bool addRow(int R, const wordList &inList, int A)
        {
            char B = board[R][A];
            if (B == ' ')
            {
                B = puzzleSeed % 26 + 65;
            }
            auto fetched = inList.fetch(A, B);
            if (fetched.empty())
            {
                return 0;
            }
            setRow(R, fetched[puzzleSeed % fetched.size()]);
            return 1;
        }

        bool addRow(int R, const wordList &inList, int A, int A1)
        {
            char B = board[R][A];
            char B1 = board[R][A1];
            auto fetched = inList.fetch(A, B);
            std::string S = "";
            for (auto word : fetched)
            {
                if (word[A1] == B1)
                {
                    LOG("addRow(R,A,A1) " + word);
                    S = word;
                    break;
                }
            }
            if (S == "")
            {
                return 0;
            }
            setRow(R, S);
            return 1;
        }

        bool addRow(int R, const wordList &inList, int A, int A1, int A2)
        {
            char B = board[R][A];
            char B1 = board[R][A1];
            char B2 = board[R][A2];
            auto fetched = inList.fetch(A, B);
            std::vector<std::string> S_fetched;
            for (auto word : fetched)
            {
                if (word[A1] == B1)
                {
                    S_fetched.push_back(word);
                }
            }
            std::string S = "";
            for (auto word : S_fetched)
            {
                if (word[A2] == B2)
                {
                    LOG("addRow(R,A,A1,A2) " + word);
                    S = word;
                    break;
                }
            }
            if (S == "")
            {
                return 0;
            }
            setRow(R, S);
            return 1;
        }

        bool addColumn(int C, const wordList &inList, int A)
        {
            char B = board[A][C];
            if (B == ' ')
            {
                B = puzzleSeed % 26 + 65;
            }
            auto fetched = inList.fetch(A, B);
            if (fetched.empty())
            {
                return 0;
            }
            setColumn(C, fetched[puzzleSeed % fetched.size()]);
            return 1;
        }

        bool addColumn(int C, const wordList &inList, int A, int A1)
        {
            char B = board[A][C];
            char B1 = board[A1][C];
            auto fetched = inList.fetch(A, B);
            std::string S = "";
            for (auto word : fetched)
            {
                if (word[A1] == B1)
                {
                    LOG("addColumn(C,A,A1) " + word);
                    S = word;
                    break;
                }
            }
            if (S == "")
            {
                return 0;
            }
            setColumn(C, S);
            return 1;
        }

        bool addColumn(int C, const wordList &inList, int A, int A1, int A2)
        {
            char B = board[A][C];
            char B1 = board[A1][C];
            char B2 = board[A2][C];
            auto fetched = inList.fetch(A, B);
            std::vector<std::string> S_fetched;
            for (auto word : fetched)
            {
                if (word[A1] == B1)
                {
                    S_fetched.push_back(word);
                }
            }
            std::string S = "";
            for (auto word : S_fetched)
            {
                if (word[A2] == B2)
                {
                    LOG("addColumn(C,A,A1,A2) " + word);
                    S = word;
                    break;
                }
            }
            if (S == "")
            {
                return 0;
            }
            setColumn(C, S);
            return 1;
        }

    private:
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
    crosswords::puzzle FourCross(0);
    return 0;
}