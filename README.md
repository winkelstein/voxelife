# biolife

Voxel Game Engine for learning neural networks in virtual environment.

## clone
This repository depends on third-party libraries. You need to clone repository with submodules.
```
git clone --recurse-submodules https://github.com/winkelstein/biolife.git biolife
```

## build
```
mkdir build
cd build
cmake ..
cd ..
./build/biolife
```
Executable trying to find shaders in the project source directory, so after building you have to jump back to the root.
