#include "parser.h"

void mono ::parser(int argc, char **argv)
{
    //check argument count
    if (argc != 3)
    {
        cout << "Usage: ./mono <input_file_name> <output_file_name>" << endl;
        exit(1);
    }

    fstream fin;
    fin.open(argv[1], fstream::in);

    //check argument open
    if (!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }

    char buffer[100];

    //parser start
    while (!fin.eof())
    {
        fin >> buffer;
        if (!strcmp(buffer, "BoundaryIndex"))
        {
            //input Bx1
            fin >> buffer;
            Bx1 = atoi(buffer);
            //input By1
            fin >> buffer;
            By1 = atoi(buffer);
            //input Bx2
            fin >> buffer;
            Bx2 = atoi(buffer);
            //input By2
            fin >> buffer;
            By2 = atoi(buffer);
        }
        if (!strcmp(buffer, "DefaultCost"))
        {
            //input default cost
            fin >> buffer;
            default_cost = atoi(buffer);
        }
        if (!strcmp(buffer, "NumNonDefaultCost"))
        {
            //set non default cost size
            fin >> buffer;
            int size = atoi(buffer);
            NDcosts.resize(size);

            for (int i = 0; i < size; ++i)
            {
                //input non default x1 y1 x2 y2 cost
                fin >> buffer;
                NDcosts[i].setX1(atoi(buffer));
                fin >> buffer;
                NDcosts[i].setY1(atoi(buffer));
                fin >> buffer;
                NDcosts[i].setX2(atoi(buffer));
                fin >> buffer;
                NDcosts[i].setY2(atoi(buffer));
                fin >> buffer;
                NDcosts[i].setValue(atoi(buffer));
            }
        }
        if (!strcmp(buffer, "Source"))
        {
            //input start x y
            fin >> buffer;
            sx = atoi(buffer);
            fin >> buffer;
            sy = atoi(buffer);
        }
        if (!strcmp(buffer, "Target"))
        {
            //input target x y
            fin >> buffer;
            tx = atoi(buffer);
            fin >> buffer;
            ty = atoi(buffer);
        }
    }

    fin.close();

    // The following demonstrates how to use the parser
    /*cout << "Boundary Index: " << Bx1 << " " << By1 << " " << Bx2 << " " << By2 << endl;
    cout << "Default cost: " << default_cost << endl;
    cout << "# non-default costs: " << NDcosts.size() << endl;
    for (int i = 0; i < NDcosts.size(); ++i)
    {
        cout << NDcosts[i].getX1() << " " << NDcosts[i].getY1() << " "
             << NDcosts[i].getX2() << " " << NDcosts[i].getY2() << " "
             << NDcosts[i].getValue() << endl;
    }*/

    return;
}

void mono ::routing()
{
    //////////////////////////////////////////////////////////
    ///////////////write your algorithm///////////////////////
    //////////////////////////////////////////////////////////

    /*vector<int> initial_cost(Bx2 - Bx1, default_cost);
    //path cost map
    vector< vector<int> > up_cost_map(By2 - By1, initial_cost);
    vector< vector<int> > right_cost_map(By2 - By1, initial_cost);

    for (int i = 0; i < NDcosts.size(); ++i)
    {
        if (NDcosts[i].getX1() == NDcosts[i].getX2())
        {
            up_cost_map[NDcosts[i].getY1()][NDcosts[i].getX1()] = default_cost + NDcosts[i].getValue();
        }
        if (NDcosts[i].getY1() == NDcosts[i].getY2())
        {
            right_cost_map[NDcosts[i].getX1()][NDcosts[i].getY1()] = default_cost + NDcosts[i].getValue();
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << " " << up_cost_map[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << " " << right_cost_map[i][j];
        }
        cout << "\n";
    }*/
    int size_x = Bx2 - Bx1 + 1;
    int size_y = By2 - By1 + 1;

    cost struct_default_cost;
    struct_default_cost.right = default_cost;
    struct_default_cost.up = default_cost;
    vector<cost> initial_cost(size_x, struct_default_cost);
    vector< vector<cost> > cost_map(size_y, initial_cost);

    optimal struct_default_optimal;
    struct_default_optimal.optimal_cost = 0;
    struct_default_optimal.direction = 0;
    vector<optimal> initial_optimal(size_x, struct_default_optimal);
    vector< vector<optimal> > optimal_map(size_y, initial_optimal);

    for (int i = 0; i < NDcosts.size(); ++i)
    {
        if (NDcosts[i].getX1() == NDcosts[i].getX2())
        {
            cost_map[NDcosts[i].getY2()][NDcosts[i].getX2()].up = default_cost + NDcosts[i].getValue();
        }
        if (NDcosts[i].getY1() == NDcosts[i].getY2())
        {
            cost_map[NDcosts[i].getY2()][NDcosts[i].getX2()].right = default_cost + NDcosts[i].getValue();
        }
    }

    /*for (int i = 4; i >= 0; --i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cout << " " << cost_map[i][j].up << "/" << cost_map[i][j].right;
        }
    
        cout << "\n";
    }*/


    for (int i = 0; i < size_x; ++i)
    {
        for (int j = 0; j < size_y; ++j)
        {
            if(i == 0 && j == 0)
            {

            }
            else if(i == 0)
            {
                optimal_map[i][j].optimal_cost = optimal_map[i][j-1].optimal_cost + cost_map[i][j].right;
                optimal_map[i][j].direction = LEFT;
            }
            else if(j == 0)
            {
                optimal_map[i][j].optimal_cost = optimal_map[i-1][j].optimal_cost + cost_map[i][j].up;
                optimal_map[i][j].direction = DOWN;
            }
            else
            {
                int left_cost = optimal_map[i][j-1].optimal_cost + cost_map[i][j].right;
                int down_cost = optimal_map[i-1][j].optimal_cost + cost_map[i][j].up;
                if(left_cost <= down_cost)
                {
                    optimal_map[i][j].optimal_cost = left_cost;
                    optimal_map[i][j].direction = LEFT;
                }
                else
                {
                    optimal_map[i][j].optimal_cost = down_cost;
                    optimal_map[i][j].direction = DOWN;
                }
                
            }
            
        }
    }

    int x = Bx2;
    int y = By2;
    while(x != 0 || y != 0)
    {
        out myout;
        myout.cost = optimal_map[x][y].optimal_cost;
        myout.path_x = y;
        myout.path_y = x;
        vector_out.push_back(myout);
        if(optimal_map[x][y].direction == LEFT)
        {
            y--;
        }
        else if(optimal_map[x][y].direction == DOWN)
        {
            x--;
        }
    }
    out myout;
    myout.cost = optimal_map[x][y].optimal_cost;
    myout.path_x = y;
    myout.path_y = x;
    vector_out.push_back(myout);

    /*for (int i = 4; i >= 0; --i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cout << " " << optimal_map[i][j].optimal_cost << "/" << optimal_map[i][j].direction;
        }
        cout << "\n";
    }
    cout << "\n";

    for(int i = 0; i < vector_out.size(); ++i)
    {
        cout << vector_out[i].cost << "/" << vector_out[i].path_x << "/" << vector_out[i].path_y << endl;
    }*/

    return;
}

void mono ::output(int argc, char **argv)
{
    fstream fout;
    fout.open(argv[2], fstream::out);

    if (!fout.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }

    //////////////////////////////////////////////////////////
    //////////////////write your output///////////////////////
    //////////////////////////////////////////////////////////

    //cout << "RoutingCost " << vector_out[0].cost << endl;
    //cout << "RoutingPath " << vector_out.size() << endl;
    //for(int i = vector_out.size()-1; i >= 0 ; --i)
    //{
    //    cout << vector_out[i].path_x << " " << vector_out[i].path_y << endl;
    //}

    fout << "RoutingCost " << vector_out[0].cost << endl;
    fout << "RoutingPath " << vector_out.size() << endl;
    for(int i = vector_out.size()-1; i >= 0 ; --i)
    {
        fout << vector_out[i].path_x << " " << vector_out[i].path_y << endl;
    }
    
    fout.close();

    return;
}
