#include "all_includes.h"
#include "engine.cpp"
#include <iostream>

int main(int argc,char**argv){
    if(argc<3){ std::cerr<<"Usage: "<<argv[0]<<" input.pgm"<<" #photons\n"; return 1; }
    PhotonEngine engine(/*photons*/std::stoi(argv[2]), /*threads*/4);
    if(!engine.loadVolumeFromPGM(argv[1], 64,1e-3,1e-3,1e-3,
                                 0.1,3.0, 5.0,30.0, 0.0)){
        std::cerr<<"Failed to load\n"; return 2;
    }
    engine.run();
    engine.printStats();
    engine.writeAbsorption2D("absorption.csv","absorption.pgm");
    return 0;
}