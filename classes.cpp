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

change:: change(int n){
    mult = n;
}
bmpfile change:: increase(bmpfile f){
    bmpfile out;
    int width = f.head.width * mult;
    int height = f.head.depth * mult;
    size_t imageSize = width * height * sizeof(PIXELDATA);
    vector<PIXELDATA> pixels(width * height);
    for(int i = 0; i < f.data.size(); i++){
        for(int j = 0; j<mult; j++){
            pixels[i*mult + j] = f.data[i];
        }
    }
    out.data = pixels;
    out.head = f.head;
    out.head.width = width;
    out.head.depth = height;
    out.head.filesize = imageSize + f.head.headersize + f.head.infoSize;
    return out;
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