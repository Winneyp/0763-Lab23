#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main(int argc,char* atgv[])
{
    if(argc == 1) cout << "Please input numbers to find average.";
    else{
        double plus=0,average;
        for (int i=1;i<argc;i++)
        {
            plus += atof(atgv[i]);
        }
        average = plus / (argc-1);
        cout << "---------------------------------\n";
        cout << "Average of "<<argc-1<<" numbers = "<<average<<endl;
        cout << "---------------------------------";
        return 0;
    }
}
