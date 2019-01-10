#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

char tiles[20][20];

class mapGen
{
public:

    void Divide(string row, int rownum)
    {
        for(int i = 0; i < row.size(); i++)
        {
            tiles[rownum][i] = row[i];
        }
    }

    void generateMap(string path)
    {
        ifstream p;
        p.open(path.c_str());
        string passedrow;
        int row_num = 0;
        while(!p.eof())
        {
            getline(p,passedrow);
            Divide(passedrow,row_num);
            row_num++;
        }
        p.close();
    }
};
