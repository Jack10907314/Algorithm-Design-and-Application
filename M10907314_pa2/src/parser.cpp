#include "parser.h"
#include "dijkstra.h"

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
        if (!strcmp(buffer, "grid"))
        {
            //input grid_x
            fin >> buffer;
            grid_x = atoi(buffer);
            //input grid_y
            fin >> buffer;
            grid_y = atoi(buffer);
        }
        if (!strcmp(buffer, "capacity"))
        {
            //input default cost
            fin >> buffer;
            capacity = atoi(buffer);
        }
        if (!strcmp(buffer, "num"))
        {
            fin >> buffer;
            if (!strcmp(buffer, "net"))
            {
                //set non default cost size
                fin >> buffer;             
                net = atoi(buffer);
                NDcosts.resize(net);

                for (int i = 0; i < net; ++i)
                {
                    //input non default x1 y1 x2 y2 cost
                    fin >> buffer;
                    NDcosts[i].setId(atoi(buffer));
                    fin >> buffer;
                    NDcosts[i].setX1(atoi(buffer));
                    fin >> buffer;
                    NDcosts[i].setY1(atoi(buffer));
                    fin >> buffer;
                    NDcosts[i].setX2(atoi(buffer));
                    fin >> buffer;
                    NDcosts[i].setY2(atoi(buffer));
                }
            }
        }
    }

    fin.close();

    return;
}

void mono ::routing()
{
    //////////////////////////////////////////////////////////
    ///////////////write your algorithm///////////////////////
    //////////////////////////////////////////////////////////

    /*cout << "------------input info-------------" << endl;
    cout << "grid " << grid_x << " " << grid_y << endl;
    cout << "capacity " << capacity << endl;
    cout << "num net " << net << endl;
    for (int i  = 0; i < NDcosts.size(); i++)
    {
        cout << NDcosts[i].getId() << " ";
        cout << NDcosts[i].getX1() << " ";
        cout << NDcosts[i].getY1() << " ";
        cout << NDcosts[i].getX2() << " ";
        cout << NDcosts[i].getY2() << " ";
        cout << endl;
    }*/

    cost struct_default_cost;
    struct_default_cost.right = Default_cost;
    struct_default_cost.up = Default_cost;
    struct_default_cost.right_count = 0;
    struct_default_cost.up_count = 0;
    vector<cost> initial_cost_y(grid_y, struct_default_cost);
    vector< vector<cost> > map_cost(grid_x, initial_cost_y);

    NDcost tmp;
    int n = NDcosts.size();
    for(int i = n-1; i > 0; i--)
    {
        for(int j = 0; j <= i-1; j++)
        {
            int long_j1 = abs(NDcosts[j].getX2()-NDcosts[j].getX1()) + abs(NDcosts[j].getY2()-NDcosts[j].getY1());
            int long_j2 = abs(NDcosts[j+1].getX2()-NDcosts[j+1].getX1()) + abs(NDcosts[j+1].getY2()-NDcosts[j+1].getY1());
            if( long_j1 > long_j2)
            {
                tmp = NDcosts[j];
                NDcosts[j] = NDcosts[j+1];
                NDcosts[j+1] = tmp;
            }
        }
    }
    //cout << NDcosts[0].getX1() << " " << NDcosts[0].getY1()<< " " << NDcosts[0].getX2() << " " << NDcosts[0].getY2()<<endl;
    int V = grid_x * grid_y;
    dijkstra my_dijkstra;
    vector<pair<int,int> > path(V, make_pair(0, 0));
    for (int k = 0; k < net; ++k)
    {
        vector<vertex > adj[V]; 
        for (int i = 0; i < grid_x; ++i)
        {
            for (int j = 0; j < grid_y; ++j)
            {
                if(i == 0 && j == 0)
                {

                }
                else if(i == 0)
                {
                    int now_index = 0;
                    int index = 0;
                    my_dijkstra.encode(&now_index, i, j, grid_y);

                    my_dijkstra.encode(&index, i, j-1, grid_y);
                    my_dijkstra.PathAdd(adj, index, now_index, map_cost[i][j-1].up); 
                }
                else if(j == 0)
                {
                    int now_index = 0;
                    int index = 0;
                    my_dijkstra.encode(&now_index, i, j, grid_y);

                    my_dijkstra.encode(&index, i-1, j, grid_y);
                    my_dijkstra.PathAdd(adj, index, now_index, map_cost[i-1][j].right); 
                }
                else
                {
                    int now_index = 0;
                    int index = 0;
                    my_dijkstra.encode(&now_index, i, j, grid_y);

                    my_dijkstra.encode(&index, i, j-1, grid_y);
                    my_dijkstra.PathAdd(adj, index, now_index, map_cost[i][j-1].up); 

                    my_dijkstra.encode(&index, i-1, j, grid_y);
                    my_dijkstra.PathAdd(adj, index, now_index, map_cost[i-1][j].right); 
                }

                 
            }
        }

        int now_index = 0;
        int start_x = NDcosts[k].getX1();
        int start_y = NDcosts[k].getY1();
        my_dijkstra.encode(&now_index, start_x, start_y, grid_y);
        my_dijkstra.CalculatePath(adj, &path, V, now_index);

        int end_x = NDcosts[k].getX2();
        int end_y = NDcosts[k].getY2();
        int end_index = 0;
        vector<NDcost> output;

        while(NDcosts[k].getX1() != end_x || NDcosts[k].getY1() != end_y)
        {
            int now_index, now_x, now_y;
            int previous_index, previous_x, previous_y;

            my_dijkstra.encode(&end_index, end_x, end_y, grid_y);
            now_index = path[end_index].first;
            previous_index = path[end_index].second;
            my_dijkstra.decode(now_index, &now_x, &now_y, grid_y);
            my_dijkstra.decode(previous_index, &previous_x, &previous_y, grid_y);
            
            NDcost temp;
            temp.setId(NDcosts[k].getId());
            temp.setX1(previous_x);
            temp.setY1(previous_y);
            temp.setX2(end_x);
            temp.setY2(end_y);
            output.push_back(temp);

            end_x = previous_x;
            end_y = previous_y;
                
        }
        
        //cout << output[0].getId() << " " << output.size() << endl;
        for (int i = output.size()-1; i >= 0; --i)
        {
            int cost_x, cost_y;
            cost_x = output[i].getX1();
            cost_y = output[i].getY1();

            if(output[i].getX1() == output[i].getX2())
            {
                if(output[i].getY2() < output[i].getY1())
                    cost_y = output[i].getY2();

                map_cost[cost_x][cost_y].up_count++;
                map_cost[cost_x][cost_y].up = map_cost[cost_x][cost_y].up_count + 1;
            }
            else if(output[i].getY1() == output[i].getY2())
            {
                if(output[i].getX2() < output[i].getX1())
                    cost_x = output[i].getX2();

                map_cost[cost_x][cost_y].right_count++;
                map_cost[cost_x][cost_y].right = map_cost[cost_x][cost_y].right_count + 1;
            }
            if(map_cost[cost_x][cost_y].right_count >= capacity)
                map_cost[cost_x][cost_y].right = 9999;
            if(map_cost[cost_x][cost_y].up_count >= capacity)
                map_cost[cost_x][cost_y].up = 9999;

            /*cout<< output[i].getX1() << " " << output[i].getY1() << " " 
                << output[i].getX2() << " " << output[i].getY2() << " "<<endl;*/
        }
        file_output.push_back(output);

        /*cout << "---------map " << k << " cost--------" << endl;

        for (int j = grid_y-1; j >= 0; --j)
        {
            for (int i = 0; i < grid_x; ++i)
            {
                cout << map_cost[i][j].up << "/" << map_cost[i][j].right << " ";
                //cout << i << "/" << j << " ";
            }
            cout << endl;
        }*/

        /*for (int i = 0; i < path.size(); ++i)
        {
            int now_index, now_x, now_y;
            int previous_index, previous_x, previous_y;
            now_index = path[i].first;
            previous_index = path[i].second;
            my_dijkstra.decode(now_index, &now_x, &now_y, grid_y);
            my_dijkstra.decode(previous_index, &previous_x, &previous_y, grid_y);

            cout << "path : " << "(" << now_x << "," << now_y << ")" << 
            " from path : " << "(" << previous_x << "," << previous_y << ")" <<endl;
        }*/
    }

    /*cout << "---------map path count--------" << endl;
    for (int j = grid_y-1; j >= 0; --j)
    {
        for (int i = 0; i < grid_x; ++i)
        {
            cout << map_cost[i][j].up_count << "/" << map_cost[i][j].right_count << " ";
            //cout << i << "/" << j << " ";
        }
        cout << endl;
    }
    int overflow = 0;

    cout << "---------overflow---------" << endl;
    for (int j = grid_y-1; j >= 0; --j)
    {
        for (int i = 0; i < grid_x; ++i)
        {
            if(map_cost[i][j].up_count > capacity)
            {
                cout << "x: "<<i<<" y: "<<j<< " up_count <<"<<map_cost[i][j].up_count << endl;
                overflow ++ ;
            }
            if(map_cost[i][j].right_count > capacity)
            {
                cout << "x: "<<i<<" y: "<<j<< " up_count <<"<<map_cost[i][j].right_count << endl;
                overflow ++ ;
            }
        }
    }

    cout << "overflow: " << overflow <<endl;*/
    
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
    for (int i = 0; i < file_output.size(); ++i)
    {
        fout << file_output[i][0].getId() << " " << file_output[i].size() << endl;
        for (int j = file_output[i].size()-1; j >= 0; --j)
        {
            fout<< file_output[i][j].getX1() << " " << file_output[i][j].getY1() << " " 
                << file_output[i][j].getX2() << " " << file_output[i][j].getY2() << " "<<endl;
        }
    }
    
    fout.close();

    return;
}
