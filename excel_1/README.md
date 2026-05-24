# excel_1

 Version: 0.9.1

 date    : 2026/05/24

 update :

***

C++ Windows , Excel example

* LLVM Clang use
* Visual studio Community 2026 use

***
### related

https://github.com/jmcnamara/libxlsxwriter

***
* vcpkg install
```
vcpkg install libxlsxwriter
```

***
* build

```
clang++ -target x86_64-pc-windows-msvc -m64 -std=c++17 -O2 main.cpp -o main.exe ^
  -I./include ^
  -I/prog/vcpkg/installed/x64-windows/include ^
  -L/prog/vcpkg/installed/x64-windows/lib ^
  -lxlsxwriter -lminizip
```

***
### blog
