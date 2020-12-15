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
    std::vector<Quad> quadTree;
    std::fstream input;
    bool isTxt;
    std::string line;
    int width = 0, height = 0;
    int previousWidth, sizeOfTree;


    //sizeOfTree could be a tree variable
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
            //change witch exception?
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
            //change witch exception
            exit(EXIT_FAILURE);
        }

        if(!powerof4(width)) {
            std::cout << "Program input width and height must conform to x^4" << std::endl;
            //change witch exception
            exit(EXIT_FAILURE);
        }
    }else{
        //iscsv
    }

    for(int i = -width; i < (width * width); i+=2){
        //Skip a line
        if(i % width == 0){
            i += width;
            if (i == width * width) break;
        }
        quadTree.emplace_back(Quad( &readFile.at(i),&readFile.at(i + 1),
                                    &readFile.at(i + width),&readFile.at(i + 1 + width)));

    }
    //calculate max size for quadtree
    int maxSize = 0;
    for(int i = quadTree.size(); i != 1; i/=4){
        maxSize += i;
    }
    int startOfPreviousTreeLevel = 0;
    //for(int j = 0; width != 1; j++){
    for(int j = width/8; j >= 0; --j){
        width /= 2;
        sizeOfTree = quadTree.size();
        int i = -width;
        do {
            if(i % width == 0){
                i += width;
                if (i == width * width) break;
            }
            quadTree.emplace_back(Quad( &quadTree.at(i + startOfPreviousTreeLevel),&quadTree.at(i + startOfPreviousTreeLevel + 1),
                                        &quadTree.at(i + width + startOfPreviousTreeLevel),&quadTree.at(i + width + startOfPreviousTreeLevel + 1)));
            //this depends on the previous tree level I think
            i += j;
        } while (j != 0 & i < pow(width, j));

        startOfPreviousTreeLevel = sizeOfTree;
    }


    exit(EXIT_SUCCESS);
}
