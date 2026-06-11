#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>


class WordleSolver {

private:
    std::vector<std::string> ignoreWords;
    std::vector<std::string> board;

public:
    void display(const std::vector<std::string> currentBoard) {
        std::cout << "[";
        for (size_t i = 0; i < currentBoard.size(); ++i) {
            std::cout << currentBoard[i];
            if (i < currentBoard.size() - 1) {
                std::cout << ", ";
            }
        }
    std::cout << "]";
    }

    void resetBoard() {
        board.clear();
        for (int i = 0; i < 5; ++i) {
            board.push_back("_");
        }
    }

    std::string getInput(std::string prompt) {
        std::cout << prompt << " ";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    int userEntry(int location) {
        std::string initialState = board[location];
        board[location] = "=";
        display(board);
        std::string userInput = getInput("");

        if (userInput == " " || userInput.empty()) {
            board[location] = initialState;
            return location + 1;
        } else if (userInput == "0") {
            board[location] = initialState;
            return 5;
        } else if (userInput == "1") {
            board[location] = "_";
            return std::max(location - 1, 0);
        } else {
            board[location] = userInput;
            return location + 1;
        }
    }

    void initializeBoard() {
        int i = 0;
        while (i < 5) {
            i = userEntry(i);
        }
        display(board);
        std::cout << std::endl;
    }

    std::vector<std::string> letterWords() {
        std::vector<std::string> rows;
        std::fstream file("Wordle_Solver/words.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                rows.push_back(line);
            }
            file.close();
        } else {
            std::cerr << "Unable to open file";
        }
        return rows;
    }

    std::vector<std::string> matcher(std::vector<std::string> bigList, std::vector<std::string> target) {
        std::vector<std::string> results;

        for (const std::string word : bigList) {
            bool isMatch = true;
            for (int i = 0; i < 5; i++) {
                if (target[i] != "_" && target[i] != std::string(1, word[i])) {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch) {
                results.push_back(word);
            }
        }

        return results;
    }

    void play() {
        std::string prompt = "Your current cell is marked with a '='.\n * Enter a letter if you know it belongs in that cell.\n * Enter a space if you want to skip to the next cell.\n * Enter '1' to move one cell back and make changes.\n * Enter '0' to exit the board editing process.";
        std::cout << prompt << std::endl;
        resetBoard();
        initializeBoard();
        std::vector<std::string> rows = letterWords();
        std::vector<std::string> results = matcher(rows, board);

        std::cout << "Here are the results of the matches:" << std::endl;
        if (results.empty()) {
                std::cout << "[]" << std::endl;
            } else {
                std::cout << "[";
                if (results.size() <= 10) {
                    for (size_t i = 0; i < results.size(); ++i) {
                        std::cout << results[i];
                        if (i < results.size() - 1) {
                            std::cout << ", ";
                        }
                    }
                } else {
                    for (size_t i = 0; i < 10; ++i) {
                        std::cout << results[i];
                        if (i < 9) {
                            std::cout << ", ";
                        }
                    }
                }
            std::cout << "]" << std::endl;
         }
     }

};


int main() {
    WordleSolver solver;
    solver.play();

    return 0;
}