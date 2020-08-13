#define CW_DEBUG 0
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
#include <chrono>

namespace crosswords
{
    struct Timer
    {
        std::chrono::high_resolution_clock::time_point start, end;
        std::chrono::duration<float> duration;

        Timer()
        {
            start = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            float ms = duration.count() * 1000;
            std::cout << "[PROGRAM DURATION] " << ms << "ms\n";
        }
    };

    class wordList
    {
        std::array<std::array<std::vector<std::string>, 26>, 4> lists;

    public:
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
        const std::vector<std::string> &fetch(int listNo, char Letter) const
        {
            return lists[(listNo) % 4][(Letter - 65) % 26];
        }
    };

    class puzzle
    {
        char board[4][4];
        int fails = 0;
        time_t now = time(0);
        std::tm *date = localtime(&now);
        int puzzleSeed = date->tm_year * 100000 + date->tm_mon * 10000 + date->tm_mday * 1000;

    public:
        puzzle()
        {
            reset();
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

        int failedAttempts()
        {
            return fails;
        }

        void print()
        {
            std::cout << "[DATE: " << date->tm_mday << '-'
                      << date->tm_mon << '-' << date->tm_year + 1900 << "]\n";
            std::cout << '\n';
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << board[i][j];
                }
                std::cout << '\n';
            }
            std::cout << '\n';
        }

        void toFile(std::string fileName)
        {
            std::ofstream myFile(fileName);
            myFile << '\n';
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    myFile << board[i][j];
                }
                myFile << '\n';
            }
            myFile << '\n';
        }

        int populateRow(int R, const wordList &inList)
        {
            bool filledColumns[4] = {0, 0, 0, 0};
            int C[4] = {-1, -1, -1};
            int sum = 0;
            for (int i = 0; i < 4; i++)
            {
                filledColumns[i] = board[R][i] != ' ';
                if (filledColumns[i])
                {
                    C[sum] = i;
                    sum++;
                }
            }
            sum = 0;
            for (int i = 0; i < 4; i++)
            {
                sum += filledColumns[i];
            }
            switch (sum)
            {
            case 0:
                return addRow(R, inList, 0);
            case 1:
                return addRow(R, inList, C[0]);
            case 2:
                return addRow(R, inList, C[0], C[1]);
            case 3:
                return addRow(R, inList, C[0], C[1], C[2]);
            case 4:
                return checkRow(R, inList);
            default:
                return 0;
            }
        }

        int populateColumn(int C, const wordList &inList)
        {
            bool filledRows[4] = {0, 0, 0, 0};
            int R[4] = {-1, -1, -1};
            int sum = 0;
            for (int i = 0; i < 4; i++)
            {
                filledRows[i] = board[i][C] != ' ';
                if (filledRows[i])
                {
                    R[sum] = i;
                    sum++;
                }
            }
            sum = 0;
            for (int i = 0; i < 4; i++)
            {
                sum += filledRows[i];
            }
            switch (sum)
            {
            case 0:
                return addColumn(C, inList, 0);
            case 1:
                return addColumn(C, inList, R[0]);
            case 2:
                return addColumn(C, inList, R[0], R[1]);
            case 3:
                return addColumn(C, inList, R[0], R[1], R[2]);
            case 4:
                return checkColumn(C, inList);
            default:
                return 0;
            }
        }

    private:
        bool addRow(int R, const wordList &inList, int A)
        {
            char B = board[R][A];
            if (B == ' ')
            {
                B = (puzzleSeed + fails) % 26 + 65;
            }
            auto fetched = inList.fetch(A, B);
            if (fetched.empty())
            {
                fails++;
                return 0;
            }
            setRow(R, fetched[(puzzleSeed + fails) % fetched.size()]);
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
                fails++;
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
                fails++;
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
                B = (puzzleSeed + fails) % 26 + 65;
            }
            auto fetched = inList.fetch(A, B);
            if (fetched.empty())
            {
                fails++;
                return 0;
            }
            setColumn(C, fetched[(puzzleSeed + fails) % fetched.size()]);
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
                fails++;
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
                fails++;
                return 0;
            }
            setColumn(C, S);
            return 1;
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

        bool checkColumn(int C, const wordList &inList)
        {
            std::string S;
            for (int i = 0; i < 4; i++)
            {
                S[i] = board[i][C];
            }
            S[4] = '\0';
            auto fetched = inList.fetch(0, S[0]);
            for (auto word : fetched)
            {
                if (word == S)
                {
                    return 1;
                }
            }
            fails++;
            return 0;
        }

        bool checkRow(int R, const wordList &inList)
        {
            std::string S;
            for (int i = 0; i < 4; i++)
            {
                S += board[R][i];
            }
            S[4] = '\0';
            auto fetched = inList.fetch(0, S[0]);
            for (auto word : fetched)
            {
                if (word == S)
                {
                    return 1;
                }
            }
            fails++;
            return 0;
        }
    };

    puzzle generatePuzzle(const wordList &inList)
    {
        auto Norm = [](int a) { return abs(a % 4); };
        bool check = true;
        int R = 2;
        puzzle myPuzzle;
        while (check)
        {
            myPuzzle.reset();
            if ((myPuzzle.populateRow(R, inList) &&
                 myPuzzle.populateColumn(Norm(R + 3), inList) &&
                 myPuzzle.populateRow(Norm(R + 1), inList) &&
                 myPuzzle.populateColumn(Norm(R + 2), inList) &&
                 myPuzzle.populateRow(Norm(R + 2), inList) &&
                 myPuzzle.populateColumn(Norm(R + 1), inList) &&
                 myPuzzle.populateColumn(R, inList) &&
                 myPuzzle.populateRow(Norm(R + 3), inList)))
                check = false;
            if (myPuzzle.failedAttempts() >= 1000)
            {
                std::cout << "[Failed]\n";
                return myPuzzle;
            }
        }
        std::cout << "[Successful]\n";
        return myPuzzle;
    }
}; // namespace crosswords

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Crossword 4x4 Puzzle Generator V1.0\nUsage: ./crosswords [file.txt]\n";
        return 1;
    }
    crosswords::Timer _Timer;
    bool filecheck = access(argv[1], F_OK);
    std::ifstream wordListFile;
    std::string line;

    if (!filecheck)
    {
        LOG("FILE EXISTS");
        wordListFile.open(argv[1]);
    }
    else
    {
        std::cout << "[ERROR] NO SUCH FILE!\n";
        return 2;
    }
    crosswords::wordList splitWordList(wordListFile);
    crosswords::puzzle FourCross = crosswords::generatePuzzle(splitWordList);
    FourCross.print();
    FourCross.toFile("Output.txt");
    return 0;
}