//
// Created by aiden on 23/11/2020.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include <vector>
#include <iostream>
/**
 * A point struct containing two integers
 */
struct Point
{
    int x,y;

    Point(int x = 0, int y = 0):x(x), y(y){};

    Point operator +(int) const;
    Point operator -(int) const;
    Point operator +(Point) const;
    Point operator -(Point) const;
    Point operator >>(Point) const;
    Point operator <<(Point) const;
};
/**
 * A node in a tree contains a centre point as well as a halfSize 2d vector (represented by a point)
 */
struct Node
{
    Point centre;
    Point halfSize;

    explicit Node(Point centre = Point(), Point halfSize = Point()): centre(centre), halfSize(halfSize){};
    //do not modify the Node instance they are called with. so can be made const
    [[nodiscard]] bool contains(Point a) const;
};
/**
 * A data struct that has a Point pos holding its position and bool load being its value
 */
struct Data
{
    Point pos;
    bool load;

    explicit Data(Point pos = {}, bool data = false): pos(pos), load(data){};
};


/**
 * A quadtree has 4 quadtree children one in each corner of a square
 */
class Quadtree
{
private:
    //4 children
    Quadtree* nw;
    Quadtree* ne;
    Quadtree* sw;
    Quadtree* se;
    //Boundaries for the tree
    Node boundary;
    //In theory quadtrees can hold more than one data object in its boundaries
    std::vector<Data> objects;
    //Changes how much data can be stored on one leaf
    static constexpr int capacity = 1;
public:
    Quadtree();
    explicit Quadtree(Node boundary);

    ~Quadtree();
    //Inserts data d into the quadtree
    bool insert(Data d);
    //subdivides the tree into its four children
    void subdivide();
    //prints the tree to standard output
    void print(int indent=0);
};

#endif //QUADTREE_QUADTREE_H
