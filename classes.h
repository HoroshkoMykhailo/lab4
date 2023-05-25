#include "file_structures.h"
class bmpfile{
public:
    BMPHEAD head;
    vector<PIXELDATA> data;
    bmpfile();
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