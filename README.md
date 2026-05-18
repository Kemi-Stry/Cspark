# Cspark
Cmake project creator

```cmd
cspark <project name> <type> <lang> <std> <path>
```
.eg

```cmd
cspark "project" "exe" "c++" "23" "."
```

It is highly recomended to use Clang compiler with Ninja build system for build generated project
```cmd
cmake -B build -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
```
