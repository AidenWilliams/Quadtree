//
// Created by aiden on 23/11/2020.
//
//https://www.geeksforgeeks.org/quad-tree/

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

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
    Node *n;

    // Children of this tree
    Quad *topLeftTree;
    Quad *topRightTree;
    Quad *botLeftTree;
    Quad *botRightTree;

public:
    Quad(){
        n = nullptr;
        topLeftTree  = nullptr;
        topRightTree = nullptr;
        botLeftTree  = nullptr;
        botRightTree = nullptr;
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
    }

    Quad(Point topL, Point botR){
        n = nullptr;
        topLeftTree  = nullptr;
        topRightTree = nullptr;
        botLeftTree  = nullptr;
        botRightTree = nullptr;
        topLeft = topL;
        botRight = botR;
    }

    void insert(Node*);

    Node* search(Point);

    [[nodiscard]] bool inBoundary(Point) const;
};


#endif //QUADTREE_QUADTREE_H
