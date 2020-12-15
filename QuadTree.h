//
// Created by aiden on 23/11/2020.
//
//https://www.geeksforgeeks.org/quad-tree/

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include <cmath>

struct Point{
    int x;
    int y;
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    Point(){
        x = 0;
        y = 0;
    }
};

// The objects that we want stored in the quadtree
struct Node{
    Point pos;
    bool data;
    Node(Point pos, bool data){
        this->pos = pos;
        this->data = data;
    }
    Node(){
        data = false;
    }
};

class Quad {
    // Hold details of the boundary of this node
    Point topLeft;
    Point botRight;

    // Contains details of node
    //Node *n;
    Node *topLeftNode;
    Node *topRightNode;
    Node *botLeftNode;
    Node *botRightNode;

    // Children of this tree
    Quad *topLeftTree;
    Quad *topRightTree;
    Quad *botLeftTree;
    Quad *botRightTree;

public:
    Quad(){
        //n = nullptr;
        topLeftNode  = nullptr;
        topRightNode = nullptr;
        botLeftNode  = nullptr;
        botRightNode = nullptr;
        topLeftTree  = nullptr;
        topRightTree = nullptr;
        botLeftTree  = nullptr;
        botRightTree = nullptr;
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
    }

    Quad(Quad *topLeftQ, Quad *topRightQ, Quad *botLeftQ, Quad *botRightQ){
        //n = nullptr;
        topLeftNode  = nullptr;
        topRightNode = nullptr;
        botLeftNode  = nullptr;
        botRightNode = nullptr;
        topLeftTree  = topLeftQ;
        topRightTree = topRightQ;
        botLeftTree  = botLeftQ;
        botRightTree = botRightQ;
        topLeft = topLeftQ->topLeft;
        botRight = botRightQ->botRight;
    }
//Point topL, Point botR,
    Quad(Node *topLeftN, Node *topRightN, Node *botLeftN, Node *botRightN){
        //n = nullptr;
        topLeftNode  = topLeftN;
        topRightNode = topRightN;
        botLeftNode  = botLeftN;
        botRightNode = botRightN;
        topLeftTree  = nullptr;
        topRightTree = nullptr;
        botLeftTree  = nullptr;
        botRightTree = nullptr;
        topLeft = topLeftN->pos;
        botRight = botRightN->pos;
    }

    //~Quad();
    //since input is restricted to 4^x
    void generateTree(int);
    [[nodiscard]] bool inBoundary(Point) const;
    void compress(int);
};

#endif //QUADTREE_QUADTREE_H
