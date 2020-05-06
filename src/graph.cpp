#include "graph.h"

Graph::Graph()
: pt_idx(0){}

Graph::Graph(std::vector<Street> &s)
{
    pt_idx = 0;

    for (auto i = s.begin(); i != s.end(); ++i) {
        addNodes(*i, i->getPoints());

        for (auto j = s.begin(); j != i; ++j) {
            Point p;

            if (j->intersect(*i, p)){
                addNode(*i,p);
                addNode(*j,p);
            }
        }
    }
    
    adj_mat.resize(pt_idx);
    for (auto &i : adj_mat)
        i.resize(pt_idx);

    std::cout << "Lets create edges\n";
    for (auto &i : cs) {
        Point P(i.front()->first);
        std::sort(i.begin(), i.end(),
            [&P](auto &lhs, auto &rhs) -> bool
            { return lhs->first.dist(P) < rhs->first.dist(P); });

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

    auto it = std::find_if(nodes.begin(), nodes.end(),
        [&A](std::pair<Point, uint32_t> &el) -> bool
        { return el.first == A; });

    if (it == nodes.end()) {
        std::pair<Point, uint32_t> p({A, pt_idx++});
        std::cout << "new pair: " << p.first.getX() << p.first.getY() << p.second << std::endl;
        nodes.push_back(p);
    }

    if (id + 1 > cs.size())
        cs.resize(id + 1);

    cs[id].push_back(&(nodes.back()));
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

std::ostream &operator<<(std::ostream &os, Graph g)
{
    uint32_t size = g.adj_mat.size();
    for (auto i = 0; i < size; i++)
        os << "\t" << i;
    os << std::endl;

    for (auto i = 0; i < size; i++) {
        os << i;

        for (auto j = 0; j < size; j++)
            os << "\t" << g.adj_mat[i][j];
            
        os << std::endl;
    }

    return os;
}

Graph::~Graph(){}
