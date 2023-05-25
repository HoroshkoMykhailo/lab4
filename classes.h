#include "file_structures.h"
class reader{
    string filename;
public:
    reader(string);
    bmpfile read();
};
class bmpfile{
    BMPHEAD head;
    vector<PIXELDATA> data;
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