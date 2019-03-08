#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include "DocumentGenerator.hpp"
#include <dirent.h>
#include <string.h>
#include <ctime>
using namespace std;

int main() 
{

    string path =  "/home/linux/ieng6/oce/32/c2patel/project_2/PresidentialSpeeches/Obama/"; 
    DocumentGenerator myDoc(path);
    cout << myDoc.generateDocument(100000) << endl;
    return 0;
}
