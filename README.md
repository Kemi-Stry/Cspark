# Cspark
### Cmake project creator

This creator allows you to create programs and libraries in both C and C++

To generate project use this command:
```cmd
cspark <project name> <type> <lang> <std> <path>
```
where:
- type: exe or lib (executable or library)
- lang: c or c++
- std: decimal value of language version (eg. 23 for C23/C++23)
- path: path to directory where project will be generated

example:
```cmd
cspark "project" "exe" "c++" "23" "."
```

It is highly recommended to use Clang compiler with Ninja build system for building generated project
```cmd
cmake -B build -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
```
