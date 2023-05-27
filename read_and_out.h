#include "classes.h"
class reader{
    string inpname;
public:
    reader(string);
    bmpfile read();
};

class outp{
    string outname;
public:
    outp(string);
    void out(bmpfile);
};