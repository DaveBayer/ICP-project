#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <algorithm>
#include <limits>
#include <map>
#include <vector>
#include <list>
#include <iostream>

#include "error.h"
#include "point.h"
#include "street.h"
#include "station.h"
#include "line.h"

class Graph
{
private:
    uint32_t pt_idx;
    std::map<uint32_t, std::vector<std::vector<Point>>> line_pts;
    std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> cs;
    std::vector<std::pair<Point, uint32_t>> nodes;
    std::vector<std::vector<float>> adj_mat;
    
    void init();
public:
    Graph();
    Graph(std::vector<Street> &);
    Graph(std::vector<Street> &, std::vector<Station> &);

    uint32_t getNodeID(Point);
    Point getNodePoint(uint32_t);
    void addNode(uint32_t, Point);
    void addNodes(uint32_t, std::vector<Point>);

    void createEdges();
    void setEdge(uint32_t, uint32_t, float);
    void resetEdge(uint32_t, uint32_t);

    void SetUpLine(uint32_t, std::vector<Point>);
    bool getPath(Point, Point, std::vector<Point> &);

    friend std::ostream &operator<<(std::ostream &, Graph);

    ~Graph();
};

#endif  //  __GRAHP_H__
