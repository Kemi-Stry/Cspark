# Cspark
### Terminal UI Cmake project creator

This creator allows you to create programs and libraries in both C and C++

To generate project use this command:
```cmd
cspark <path>
```

It is highly recommended to use Clang compiler with Ninja build system for building generated project
```cmd
cmake -B build -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
```
