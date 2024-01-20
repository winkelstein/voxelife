# voxelife [PROJECT IN STATUS PROGRESS]

Voxel Game Engine for learning neural networks in the virtual environment.

## clone

This repository depends on third-party libraries. You need to clone repository with submodules.

```
git clone --recurse-submodules https://github.com/winkelstein/voxelife.git voxelife
```

## build

```
mkdir build
cd build
cmake ..
make
cd ..
./build/voxelife
```

Executable is trying to find shaders in the project source directory, so after building you have to jump back to the root.
