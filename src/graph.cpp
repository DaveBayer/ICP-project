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
        std::vector<std::pair<Point, uint32_t>> &v = i.second;

        if (v.size() > 0) {
//            std::cout << "sort\n";
            Point P(v.front().first);
            std::sort(v.begin(), v.end(),
                [&P](auto &lhs, auto &rhs) -> bool
                { return lhs.first.dist(P) < rhs.first.dist(P); });

//            std::cout << "done, lets set edges now\n";
            for (auto j = 0; j < v.size() - 1; j++) {
                setEdge(v[j].second, v[j+1].second, (v[j].first).dist(v[j+1].first));
            }
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
    std::pair<Point, uint32_t> p;
    auto id = s.getID();

    auto it_nd = std::find_if(nodes.begin(), nodes.end(),
        [&A](auto &el) -> bool
        { return el.first == A; });

    if (it_nd == nodes.end()) {
        p = std::make_pair(A, pt_idx++);
        nodes.push_back(p);
    } else
        p = *it_nd;
    
    auto it_cs = std::find_if(cs[id].begin(), cs[id].end(),
        [&A](auto &el) -> bool
        { return el.first == A; });

    if (it_cs == cs[id].end())
        cs[id].push_back(p);
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
/*
std::ostream &operator<<(std::ostream &os, Graph g)
{
    os.precision(2);
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
*/
std::ostream &operator<<(std::ostream &os, Graph g)
{
    for (auto i = 0; i < g.pt_idx; i++) {
        for (auto j = 0; j < g.pt_idx; j++) {
            if (g.adj_mat[i][j] > 0) {
                std::cout << g.nodes[i].first
                    << "\t" << g.nodes[j].first
                    << "\t\t" << g.adj_mat[i][j]
                    << std::endl;
            }
        }
    }
    return os;
}

Graph::~Graph(){}
