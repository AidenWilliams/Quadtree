#include <iostream>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <vector>
#include "QuadTree.h"

//https://www.geeksforgeeks.org/find-whether-a-given-number-is-a-power-of-4-or-not/
// returns true if n is power of four
bool powerof4(unsigned n){
    // find log4(n)
    double i = log(n) / log(4);

    // return true if log4(n) is an integer
    return i == trunc(i);
}

int main(int argc, char* args[]) {
    std::vector<Node> readFile;
    std::fstream input;
    bool isTxt;
    std::string line;
    int width = 0, height = 0;

    if(argc != 2){
        std::cout << "Program requires argument for file to open!" << std::endl;
        exit(EXIT_FAILURE);
    }

    isTxt = std::string (args[1]).back() == 't';

    std::filesystem::path inputDirectory = std::filesystem::current_path() / args[1];

    if(isTxt){
        input.open(inputDirectory.string(), std::ios::in);

        if (!input) {
            perror ("Error encountered: ");
            exit(EXIT_FAILURE);
        }

        while (std::getline(input, line)){
            width = 0;
            for(auto c : line){
                readFile.emplace_back(Node(Point(width++,height),c == 'T'));
            }
            ++height;
        }

        input.close();

        if(width != height){
            std::cout << "Program input must be a square!" << std::endl;
            exit(EXIT_FAILURE);
        }

        if(powerof4(width)){
            std::cout << "Program input width and height must conform to x^4" << std::endl;
            exit(EXIT_FAILURE);
        }

        Quad *Q = new Quad();


    }else{
        //iscsv
    }

    exit(EXIT_SUCCESS);
}
