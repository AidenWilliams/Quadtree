//
// Created by aiden on 23/11/2020.
//

#include "QuadTree.h"
///*
// * Transforms Point by adding scalar to both x,y
// */
//Point Point::operator+(int rhs) const {
//    return Point(x + rhs, y + rhs);
//}
///*
// * Transforms Point by subtracting scalar to both x,y
// */
//Point Point::operator-(int rhs) const {
//    return Point(x - rhs, y - rhs);
//}
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

bool Node::intersects(Node& other) const
{
    //this right > that left                                          this left <s that right
    if(centre.x + halfSize.x > other.centre.x - other.halfSize.x || centre.x - halfSize.x < other.centre.x + other.halfSize.x)
    {
        // This bottom > that top
        if(centre.y + halfSize.y > other.centre.y - other.halfSize.y || centre.y - halfSize.y < other.centre.y + other.halfSize.y)
        {
            return true;
        }
    }
    return false;
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
}

//template <class T>
Quadtree::~Quadtree()
{
    delete nw;
    delete sw;
    delete ne;
    delete se;
}

//template <class T>
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

//template <class T>
bool Quadtree::insert(Data d)
{
    if(!boundary.contains(d.pos))
    {
        return false;
    }

    if(objects.size() < capacity)
    {
        objects.push_back(d);
        return true;
    }

    if(nw == nullptr)
    {
        subdivide();
    }

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

//template <class T>
std::vector<Data> Quadtree::queryRange(Node range)
{
    std::vector<Data> pInRange = std::vector<Data>();

    if(!boundary.intersects(range))
    {
        return pInRange;
    }

    for(auto&& object: objects)
    {
        if(range.contains(object.pos))
        {
            pInRange.push_back(object);
        }
    }

    if(nw == nullptr)
    {
        return pInRange;
    }

    std::vector<Data> temp = nw->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    temp = ne->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    temp = sw->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    temp = se->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());

    return pInRange;
}
