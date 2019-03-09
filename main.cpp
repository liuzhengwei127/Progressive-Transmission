#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    float x, y, z;
};

struct Chartlet {
    float x, y;
};

struct Face {
    int a1, a2, a3,
            b1, b2, b3,
            c1, c2, c3,
            d1=0, d2=0, d3=0;
};

vector<Point*> vertexs;
vector<Chartlet*> chartlets;
vector<Point*> normal_vectors;
vector<Face*> faces;

float getDistanceF(int index, int v1, int v2, int v3) {
    // 计算点到面的距离
    float u1 = vertexs[v1]->x - vertexs[v2]->x,
            u2 = vertexs[v1]->y - vertexs[v2]->y,
            u3 = vertexs[v1]->z - vertexs[v2]->z,
            w1 = vertexs[v1]->x - vertexs[v3]->x,
            w2 = vertexs[v1]->y - vertexs[v3]->y,
            w3 = vertexs[v1]->z - vertexs[v3]->z;

    float a = u2 * w3 - u3 * w2,
            b = u3 * w1 - u1 * w3,
            c = u1 * w2 - u2 * w1,
            d = -(a*vertexs[v2]->x + b * vertexs[v2]->y + c * vertexs[v2]->z);

    float mod = sqrt((a * a + b * b + c * c));

    return abs(a* vertexs[index]->x + b * vertexs[index]->y + c * vertexs[index]->z + d) / mod;
}

float getDistance(int i, int j)
{
    // 简化的QEM算法
    float distance = 0;
    int count = 0;

    for (int k = 0; k < faces.size(); k++) {
        if (faces[k]->a1 == i + 1 || faces[k]->b1 == i + 1 || faces[k]->c1 == i + 1 || faces[k]->d1 == i + 1
            || faces[k]->a1 == j + 1 || faces[k]->b1 == j + 1 || faces[k]->c1 == j + 1 || faces[k]->d1 == j + 1) {
            distance += getDistanceF(j, faces[k]->a1 - 1, faces[k]->b1 - 1, faces[k]->c1 - 1);
            count++;
        }
    }

    return distance/count;
}

pair<int, int> getVertexToDel()
{
    float value = INT_MAX;
    pair<int, int> index;
    for (int i = 0; i < vertexs.size(); i++)
    {
        for (int j = 0; j < vertexs.size(); j++)
        {
            if (i != j){
                for (int k=0;k<faces.size();k++){
                    if ( (faces[k]->a1 == i+1 || faces[k]->b1 == i+1 || faces[k]->c1 == i+1 || faces[k]->d1 == i+1)
                    && (faces[k]->a1 == j+1 || faces[k]->b1 == j+1 || faces[k]->c1 == j+1 || faces[k]->d1 == j+1) ){
                        float distance = getDistance(i, j);
                        if (distance < value)
                        {
                            value = distance;
                            index.first = i + 1;
                            index.second = j + 1;
                        }
                        break;
                    }
                }
            }
        }
    }

    return index;
}

void Simplify(pair<int, int> index)
{
    for (int i = 0; i < faces.size(); i++)
    {
        if (faces[i]->a1 == index.first || faces[i]->b1 == index.first || faces[i]->c1 == index.first || faces[i]->d1 == index.first)
        {
            if (faces[i]->a1 == index.second || faces[i]->b1 == index.second || faces[i]->c1 == index.second || faces[i]->d1 == index.second)
            {
                if (faces[i]->d1 == 0)
                {
                    //包含三个点的面中含收缩边的两个点
                    delete faces[i];
                    faces.erase(faces.begin() + i);
                    i--;
                }
                else
                {
                    //包含四个点的面中含收缩边的两个点
                    if (faces[i]->a1 == index.first)
                    {
                        faces[i]->a1 = faces[i]->d1; faces[i]->a2 = faces[i]->d2; faces[i]->a3 = faces[i]->d3;
                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                    if (faces[i]->b1 == index.first)
                    {
                        faces[i]->b1 = faces[i]->d1; faces[i]->b2 = faces[i]->d2; faces[i]->b3 = faces[i]->d3;
                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                    if (faces[i]->c1 == index.first)
                    {
                        faces[i]->c1 = faces[i]->d1; faces[i]->c2 = faces[i]->d2; faces[i]->c3 = faces[i]->d3;
                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                    if (faces[i]->d1 == index.first)
                    {
                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                }
            }
            else
            {
                if (faces[i]->d1 == 0)
                {
                    //包含三个点的面中含收缩边的一个点
                    if (faces[i]->a1 == index.first)
                    {
                        faces[i]->a1 = index.second;
                        continue;
                    }
                    if (faces[i]->b1 == index.first)
                    {
                        faces[i]->b1 = index.second;
                        continue;
                    }
                    if (faces[i]->c1 == index.first)
                    {
                        faces[i]->c1 = index.second;
                        continue;
                    }
                }
                else
                {
                    //包含四个点的面含收缩边的一个点
                    if (faces[i]->a1 == index.first)
                    {
                        Face* tmpf = new Face;
                        tmpf->a1 = faces[i]->a1;
                        tmpf->a2 = faces[i]->a2;
                        tmpf->a3 = faces[i]->a3;
                        tmpf->b1 = faces[i]->b1;
                        tmpf->b2 = faces[i]->b2;
                        tmpf->b3 = faces[i]->b3;
                        tmpf->c1 = faces[i]->d1;
                        tmpf->c2 = faces[i]->d2;
                        tmpf->c3 = faces[i]->d3;
                        faces.push_back(tmpf);

                        faces[i]->a1 = faces[i]->d1;
                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                    if (faces[i]->b1 == index.first)
                    {
                        Face* tmpf = new Face;
                        tmpf->a1 = faces[i]->a1;
                        tmpf->a2 = faces[i]->a2;
                        tmpf->a3 = faces[i]->a3;
                        tmpf->b1 = faces[i]->b1;
                        tmpf->b2 = faces[i]->b2;
                        tmpf->b3 = faces[i]->b3;
                        tmpf->c1 = faces[i]->c1;
                        tmpf->c2 = faces[i]->c2;
                        tmpf->c3 = faces[i]->c3;
                        faces.push_back(tmpf);

                        faces[i]->b1 = faces[i]->d1;
                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                    if (faces[i]->c1 == index.first)
                    {
                        Face* tmpf = new Face;
                        tmpf->a1 = faces[i]->d1;
                        tmpf->a2 = faces[i]->d2;
                        tmpf->a3 = faces[i]->d3;
                        tmpf->b1 = faces[i]->b1;
                        tmpf->b2 = faces[i]->b2;
                        tmpf->b3 = faces[i]->b3;
                        tmpf->c1 = faces[i]->c1;
                        tmpf->c2 = faces[i]->c2;
                        tmpf->c3 = faces[i]->c3;
                        faces.push_back(tmpf);

                        faces[i]->c1 = faces[i]->d1;
                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                    if (faces[i]->d1 == index.first)
                    {
                        Face* tmpf = new Face;
                        tmpf->a1 = faces[i]->a1;
                        tmpf->a2 = faces[i]->a2;
                        tmpf->a3 = faces[i]->a3;
                        tmpf->b1 = faces[i]->b1;
                        tmpf->b2 = faces[i]->b2;
                        tmpf->b3 = faces[i]->b3;
                        tmpf->c1 = faces[i]->d1;
                        tmpf->c2 = faces[i]->d2;
                        tmpf->c3 = faces[i]->d3;
                        faces.push_back(tmpf);

                        faces[i]->d1 = 0; faces[i]->d2 = 0; faces[i]->d3 = 0;
                        continue;
                    }
                }
            }
        }
    }

    for (int i = 0; i < faces.size(); i++)
    {
        if (faces[i]->a1 > index.first)
            faces[i]->a1--;
        if (faces[i]->b1 > index.first)
            faces[i]->b1--;
        if (faces[i]->c1 > index.first)
            faces[i]->c1--;
        if (faces[i]->d1 > index.first)
            faces[i]->d1--;
    }

    vertexs.erase(vertexs.begin() + index.first - 1);
}

void readFile(string ifilename)
{
    ifstream ifile(ifilename);
    string line;

    if (ifile)
    {
        while (!ifile.eof())
        {
            float x, y, z;
            int a1, a2, a3, b1, b2, b3, c1, c2, c3, d1=0, d2=0, d3=0;
            getline(ifile, line);
            stringstream ss;
            switch (line[0])
            {
                case 'v':
                    switch (line[1])
                    {
                        case ' ':
                            line.erase(0, 2);
                            ss << line;
                            ss >> x >> y >> z;
                            {
                                Point* tmpv = new Point;
                                tmpv->x = x;
                                tmpv->y = y;
                                tmpv->z = z;
                                vertexs.push_back(tmpv);
                            }
                            break;
                        case 't':
                            line.erase(0, 2);
                            ss << line;
                            ss >> x >> y;
                            {
                                Chartlet* tmpc = new Chartlet;
                                tmpc->x = x;
                                tmpc->y = y;
                                chartlets.push_back(tmpc);
                            }
                            break;
                        case 'n':
                            line.erase(0, 2);
                            ss << line;
                            ss >> x >> y >> z;
                            {
                                Point* tmpn = new Point;
                                tmpn->x = x;
                                tmpn->y = y;
                                tmpn->z = z;
                                normal_vectors.push_back(tmpn);
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case 'f':
                    char ch;
                    line.erase(0, 2);
                    ss << line;
                    ss >> a1 >> ch >> a2 >> ch >> a3
                       >> b1 >> ch >> b2 >> ch >> b3
                       >> c1 >> ch >> c2 >> ch >> c3;
                    if (!ss.eof())
                        ss >> d1 >> ch >> d2 >> ch >> d3 >> ch;
                    {
                        Face* tmpf = new Face;
                        tmpf->a1 = a1;
                        tmpf->a2 = a2;
                        tmpf->a3 = a3;
                        tmpf->b1 = b1;
                        tmpf->b2 = b2;
                        tmpf->b3 = b3;
                        tmpf->c1 = c1;
                        tmpf->c2 = c2;
                        tmpf->c3 = c3;
                        tmpf->d1 = d1;
                        tmpf->d2 = d2;
                        tmpf->d3 = d3;
                        faces.push_back(tmpf);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        cout << "fail to open the input file" << endl;
        return;
    }

    ifile.close();
}

int main() {
    string ifilename, ofilename;
    cout << "Please input the name of file to be read" << endl;
    ifilename = "cylinder.obj";
    //cin >> ifilename;
    cout << "Please input the name of file to be written" << endl;
    ofilename = "output.obj";
    // cin >> ofilename;

    readFile(ifilename);

    for (int i=0;i<vertexs.size()/5;i++)
        Simplify(getVertexToDel());

    ofstream ofile(ofilename);
    ifstream ifile(ifilename);
    string line;

    if (ofile)
    {
        bool vertex = true, face = true;
        while (!ifile.eof())
        {
            getline(ifile, line);
            switch (line[0])
            {
                case 'v':
                    if (vertex)
                    {
                        for (int i = 0; i < vertexs.size(); i++)
                            ofile << "v " << vertexs[i]->x << ' ' << vertexs[i]->y << ' ' << vertexs[i]->z << '\n';
                        for (int i = 0; i < chartlets.size(); i++)
                            ofile << "vt " << chartlets[i]->x << ' ' << chartlets[i]->y << '\n';
                        for (int i = 0; i < normal_vectors.size(); i++)
                            ofile << "vn " << normal_vectors[i]->x << ' ' << normal_vectors[i]->y << ' ' << normal_vectors[i]->z << '\n';
                        vertex = false;
                    }
                    break;
                case 'f':
                    if (face)
                    {
                        for (int i = 0; i < faces.size(); i++)
                        {
                            ofile << "f " << faces[i]->a1 << '/' << faces[i]->a2 << '/' << faces[i]->a3 << ' '
                                  << faces[i]->b1 << '/' << faces[i]->b2 << '/' << faces[i]->b3 << ' '
                                  << faces[i]->c1 << '/' << faces[i]->c2 << '/' << faces[i]->c3;
                            if (faces[i]->d1 != 0)
                                ofile << ' ' << faces[i]->d1 << '/' << faces[i]->d2 << '/' << faces[i]->d3 << '\n';
                            else
                                ofile << '\n';
                        }

                        face = false;
                    }
                    break;
                default:
                    ofile << line << '\n';
                    break;
            }
        }
    }
    else
    {
        cout << "fail to open the output file" << endl;
    }
    ifile.close();
    ofile.close();

    return 0;
}