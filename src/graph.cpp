#include "graph.h"

Graph::Graph(std::vector<Street> &s)
{
    pt_idx = 0;
    for (std::vector<Street>::iterator i = s.begin();
         i != s.end(); ++i) {
        std::vector pts = i->getPoints();
        addNodes(*i, pts);

        for (auto j = s.begin(); j != i; ++j) {
            Point p;
            if (Street::intersect(*j, *i, p)){
                addNode(*i,p);

                addNode(*j,p);
            }
        }
    }
    
    for (auto &i : cs) {
        Point p = i[0]->first;
        std::sort(i.begin(), i.end(), [p](const Point& lhs, const Point& rhs){ return p.dist(lhs) < p.dist(rhs); });
        
        for (auto j = 0; j < i.size() - 1; j++) {
            setEdge(i[j]->second, i[j+1]->second, (i[j]->first).dist(i[j+1]->first));
        }
    }
}

uint32_t Graph::getNode(Point A)
{
    auto it = std::find(nodes.begin(), nodes.end(), A);

    if (it == nodes.end()) {
        std::cerr << "Node not find" << std::endl;
        exit(1);
    }

    return std::distance(nodes.begin(), it);
}

void Graph::addNode(Street s, Point A) 
{
    auto id = s.getID();
    auto it = std::find(cs[id].begin(), cs[id].end(), A);

    if (it != cs[id].end()) {
        std::pair<Point, uint32_t> p(A, pt_idx++);
        nodes.push_back(p);
        cs[id].push_back(&nodes.back());
    }
}

void Graph::addNodes(Street s,std::vector<Point> v)
{
    for (auto i : v)
        addNode(s,i);
}

void Graph::setEdge(uint32_t idx_a, uint32_t idx_b, float w)
{ 
    adj_mat[idx_a][idx_b] = w;
    adj_mat[idx_b][idx_a] = w;
}

void Graph::setOEdge(uint32_t idx_a, uint32_t idx_b, float w) 
{
    adj_mat[idx_a][idx_b] = w;
}
