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
bmpfile:: bmpfile(){
    pad = 0;
}
void bmpfile:: changepad(int w){
    pad = (4 - (w * sizeof(PIXELDATA)) % 4) % 4;
}
BMPHEAD& bmpfile:: gethead(){
    return head;
}
vector<vector<PIXELDATA>>& bmpfile:: getdata(){
    return data;
}
void bmpfile:: setdata(vector<vector<PIXELDATA>> d){
    data = d;
}
void bmpfile:: sethead(BMPHEAD h){
    head = h;
}
int bmpfile:: getpad(){
    return pad;
}
change:: change(int n){
    mult = n;
}
bmpfile change:: increase(bmpfile f){
    bmpfile out;
    int old_width = f.gethead().width;
    int old_height = f.gethead().depth;
    int width = old_width * mult;
    int height = old_height * mult;
    vector<vector<PIXELDATA>> pixels(height);
    for(int i = 0; i < height; i++){
        pixels[i].resize(width);
    }
    double index_row = 0;
    double index_col = 0;
    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            PIXELDATA to_add = f.getdata()[i][j];
            for (int k = index_row; k < index_row + mult; k++) {
                for (int h = index_col; h < index_col + mult; h++) {
                    pixels[k][h] = to_add;
                }
            }
            index_col += mult;
        }
        index_row += mult;
        index_col = 0;
    }
    /*
    vector<vector<PIXELDATA>> pixels1(height);
    for(int i =0; i < height; i++){
        pixels1[i].resize(old_width);
    }
    for(int i = 0; i < old_height; i++){
        for(int k = 0; k < old_width; k++){
            PIXELDATA temp = f.data[i][k];
            int row = i*mult;
            for(int j = 0; j<mult; j++){
                pixels1[j + row] [k] = temp;
            }
        }
    }
    vector<vector<PIXELDATA>> pixels(height);
    for(int i =0; i < height; i++){
        pixels[i].resize(width);
    }
    for(int i = 0; i<old_width; i++){
        for(int k = 0; k<height; k++){
            PIXELDATA temp = pixels1[k][i];
            int col = i*mult;
            for(int j =0; j <mult; j++){
                pixels[k][j + col]= temp;
            }
        }
    }
    */
    out.setdata(pixels);
    out.sethead(f.gethead());
    out.gethead().width = width;
    out.gethead().depth = height;
    out.changepad(width);
    size_t imageSize = (width * sizeof(PIXELDATA) + f.getpad())*height;
    out.gethead().filesize = imageSize + f.gethead().headersize + f.gethead().infoSize;
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