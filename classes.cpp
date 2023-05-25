#include "classes.h"
reader:: reader(string s){
    inpname = s;
}
bmpfile reader:: read(){
    ifstream file(inpname, ios::binary);
    if(!file.is_open()){
        throw invalid_argument("File doesn`t exist");
    }
    bmpfile f;
    file.read((char*)(&f.head), sizeof(f.head));
    int width = f.head.width;
    int height = f.head.depth;
    int bytesPerPixel = f.head.bits / 8;
    cout << f.head.bits;
    if (bytesPerPixel != 3) {
        throw invalid_argument("Format of image is not supported");
    }
    size_t imageSize = width * height * sizeof(PIXELDATA);
    vector<PIXELDATA> pixels(width * height);
    file.read((char*)pixels.data(), imageSize);
    f.data = pixels;
    file.close();
    return f;
}
bmpfile:: bmpfile(){
}
outp:: outp(string s){
    outname = s;
}
void outp:: out(bmpfile f){
    ofstream file(outname, ios::binary);
    if(!file.is_open()){
        throw invalid_argument("Can`t create a new file");
    }
    size_t imageSize = f.data.size() * sizeof(PIXELDATA);
    file.write((char*)(&f.head), sizeof(f.head));
    file.write((char*)f.data.data(), imageSize);
    file.close();
}