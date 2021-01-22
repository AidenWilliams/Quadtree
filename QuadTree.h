//
// Created by aiden on 23/11/2020.
//
//https://www.geeksforgeeks.org/quad-tree/

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include <vector>
#include <iostream>

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

struct Node
{
    Point centre;
    Point halfSize;

    explicit Node(Point centre = Point(), Point halfSize = Point()): centre(centre), halfSize(halfSize){};
    //do not modify the Node instance they are called with. so can be made const
    [[nodiscard]] bool contains(Point a) const;

    //Pass by reference since I wont be modifying this
    [[nodiscard]] bool intersects(Node& other) const;
};

struct Data
{
    Point pos;
    bool load;

    explicit Data(Point pos = {}, bool data = false): pos(pos), load(data){};
};


//template <class T>
class Quadtree
{
private:
    //4 children
    Quadtree* nw;
    Quadtree* ne;
    Quadtree* sw;
    Quadtree* se;
    Node boundary;

    std::vector<Data> objects;
    //Changes how much data can be stored on one leaf
    static constexpr int capacity = 1;
public:
    //Quadtree<T>();
    //explicit Quadtree<T>(Node boundary);
    Quadtree();
    explicit Quadtree(Node boundary);

    ~Quadtree();

    bool insert(Data d);
    void subdivide();
    std::vector<Data> queryRange(Node range);
    void print(int indent=0);
};

#endif //QUADTREE_QUADTREE_H
