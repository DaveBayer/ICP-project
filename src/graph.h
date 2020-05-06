#ifndef __GRAPH_H__
#define __GRAPH_H__

//#include <algorithm>
#include <vector>
#include <iostream>

#include "point.h"
#include "street.h"

class Graph
{
private:
    uint32_t pt_idx;
    std::vector<std::vector<std::pair<Point, uint32_t> *>> cs;
    std::vector<std::pair<Point, uint32_t>> nodes;
    std::vector<std::vector<float>> adj_mat;
public:
    Graph();
    Graph(std::vector<Street> &);

//    uint32_t getNode(Point);
    void addNode(Street, Point);
    void addNodes(Street, std::vector<Point>);
    
    void setEdge(uint32_t idx_a, uint32_t idx_b, float w);
    void setOEdge(uint32_t idx_a, uint32_t idx_b, float w);



    ~Graph();
};

#endif  //  __GRAHP_H__
