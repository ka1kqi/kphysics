#pragma once
#include "includes.h"

// Minimal PGM (P5) loader
struct Image {
    int w=0, h=0;
    std::vector<uint8_t> pix; // row-major, 8-bit
};

static inline void skip_ws_and_comments(std::istream& in){
    while (true){
        int c = in.peek();
        if (c=='#'){ in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }
        else if (std::isspace(c)) { in.get(); }
        else break;
    }
}

bool load_pgm(const std::string& path, Image& img){
    std::ifstream in(path, std::ios::binary);
    if(!in) return false;
    std::string magic; in >> magic;
    if(magic!="P5") return false;
    skip_ws_and_comments(in);
    in >> img.w; skip_ws_and_comments(in);
    in >> img.h; skip_ws_and_comments(in);
    int maxv; in >> maxv;
    if(maxv<=0 || maxv>255) return false;
    in.get(); // consume single whitespace after header
    img.pix.resize((size_t)img.w*img.h);
    in.read(reinterpret_cast<char*>(img.pix.data()), img.pix.size());
    return in.good();
}

// Simple PGM writer (P5)
bool write_pgm(const std::string& path, const std::vector<uint8_t>& data, int w, int h){
    std::ofstream out(path, std::ios::binary);
    if(!out) return false;
    out << "P5\n" << w << " " << h << "\n255\n";
    out.write(reinterpret_cast<const char*>(data.data()), (size_t)w*h);
    return (bool)out;
}

// CSV writer for double grid
bool write_csv(const std::string& path, const std::vector<double>& v, int w, int h){
    std::ofstream out(path);
    if(!out) return false;
    out.setf(std::ios::fixed); out.precision(8);
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            if(x) out << ",";
            out << v[x + w*y];
        }
        out << "\n";
    }
    return true;
}