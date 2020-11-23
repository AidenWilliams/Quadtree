#include <iostream>
#include <cmath>
#include <fstream>
#include <filesystem>

//https://www.geeksforgeeks.org/find-whether-a-given-number-is-a-power-of-4-or-not/
// returns true if n is power of four
bool powerof4(unsigned n)
{
    // find log4(n)
    double i = log(n) / log(4);

    // return true if log4(n) is an integer
    return i == trunc(i);
}

int main(int argc, char* args[]) {
    std::fstream input;
    bool isTxt;
    char ch;
    int width = 0, height = 0;

    if(argc != 2){
        std::cout << "Program requires argument for file to open!" << std::endl;
        exit(EXIT_FAILURE);
    }

    isTxt = std::string (args[1]).back() == 't';

    std::filesystem::path inputDirectory = std::filesystem::current_path() / args[1];
    std::string s = inputDirectory.string();
    if(isTxt){
        input.open(inputDirectory.string(), std::ios::in);

        if (!input) {
            perror ("Error encountered: ");
            exit(EXIT_FAILURE);
        }
        //Verify input is a square and x^4
        while (true) {
            input >> ch;
            if (input.eof()) break;

            if(height == 0) ++width;

            if(ch == '\n') ++height;
        }

        if(width != height){
            std::cout << "Program input must be a square!" << std::endl;
            exit(EXIT_FAILURE);
        }

        if(powerof4(++width)){
            std::cout << "Program input width and height must conform to x^4" << std::endl;
            exit(EXIT_FAILURE);
        }



        input.close();
    }else{
        //iscsv
    }

    exit(EXIT_SUCCESS);
}
