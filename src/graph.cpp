
#include "graph.h"

Graph::Graph()
: pt_idx(0){}

Graph::Graph(std::vector<Street> &s)
{
    pt_idx = 0;

    for (auto i = s.begin(); i != s.end(); i++) {
        addNodes(i->getID(), i->getPoints());
    
        for (auto j = s.begin(); j != i; j++) {
            Point p;

            if (j->intersect(*i, p)) {
                addNode(i->getID(), p);
                addNode(i->getID(), p);
            }
        }
    }

    createEdges();
}

Graph::Graph(std::vector<Street> &streets, std::vector<Station> &stations)
{
    pt_idx = 0;

    for (auto i = streets.begin(); i != streets.end(); i++) {
        addNodes(i->getID(), i->getPoints());
    
        for (auto j = streets.begin(); j != i; j++) {
            Point p;

            if (j->intersect(*i, p)) {
                addNode(i->getID(), p);
                addNode(j->getID(), p);
            }
        }
    }

    for (auto i = stations.begin(); i != stations.end(); i++)
        addNode(i->getStreetID(), i->getPoint());

    createEdges();
}

uint32_t Graph::getNodeID(Point A)
{
    auto it = std::find_if(nodes.begin(), nodes.end(),
    [&A](auto &el) -> bool
    { return el.first == A; });

    if (it == nodes.end()) {
        std::cerr << "Node not find" << std::endl;
        exit(1);
    }

    return it->second;
}


Point Graph::getNodePoint(uint32_t idx)
{
    std::cout<<idx<<std::endl;
    auto it = std::find_if(nodes.begin(), nodes.end(),
    [&idx](auto &el) -> bool
    { return idx == el.second; });
    if (it == nodes.end()) {
        std::cerr << "Node not found\n";
        exit(1); 
    }

    return it->first;
}

void Graph::addNode(uint32_t sid, Point A)
{
    std::pair<Point, uint32_t> p;

    auto it_nd = std::find_if(nodes.begin(), nodes.end(),
        [&A](auto &el) -> bool
        { return el.first == A; });

    if (it_nd == nodes.end()) {
        p = std::make_pair(A, pt_idx++);
        nodes.push_back(p);
    } else
        p = *it_nd;
    
    auto it_cs = std::find_if(cs[sid].begin(), cs[sid].end(),
        [&A](auto &el) -> bool
        { return el.first == A; });

    if (it_cs == cs[sid].end())
        cs[sid].push_back(p);
}

void Graph::addNodes(uint32_t sid, std::vector<Point> v)
{
    for (auto i : v)
        addNode(sid, i);
}

void Graph::createEdges()
{
    adj_mat.resize(pt_idx);
    for (auto &i : adj_mat)
        i.resize(pt_idx);

    for (auto &i : cs) {
        std::vector<std::pair<Point, uint32_t>> &v = i.second;

        if (v.size() > 0) {
            Point P(v.front().first);

            std::sort(v.begin(), v.end(),
                [&P](auto &lhs, auto &rhs) -> bool
                { return lhs.first.dist(P) < rhs.first.dist(P); });

            for (auto j = 0; j < v.size() - 1; j++)
                setEdge(v[j].second, v[j+1].second, (v[j].first).dist(v[j+1].first));
        }
    }
}

void Graph::setEdge(uint32_t idx_a, uint32_t idx_b, float w)
{ 
    adj_mat[idx_a][idx_b] = w;
    adj_mat[idx_b][idx_a] = w;
}

void Graph::resetEdge(uint32_t idx_a, uint32_t idx_b)
{
    auto it1 = std::find_if(nodes.begin(), nodes.end(),
        [&idx_a](auto &el) -> bool
        { return idx_a == el.second; });
    
    auto it2 = std::find_if(nodes.begin(), nodes.end(),
        [&idx_b](auto &el) -> bool
        { return idx_b == el.second; });

    if (it1 == nodes.end() || it2 == nodes.end()) {
        std::cerr << "Edge cannot be reset: points not found\n";
        exit(1);
    }

    float dist = it1->first.dist(it2->first);

    setEdge(idx_a, idx_b, dist);
}

bool Graph::getPath(Point A, Point B, std::vector<Point> &path)
{
    uint32_t idx;
    auto getClosest = [](auto &lhs, auto &rhs)
        { return lhs.second < rhs.second; };
    
    auto findLast = [&idx](auto &el) -> bool
        { return idx == el.first.back(); };

    uint32_t src = getNodeID(A);
    uint32_t dst = getNodeID(B);

    std::list<std::pair<std::vector<uint32_t>, float>> open, close;
    std::list<std::pair<std::vector<uint32_t>, float>>::iterator it;

    open.push_back(make_pair(std::vector<uint32_t>{src}, 0.f));

    while (!open.empty()) {
        it = std::min_element(open.begin(), open.end(), getClosest);
        if (it->first.back() == dst)
            break;
        
        close.push_back(*it);
        idx = it->first.back();

        for (uint32_t i = 0; i < pt_idx; i++) {
            if (std::find_if(close.begin(), close.end(), findLast) != close.end() ||
                i == idx)
                continue;
            else {
                float f = it->second + adj_mat[idx][i];
                std::vector<uint32_t> v(it->first);
                
                if (f > 0) {
                    auto toDel = std::find_if(open.begin(), open.end(), findLast);
                    if (toDel != open.end() && f < toDel->second) {
                        open.erase(toDel);
                        v.push_back(i);
                        open.push_back(make_pair(v, f));
                    }
                }
            }
        }

        open.erase(it);
    }

    path.clear();
    for (auto &i : it->first)
        path.push_back(getNodePoint(i));

    return true;
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

std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> Graph::getMap()
{
    return this->cs;
}

Graph::~Graph(){}