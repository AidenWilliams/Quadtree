//
// Created by aiden on 23/11/2020.
//
//https://www.geeksforgeeks.org/quad-tree/

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include <vector>
#include <iostream>
/*
 * Simple vector of 2 struct, including some mathematical functions.
 */
 struct Vector
{
 private:
    int x,y;

 public:
    explicit Vector(int x = 0, int y = 0): x(x), y(y){};

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    Vector operator +(Vector) const;
    Vector operator -(Vector) const;
    Vector operator >>(Vector) const;
    Vector operator <<(Vector) const;
    //Multiplying/ Dividing a vector by a constant
    Vector operator *=(int) const;
    Vector operator /=(int) const;

     //TODO: * and /
};

struct Data
{
private:
    Vector pos;
public:
    bool load;
    explicit Data(Vector pos, bool data = false): pos(pos), load(data){};

    [[nodiscard]] const Vector &getPos() const;
};

struct Node
{
private:
    //x and y points
    Vector centre;
    //distance from centre to edge, x = width, y = height
    Vector halfSize;

public:
    explicit Node(Vector centre = Vector(), Vector halfSize = Vector()): centre(centre), halfSize(halfSize){};
    //Below functions' return should be used for something
    //do not modify the Node instance they are called with. so can be made const
    [[nodiscard]] bool contains(Vector a) const;

    //Pass by reference since I wont be modifying this
    [[nodiscard]] bool intersects(Node& other) const;

    [[nodiscard]] const Vector &getCentre() const;
    [[nodiscard]] const Vector &getHalfSize() const;

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
    bool divided;
    //Quadtree<T>();
    //explicit Quadtree<T>(Node boundary);
    Quadtree();
    explicit Quadtree(Node boundary);

    ~Quadtree();

    bool insert(Data d);
    void subdivide();
    std::vector<Data> queryRange(Node range);


};

#endif //QUADTREE_QUADTREE_H
