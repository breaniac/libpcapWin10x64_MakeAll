#include <iostream>
#include <pcap/pcap.h>
#include "Pcap.h"
#include "utils.h"

#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char** argv)
{
#ifdef _DEBUG
    const char argc1[] = "Data/bigtest2.pcap";

    //ifstream myfile("Data/bigtest2.pcap");
    //if (myfile.is_open())
    //{
    //    myfile.close();
    //}
    //else {
    //    cout << "The file is not opened" << endl;
    //}


    Pcap p;
    for (int i = 1; i <= argc; i++) {
        if (p.init(argc1)) {
            p.loop();
        }
    }

#else
    Pcap p;
    for(int i=1; i < argc; i++) {
        if (p.init(argv[i])) {
            p.loop();
        }
    }
#endif


    return 0;
}


