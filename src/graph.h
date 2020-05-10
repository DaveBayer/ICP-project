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
    float TrafficCoef;
    uint32_t pt_idx;
    
    std::vector<std::pair<Point, uint32_t>> nodes;
    std::vector<std::vector<std::pair<float, float>>> adj_mat;
    
    void init();
public:

    std::map<uint32_t, std::vector<std::vector<Point>>> line_pts;
    std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> cs;
    Graph();
    Graph(std::vector<Street> &);
    Graph(std::vector<Street> &, std::vector<Station> &);

    uint32_t getNodeID(Point);
    Point getNodePoint(uint32_t);
    void addNode(uint32_t, Point);
    void addNodes(uint32_t, std::vector<Point>);

    void createEdges();
    float getEdgeW(Point, Point);
    void setEdgeW(uint32_t, uint32_t, float);
    void resetEdgeW(uint32_t, uint32_t);

    float getTC();
    void setTC(float);
    float getEdgeTC(uint32_t, uint32_t);
    float getEdgeTC(Point, Point);
    void incEdgeTC(uint32_t, uint32_t);

    void SetUpLine(uint32_t, std::vector<Point>);
    bool getPath(Point, Point, std::vector<Point> &);

    friend std::ostream &operator<<(std::ostream &, Graph);

    ~Graph();
};

#endif  //  __GRAHP_H__