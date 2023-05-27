#include "read_and_out.h"
reader:: reader(string s){
    inpname = s;
}
bmpfile reader:: read(){
    ifstream file(inpname, ios::binary);
    if(!file.is_open()){
        throw invalid_argument("File doesn`t exist");
    }
    bmpfile f;
    BMPHEAD head;
    file.read((char*)(&head), sizeof(BMPHEAD));
    int width = head.width;
    int height = head.depth;
    int bytesPerPixel = head.bits / 8;
    if (bytesPerPixel != 3) {
        throw invalid_argument("Format of image is not supported");
    }
    f.changepad(width);
    vector<vector<PIXELDATA>> pixels(height);
    for(int i =0; i < height; i++){
        pixels[i].resize(width);
    }
    for(int i = 0; i < height; i++){
        file.read((char*)pixels[i].data(), width*sizeof(PIXELDATA));
        file.seekg(f.getpad(), ios::cur);
    }
    f.sethead(head);
    f.setdata(pixels);
    file.close();
    return f;
}
outp:: outp(string s){
    outname = s;
}
void outp:: out(bmpfile f){
    ofstream file(outname, ios::binary);
    if(!file.is_open()){
        throw invalid_argument("Can`t create a new file");
    }
    char* pad = new char(f.getpad());
    for(int i =0; i< f.getpad(); i++){
        pad[i] = 0;
    }
    file.write((char*)(&f.gethead()), sizeof(BMPHEAD));
    for(int i =0; i < f.gethead().depth; i++){
        file.write((char*)f.getdata()[i].data(), f.gethead().width*sizeof(PIXELDATA));
        file.write(pad, f.getpad());
    }
    file.close();
}