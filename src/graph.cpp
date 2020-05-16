/**
 * @file graph.cpp
 * @brief Tento soubor obsahuje implementace metod třídy Graph
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "graph.h"

Graph::Graph()
: pt_idx(0), TrafficCoef(.5f){}

/**
 * @param s vektor ulic pro vytvoření grafu
 */
Graph::Graph(std::vector<Street> &s)
{
    init();

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

/**
 * @param streets vektor ulic pro vytvoření grafu
 * @param stations vektor stanic
 */
Graph::Graph(std::vector<Street> &streets, std::vector<Station> &stations)
{
    init();

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

void Graph::init()
{
    cs.clear();
    nodes.clear();
    adj_mat.clear();
    TrafficCoef = .5f;
    pt_idx = 0;
}

/**
 * @param A první bod
 * @param B druhý bod
 * @return id ulice, na které body leží
 */
uint32_t Graph::getStreetFromPoints(Point A, Point B)
{
    uint32_t sid;
    bool exists = false;

    for (auto &i : cs) {
        auto it_a = std::find_if(i.second.begin(), i.second.end(),
            [&A](auto &el) -> bool
            { return A == el.first; });
        auto it_b = std::find_if(i.second.begin(), i.second.end(),
            [&B](auto &el) -> bool
            { return B == el.first; });
        
        if (it_a != i.second.end() && it_b != i.second.end()) {
            sid = i.first;
            exists = true;
            break;
        }   
    }

    if (!exists)
        errExit(1, "No street has both points");
    
    return sid;
}

/**
 * @param A bod k přeložení
 * @return index vrcholu
 */
uint32_t Graph::getNodeID(Point A)
{
    auto it = std::find_if(nodes.begin(), nodes.end(),
    [&A](auto &el) -> bool
    { return el.first == A; });

    if (it == nodes.end())
        errExit(1, "Node not found");

    return it->second;
}

/**
 * @param idx index vrcholu
 * @return souřadnice vrcholu
 */
Point Graph::getNodePoint(uint32_t idx)
{
    auto it = std::find_if(nodes.begin(), nodes.end(),
    [&idx](auto &el) -> bool
    { return idx == el.second; });
    if (it == nodes.end())
        errExit(1, "Node not found");

    return it->first;
}

/**
 * @param sid id ulice
 * @param A nový bod
 */
void Graph::addNode(uint32_t sid, Point A)
{
    auto findPoint = [&A](auto &el) -> bool
        { return el.first == A; };

    std::pair<Point, uint32_t> p;

    auto it_nd = std::find_if(nodes.begin(), nodes.end(), findPoint);

    if (it_nd == nodes.end()) {
        p = std::make_pair(A, pt_idx++);
        nodes.push_back(p);
    } else
        p = *it_nd;
    
    auto it_cs = std::find_if(cs[sid].begin(), cs[sid].end(), findPoint);

    if (it_cs == cs[sid].end())
        cs[sid].push_back(p);
}

/**
 * @param sid id ulice
 * @param v vektor bodů
 */
void Graph::addNodes(uint32_t sid, std::vector<Point> v)
{
    for (auto i : v)
        addNode(sid, i);
}

void Graph::createEdges()
{
    adj_mat.resize(pt_idx);
    for (auto &i : adj_mat) {
        i.resize(pt_idx);
        for (auto &j : i)
            j = std::make_pair(0.f, 1.f);
    }

    for (auto &i : cs) {
        std::vector<std::pair<Point, uint32_t>> &v = i.second;

        if (v.size() > 0) {
            Point P(v.front().first);

            std::sort(v.begin(), v.end(),
                [&P](auto &lhs, auto &rhs) -> bool
                { return lhs.first.dist(P) < rhs.first.dist(P); });

            for (uint32_t j = 0; j < v.size() - 1; j++)
                setEdgeW(v[j].second, v[j+1].second, (v[j].first).dist(v[j+1].first));
        }
    }
}

/**
 * @param sid id ulice
 */
void Graph::closeStreetEdges(uint32_t sid)
{
    for (uint32_t i = 0; i < cs[sid].size() - 1; i++)
        setEdgeW(cs[sid][i].second, cs[sid][i + 1].second,
                 std::numeric_limits<float>::infinity());
}

/**
 * @param A první bod
 * @param B druhý bod
 * @return délka hrany
 */
float Graph::getEdgeW(Point A, Point B)
{
    auto idx_a = getNodeID(A);
    auto idx_b = getNodeID(B);

    return adj_mat[idx_a][idx_b].first;
}

/**
 * @param idx_a první index vrcholu
 * @param idx_b druhý index vrcholu
 * @param w délka hrany
 */
void Graph::setEdgeW(uint32_t idx_a, uint32_t idx_b, float w)
{ 
    adj_mat[idx_a][idx_b].first = w;
    adj_mat[idx_b][idx_a].first = w;
}

/**
 * @param idx_a první index vrcholu
 * @param idx_b druhý index vrcholu
 */
void Graph::resetEdgeW(uint32_t idx_a, uint32_t idx_b)
{
    auto it1 = std::find_if(nodes.begin(), nodes.end(),
        [&idx_a](auto &el) -> bool
        { return idx_a == el.second; });
    
    auto it2 = std::find_if(nodes.begin(), nodes.end(),
        [&idx_b](auto &el) -> bool
        { return idx_b == el.second; });

    if (it1 == nodes.end() || it2 == nodes.end())
        errExit(1, "Edge cannot be reset: points not found");

    float dist = it1->first.dist(it2->first);

    setEdgeW(idx_a, idx_b, dist);
}

void Graph::resetEdgesW()
{
    for (uint32_t i = 0; i < pt_idx; i++) {
        for (uint32_t j = 0; j < pt_idx; j++) {
            if (floatEQ(adj_mat[i][j].first, std::numeric_limits<float>::infinity())) {
                resetEdgeW(i, j);
                resetEdgeW(j, i);
            }
        }
    }
}

/**
 * @return aktuální dopravní koeficient
 */
float Graph::getTC()
{
    return TrafficCoef;
}

/**
 * @param nová hodnota dopravního koeficientu
 */
void Graph::setTC(float f)
{
    TrafficCoef = f;
}

/**
 * @param idx_a první index vrcholu
 * @param idx_b druhý index vrcholu
 * @return dopravní koeficient hrany
 */
float Graph::getEdgeTC(uint32_t idx_a, uint32_t idx_b)
{
    return adj_mat[idx_a][idx_b].second;
}

/**
 * @param A první bod
 * @param B druhý bod
 * @return dopravní koeficient hrany
 */
float Graph::getEdgeTC(Point A, Point B)
{
    return adj_mat[getNodeID(A)][getNodeID(B)].second;
}

/**
 * @param idx_a první index vrcholu
 * @param idx_b druhý index vrcholu
 */
void Graph::incEdgeTC(uint32_t idx_a, uint32_t idx_b)
{
    adj_mat[idx_a][idx_b].second += TrafficCoef;
    adj_mat[idx_b][idx_a].second += TrafficCoef;
}

/**
 * @param idx_a první index vrcholu
 * @param idx_b druhý index vrcholu
 */
void Graph::resetEdgeTC(uint32_t idx_a, uint32_t idx_b)
{
    adj_mat[idx_a][idx_b].second = 1.f;
    adj_mat[idx_b][idx_a].second = 1.f;
}

/**
 * @param A první bod
 * @param B druhý bod
 */
void Graph::incStreetTC(Point A, Point B)
{
    uint32_t sid = getStreetFromPoints(A, B);
    for (uint32_t i = 0; i < cs[sid].size() - 1; i++)
        incEdgeTC(cs[sid][i].second, cs[sid][i + 1].second);
}

/**
 * @param A první bod
 * @param B druhý bod
 */
void Graph::resetStreetTC(Point A, Point B)
{
    uint32_t sid = getStreetFromPoints(A, B);
    for (uint32_t i = 0; i < cs[sid].size() - 1; i++)
        resetEdgeTC(cs[sid][i].second, cs[sid][i + 1].second);
}

/**
 * @param A první bod
 * @param B druhý bod
 * @return dopravní koeficient celé ulice
 */
float Graph::getStreetTC(Point A, Point B)
{
    uint32_t sid = getStreetFromPoints(A, B);
    uint32_t idx_a, idx_b;

    idx_a = cs[sid][0].second;
    idx_b = cs[sid][1].second;

    return adj_mat[idx_a][idx_b].second;
}

/**
 * @param lnum id linky
 * @param path vektor s body stanic
 */
void Graph::SetUpLine(uint32_t lnum, std::vector<Point> path)
{
    line_pts[lnum].clear();

    line_pts[lnum].push_back(std::vector<Point>{path.front()});
    for (uint32_t i = 0; i + 1 < path.size(); i++) {
        std::vector<Point> subpath;

        if (!getPath(path[i], path[i + 1], subpath))
            errExit(1, "No path exists");

        line_pts[lnum].push_back(subpath);
    }

    line_pts[lnum].push_back(std::vector<Point>{path.back()});
}

/**
 * @param sid id uzavřené ulice
 * @return vektor s čísly zasažených linek
 */
std::vector<uint32_t> Graph::findLineConflicts(uint32_t sid)
{
    std::vector<uint32_t> ret(0);

    for (auto &i : line_pts) {
        std::vector<std::vector<Point>> &lpts = i.second;
        bool endFlag = false;

        for (uint32_t j = 1; j < lpts.size() - 1 && !endFlag; j++) {
            uint32_t len = 0;

            for (uint32_t k = 0; k < lpts[j].size() && !endFlag; k++) {
                Point P = lpts[j][k];

                auto it = std::find_if(cs[sid].begin(), cs[sid].end(),
                    [&P](auto &el) -> bool
                    { return P == el.first;});

                if (it != cs[sid].end()) {
                    len++;
                    if (len > 1) {
                        ret.push_back(i.first);
                        endFlag = true;
                    }
                } else
                    len = 0;
            }
        }
    }

    return ret;
}

/**
 * @param lid číslo linky
 * @param path nová cesta linky
 */
void Graph::updateLinePath(uint32_t lid, std::vector<std::vector<Point>> path)
{
    path.insert(path.begin(), std::vector<Point>{path.front().front()});
    path.push_back(std::vector<Point>{path.back().back()});
    line_pts[lid] = path;
}

/**
 * @param lid číslo linky
 * @return vektor vzdáleností jednotlivých stanic
 */
std::vector<std::pair<Point, float>> Graph::countLineSchedule(uint32_t lid)
{
    auto &lptr = line_pts[lid];
    std::vector<std::pair<Point, float>> distances{std::make_pair(lptr.front().front(), 0.f)};
    

    for (uint32_t i = 1; i < lptr.size() - 1; i++) {
        float d = 0.f;
        for (uint32_t j = 0; j < lptr[i].size() - 1; j++)
            d += lptr[i][j].dist(lptr[i][j + 1]);

        distances.push_back(std::make_pair(lptr[i].back(), d));
    }

    return distances;
}

/**
 * @param A první bod
 * @param B druhý bod
 * @param path vektor pro uložení cesty
 * @return true pokud byla nalezena cesta z bodu A do bodu B
 */
bool Graph::getPath(Point A, Point B, std::vector<Point> &path)
{
    uint32_t idx;
    auto getClosest = [](auto &lhs, auto &rhs)
        { return lhs.second < rhs.second; };

    uint32_t src = getNodeID(A);
    uint32_t dst = getNodeID(B);

    std::list<std::pair<std::vector<uint32_t>, float>> open, close;
    std::list<std::pair<std::vector<uint32_t>, float>>::iterator it;

    open.push_back(make_pair(std::vector<uint32_t>{src}, 0.f));

    while (!open.empty()) {
        it = std::min_element(open.begin(), open.end(), getClosest);
        if (it->first.back() == dst) {
            path.clear();
            for (auto &i : it->first)
                path.push_back(getNodePoint(i));

            return true;
        }
        
        close.push_back(*it);
        idx = it->first.back();

        for (uint32_t i = 0; i < pt_idx; i++) {
            if (std::find_if(close.begin(), close.end(),
                [&i](auto &el) -> bool
                { return i == el.first.back(); }) != close.end())
                continue;
            else {
                float f = adj_mat[idx][i].first;
                std::vector<uint32_t> v(it->first);
                
                if (f > 0 && f != std::numeric_limits<float>::infinity()) {
                    f += it->second;
                    auto toDel = std::find_if(open.begin(), open.end(),
                        [&i](auto &el) -> bool
                        { return i == el.first.back(); });
                    if (toDel != open.end()) {
                        if (f < toDel->second) {
                            open.erase(toDel);
                            v.push_back(i);
                            open.push_back(make_pair(v, f));
                        }
                    } else {
                        v.push_back(i);
                        open.push_back(make_pair(v, f));
                    }
                }
            }
        }

        open.erase(it);
    }

    return false;    
}

/**
 * @param p1 první bod
 * @param p2 druhý bod
 * @return true pokud jsou body spojeny hranou
 */
bool Graph::isEdge(Point p1, Point p2)
{
    auto idx1 = getNodeID(p1);
    auto idx2 = getNodeID(p2);
    if (adj_mat[idx1][idx2].first != 0.f) return true;
    return false;
}

Graph::~Graph(){}