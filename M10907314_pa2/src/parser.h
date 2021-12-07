#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>

#include <math.h>

using namespace std;

#define NIL -1
#define Inf 99999999
#define Default_cost 1
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


struct cost 
{
    int up;
    int right;

    int up_count;
    int right_count;
};

class NDcost
{
public:
    //////////////////set////////////////////
    void setX1 ( int x1 ) { _x1 = x1; }
    void setY1 ( int y1 ) { _y1 = y1; }
    void setX2 ( int x2 ) { _x2 = x2; }
    void setY2 ( int y2 ) { _y2 = y2; }
    void setId ( int value ) { _id = value; }

    //////////////////get////////////////////
    int getX1 ( ) { return _x1; }
    int getY1 ( ) { return _y1; }
    int getX2 ( ) { return _x2; }
    int getY2 ( ) { return _y2; }
    int getId ( ) { return _id; }

private:
    int _x1;
    int _y1;
    int _x2;
    int _y2;
    int _id;
};

class mono
{
public:
/////////////////////////////functions/////////////////////////////

    void parser( int argc, char **argv );
    void routing( );
    void output( int argc, char **argv );

/////////////////////////////declaration/////////////////////////////

    //grid x y
    int grid_x;
    int grid_y;

    int capacity;

    int net;
    //non default cost
    vector< NDcost > NDcosts;

private:
    vector< vector<NDcost> > file_output;
};

#endif // PARSER_H
