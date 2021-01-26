//
// Created by aiden on 23/11/2020.
//

#include "QuadTree.h"
/*
 * Transforms Point by adding scalar to both x,y
 */
Point Point::operator+(int rhs) const {
    return Point(x + rhs, y + rhs);
}
/*
 * Transforms Point by subtracting scalar to both x,y
 */
Point Point::operator-(int rhs) const {
    return Point(x - rhs, y - rhs);
}
/*
 * Add x and y values of points
 */
Point Point::operator+(Point rhs) const {
    return Point(x + rhs.x, y + rhs.y);
}
/*
 * Subtracts x and y values of points
 */
Point Point::operator-(Point rhs) const {
    return Point(x - rhs.x, y - rhs.y);
}
/*
 * Adds x values points but subtracts y values
 */
Point Point::operator>>(Point rhs) const {
    return Point(x + rhs.x, y - rhs.y);
}
/*
 * Subtracts x values points but adds y values
 */
Point Point::operator<<(Point rhs) const {
    return Point(x - rhs.x, y + rhs.y);
}
/**
 * Returns whether a node contains point a in it or not
 * @param a the point that could be in the Node
 * @return true if point a is in node
 */
bool Node::contains(Point a) const {
    if(a.x < centre.x + halfSize.x && a.x > centre.x - halfSize.x)
    {
        if(a.y < centre.y + halfSize.y && a.y > centre.y - halfSize.y)
        {
            return true;
        }
    }
    return false;
}

Quadtree::Quadtree()
{
    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    boundary = Node();
    objects = std::vector<Data>();
}

Quadtree::Quadtree(Node boundary)
{
    objects = std::vector<Data>();
    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    this->boundary = boundary;
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
    Point qSize = boundary.halfSize;

    Point qCentre = boundary.centre - qSize;
    nw = new Quadtree(Node(qCentre, qSize));

    qCentre = boundary.centre >> qSize;
    ne = new Quadtree(Node(qCentre, qSize));

    qCentre = boundary.centre << qSize;
    sw = new Quadtree(Node(qCentre, qSize));

    qCentre = boundary.centre + qSize;
    se = new Quadtree(Node(qCentre, qSize));
}
/**
 * Inserts data d into the tree
 * @param d Data to be inserter
 * @return if insertion was successful or not
 */
bool Quadtree::insert(Data d)
{
    //if d is not within the boundary of this, return
    if(!boundary.contains(d.pos))
    {
        return false;
    }
    //if there is space in the tree then add d
    if(objects.size() < capacity)
    {
        objects.push_back(d);
        return true;
    }
    //If the tree hasn't been subdivided yet, subdivide it
    if(nw == nullptr)
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
        std::cout << "Pos " << data.pos.x << ", "<< data.pos.x << " data: " << data.load << std::endl;
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
        se->print(indent++);
}
