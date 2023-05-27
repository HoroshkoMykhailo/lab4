#include "read_and_out.h"
int main(int argc, char* argv[]){
    try{
        if(argc != 4){
            cerr<< "You have not entered 3 arguments in command line";
            return 1;
        }
        string inp = "C:\\Visual studio\\codes\\4\\examples_4\\", out = inp;
        inp.append(argv[1]);
        out.append(argv[2]);
        int mult = stoi(argv[3]);
        reader input(inp);
        change c(mult);
        outp output(out);
        bmpfile infile = input.read();
        bmpfile outfile = c.increase(infile);
        output.out(outfile);
    }
    catch(const invalid_argument& e){
        cerr<< e.what();
    }
}