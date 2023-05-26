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
    //vector<unsigned char> bvector(imageSize);
    //file.read(&bvector.data(), imageSize);
    f.changepad(width);
    vector<vector<PIXELDATA>> pixels(height);
    for(int i =0; i < height; i++){
        pixels[i].resize(width);
    }
    for(int i = 0; i < height; i++){
        file.read((char*)pixels[i].data(), width*sizeof(PIXELDATA));
        file.seekg(f.pad, ios::cur);
    }
    f.data = pixels;
    file.close();
    return f;
}
bmpfile:: bmpfile(){
    pad = 0;
}
void bmpfile:: changepad(int w){
     pad = (4 - (w * sizeof(PIXELDATA)) % 4) % 4;
}
change:: change(int n){
    mult = n;
}
bmpfile change:: increase(bmpfile f){
    bmpfile out;
    int old_width = f.head.width;
    int old_height = f.head.depth;
    int width = old_width * mult;
    int height = old_height * mult;
    cout << old_width << ' '<< old_height << ' '<<f.head.filesize<<endl;
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
/*    for (int i = 0; i < f.head.depth; i++){
        // Vertical resizing loop.
        // See below for full explanation on what this loop is achieving.
        for(int j = 0; j < mult; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < f.head.width; k++)
            {
                // temporary storage
                PIXELDATA temp = f.data[i*mult*f.head.width + j*f.head.width + k];
            
                // Horizontal resizing loop.
                for(int l = 0; l < mult; l++)
                {
                    // write RGB triple to outfile
                    pixels[]
                }
            }
        }
    }
    */
    out.data = pixels;
    out.head = f.head;
    out.head.width = width;
    out.head.depth = height;
    out.changepad(width);
    size_t imageSize = (width * sizeof(PIXELDATA) + f.pad)*height;
    out.head.filesize = imageSize + f.head.headersize + f.head.infoSize;
    return out;
}
outp:: outp(string s){
    outname = s;
}
void outp:: out(bmpfile f){
    cout << f.head.width << ' '<< f.head.depth << ' '<<f.head.filesize<<endl;
    ofstream file(outname, ios::binary);
    if(!file.is_open()){
        throw invalid_argument("Can`t create a new file");
    }
    char* pad = new char(f.pad);
    for(int i =0; i< f.pad; i++){
        pad[i] = 0;
    }
    file.write((char*)(&f.head), sizeof(f.head));
    for(int i =0; i < f.head.depth; i++){
        file.write((char*)f.data[i].data(), f.head.width*sizeof(PIXELDATA));
        file.write(pad, f.pad);
    }
    file.close();
}