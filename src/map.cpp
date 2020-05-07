#include "map.h"

Map::Map(){}

Map::Map(float new_w, float new_h)
: w(new_w), h(new_h){}

Map::Map(float w, float h, std::vector<Street> s)
: w(w), h(h), streets(s){}

void Map::addStreet(Street &s)
{
    streets.push_back(s);
}

void Map::createGraph()
{
    g = Graph(streets);
}

void Map::outputGraph()
{
    std::cout << g;
}

int Map::readMap(const char *filename)
{
    int i = 0;
    std::string a, b, c;
    std::ifstream infile;
    infile.open(filename, std::ios::in);

    if (!infile.is_open())
        return -1;

    for (std::string line; std::getline(infile, line); i++) {
        std::istringstream iss(line);
        if (i == 0) {
            if (!(iss >> w >> h)) {
                i = -2;
                break;
            }

        } else {
            std::string name;
            std::vector<float> c(4);
            if (!(iss >> c[0] >> c[1] >> c[2] >> c[3] >> name)) {
                    i = -3;
                    break;
                }
            else {
                Street s(Point(c[0], c[1]), Point(c[2], c[3]), name);
                addStreet(s);
            }
        }
    }

    infile.close();
    return i;
}


Map::~Map(){}
