#include "parser.h"


int main( int argc, char** argv )
{   
    
double START,END; START = clock();
    //cout << "############################################" << endl;
    //cout << "#            Monotonic Routing             #" << endl;
    //cout << "############################################" << endl;

    mono monotonic;

    /////////////////////parser/////////////////////
    monotonic.parser( argc, argv );
    //cout << "............parser done!!!!!!.............." << endl;

    ////////////////////////monotonic route///////////////////////
    monotonic.routing( );
    //cout << "............monotonic routing done!!!!!!.............." << endl;

    /////////////////////output/////////////////////
    monotonic.output( argc, argv );
    //cout << "............output done!!!!!!.............." << endl;

    /*---要計算的程式效率區域---*/
END = clock();
cout << (END - START) / CLOCKS_PER_SEC << endl;
    return 0;
}

