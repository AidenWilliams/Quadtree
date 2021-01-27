//
// Created by aiden on 23/11/2020.
//

#include "QuadTree.h"
/*
 * Add x and y values of points
 */
Vector Vector::operator+(Vector rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}
/*
 * Subtracts x and y values of points
 */
Vector Vector::operator-(Vector rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}
/*
 * Adds x values points but subtracts y values
 */
Vector Vector::operator>>(Vector rhs) const {
    return Vector(x + rhs.x, y - rhs.y);
}
/*
 * Subtracts x values points but adds y values
 */
Vector Vector::operator<<(Vector rhs) const {
    return Vector(x - rhs.x, y + rhs.y);
}

Vector Vector::operator*=(int num) const {
    return Vector(x * num, y * num);
}

Vector Vector::operator/=(int num) const {
    return Vector(x / num, y / num);
}

int Vector::getX() const {
    return x;
}

int Vector::getY() const {
    return y;
}

const Vector &Data::getPos() const {
    return pos;
}
/**
 * Returns whether a node contains point a in it or not
 * @param a the vector that could be in the Node
 * @return true if point a is in node
 */
bool Node::contains(Vector a) const {
    return  a.getX() >= centre.getX() - halfSize.getX() &&
            a.getX() <= centre.getX() + halfSize.getX() &&
            a.getY() >= centre.getY() - halfSize.getY() &&
            a.getY() <= centre.getY() + halfSize.getY();
}

const Vector &Node::getCentre() const {
    return centre;
}

const Vector &Node::getHalfSize() const {
    return halfSize;
}

//template <class T>
Quadtree::Quadtree()
{
    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    boundary = Node();
    objects = std::vector<Data>();
    divided = false;
}

//template <class T>
Quadtree::Quadtree(Node boundary)
{
    objects = std::vector<Data>();
    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    this->boundary = boundary;
    objects = std::vector<Data>();
    divided = false;
}

Quadtree::~Quadtree()
{
    delete nw;
    delete sw;
    delete ne;
    delete se;
}
/**
 * Subdivide the quadtree into 4 new quadtrees
 */
void Quadtree::subdivide()
{
    Vector nCentre = boundary.getCentre();

    Vector nHalfSize = boundary.getHalfSize() /= 2;

    nw = new Quadtree(Node(Vector(nCentre - nHalfSize), nHalfSize));
    ne = new Quadtree(Node(Vector(nCentre >> nHalfSize), nHalfSize));
    sw = new Quadtree(Node(Vector(nCentre << nHalfSize), nHalfSize));
    se = new Quadtree(Node(Vector(nCentre + nHalfSize), nHalfSize));

    divided = true;
}
/**
 * Inserts data d into the tree
 * @param d Data to be inserter
 * @return if insertion was successful or not
 */
bool Quadtree::insert(Data d)
{
    //if d is not within the boundary of this, return
    if(!boundary.contains(d.getPos()))
    {
        return false;
    }
    //if there is space in the tree then add d
    if(objects.size() < capacity)
    {
        objects.push_back(d);
        return true;
    }

    if(!divided)
    {
        subdivide();
    }
    //Insert it in its place via recursion

    if(nw->insert(d))
    {
        return true;
    }
    if(ne->insert(d))
    {
        return true;
    }
    if(sw->insert(d))
    {
        return true;
    }
    if(se->insert(d))
    {
        return true;
    }

    return false;
}

/**
 * Print the QuadTree
 */
void Quadtree::print(int indent) {
    //Generate indentations
    for(int i = 0; i < indent; i++)
        std::cout << '\t';
    //Start outputting about the data at the current space in the tree
    std::cout << "Data: " << std::endl;
    for(auto data: objects){
        for(int i = 0; i < indent; i++)
            std::cout << '\t';
        std::cout << "Pos " << data.getPos().getX() << ", "<< data.getPos().getX() << " data: " << data.load << std::endl;
    }
    //indent further
    for(int i = 0; i < indent; i++)
        std::cout << '\t';
    //print the children trees
    std::cout << "Children: " << std::endl;
    if (nw != nullptr)
        nw->print(indent++);
    if (ne != nullptr)
        ne->print(indent++);
    if (sw != nullptr)
        sw->print(indent++);
    if (se != nullptr)
        se->print(indent);
}
