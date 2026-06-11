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

    void play() {
        std::vector<std::string> words = letterWords();
        
        // Print the first five words
        std::cout << "[";
        for (int i = 0; i < 5; ++i) {
            std::cout << words[i];
            if (i < 4) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;


        // Print the last five words
        std::cout << "[";
        for (int i = words.size() - 6; i < words.size() - 1; ++i) {
            std::cout << words[i];
            if (i < words.size() - 2) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
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

};


int main() {
    WordleSolver solver;
    solver.play();

    return 0;
}