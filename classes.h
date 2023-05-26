#include "file_structures.h"
class bmpfile{
    BMPHEAD head;
    int pad;
    vector<vector<PIXELDATA>> data;
public:
    bmpfile();
    BMPHEAD& gethead();
    vector<vector<PIXELDATA>>& getdata();
    void sethead(BMPHEAD);
    void setdata(vector<vector<PIXELDATA>>);
    int getpad();
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