#include <iostream>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <vector>
#include "QuadTree.h"
#include <string>

//https://www.geeksforgeeks.org/find-whether-a-given-number-is-a-power-of-4-or-not/
// returns true if n is power of four
bool powerof4(unsigned n){
    // find log4(n)
    double i = log(n) / log(4);

    // return true if log4(n) is an integer
    return i == trunc(i);
}

int main(int argc, char* args[]) {
    std::vector<Data> readFile;
    //std::vector<Quad> quadTree;
    //Quadtree* quadtree;
    std::fstream input;
    bool isTxt;
    std::string line;
    int width = 0, height = 0;


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
                //readFile.emplace_back(Node(Point(width++,height),c == 'T'));
                readFile.emplace_back(Data(Point(width++,height),c == 'T'));
            }
            ++height;
        }

        input.close();
    }else{
        input.open(inputDirectory.string(), std::ios::in);
        if (!input) {
            perror ("Error encountered: ");
            //change witch exception?
            exit(EXIT_FAILURE);
        }

        while (input >> line){
            std::stringstream s(line);
            int i = 0;
            std::string word;
            int t[] = {0,0};
            while(getline(s, word, 's')){
                t[i++] = std::stoi(word);
            }

            readFile.emplace_back(Data(Point(t[0],t[1]),true));
        }
    }

    auto* root =  new Quadtree(Node(
                            Point(width/2 -1, height/2 -1),
                            Point(width/2, width/2)));

    for(auto data: readFile){
        //root->insert(data);
        if(data.load) root->insert(data);
    }
    root->print();
    exit(EXIT_SUCCESS);
}
