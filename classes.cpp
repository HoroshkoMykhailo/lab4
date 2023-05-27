#include "classes.h"
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