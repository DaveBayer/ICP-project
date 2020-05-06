#include "graph.h"

Graph::Graph()
: pt_idx(0){}

Graph::Graph(std::vector<Street> &s)
{
    pt_idx = 0;
    for (std::vector<Street>::iterator i = s.begin(); i != s.end(); ++i) {

        addNodes(*i, i->getPoints());

        for (auto j = s.begin(); j != i; ++j) {
            Point p;
            if (j->intersect(*i, p)){
                addNode(*i,p);

                addNode(*j,p);
            }
        }
    }
    
    for (auto &i : cs) {
        /*
        std::sort(i.begin(), i.end(), [](auto lhs, auto rhs)
        { return lhs->first.getX() < rhs->first.getY(); });
        */
        for (auto j = 0; j < i.size() - 1; j++) {
            setEdge(i[j]->second, i[j+1]->second, (i[j]->first).dist(i[j+1]->first));
        }
    }
}
/*
uint32_t Graph::getNode(Point A)
{
    auto it = std::find_if(nodes.begin(), nodes.end(), [&A](const std::pair<Point, uint32_t>& el) -> bool
    { return el.first == A; });

    if (it == nodes.end()) {
        std::cerr << "Node not find" << std::endl;
        exit(1);
    }

    return std::distance(nodes.begin(), it);
}
*/
void Graph::addNode(Street s, Point A)
{
    auto id = s.getID();

    std::pair<Point, uint32_t> p(A, pt_idx++);
    nodes.push_back(p);
    cs[id].push_back(&nodes.back());
}

void Graph::addNodes(Street s, std::vector<Point> v)
{
    for (auto i : v)
        addNode(s, i);
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

Graph::~Graph(){}
