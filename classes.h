#include "file_structures.h"
class bmpfile{
public:
    BMPHEAD head;
    int pad;
    vector<vector<PIXELDATA>> data;
    bmpfile();
    void changepad(int);
};

class reader{
    string inpname;
public:
    reader(string);
    bmpfile read();
};

class change{
    int mult;
public:
    change(int);
    bmpfile increase(bmpfile);
};

class outp{
    string outname;
public:
    outp(string);
    void out(bmpfile);
};