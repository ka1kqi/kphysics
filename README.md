# kphysics
Monte Carlo Photon propogation sim, built on OpenMP and ImageMagick. Takes a PGM as the propogation material.
Upload a PHM or generate from a JPEG/PNG. 

Only supported on Apple systems

---

### Requirements
- C++ >=17
- llvm
- brew
- ImageMagick

## Installation
Install OpenMP and ImageMagick if not installed 

```
#if llvm not installed
brew install llvm libomp

brew install imagemagick
```

Go into the build directory and build the executable

```
cd build
cmake -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++ ..
cmake --build .
make
```

Generate the PGM from any JPEG/PNG (skip if you already have a PGM)
```
magick /path/to/*.jpg -colorspace Gray -depth 8 pgms/*.pgm
```

# Usage
```
./r70 pgms/*.pgm #photon_to_propogate
```

The resulting output will be an "absorbtion.csv" map of the output and a visualization of the results in "absorbtion.pgm." 