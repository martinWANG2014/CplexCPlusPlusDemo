# CplexCPlusPlusDemo
a simple demo of using cplex callable library for C/C++. 
>> Be attention that you should configure Visual Studio for your toolchain and cmake if you use the CLion in the Windows environment because that cplex C++ callable library works for MSVC compiler while not for MinGW and CygWin (always find some bugs for MinGW and CygWin).
## Configuration of ToolChain for CLion in Windows 
![ToolChains](https://github.com/martinWANG2014/CplexCPlusPlusDemo/blob/master/toolchain_wins_clion.jpg)
## Configuration of CMake for CLion in Windows
![CMake](https://github.com/martinWANG2014/CplexCPlusPlusDemo/blob/master/cmake_wins_clion.jpg)
# Executable Target
## Path: /build/bin
# Model File
## Path: /build/model.lp
# Solution File
## Path: /build/sol.sl
# Dependency Library Configuration
## Path: /cmake/FindCplex.cmake
# CMakeLists File
## Path: CMakeLists.txt
>> For a simple use, you can just modify the project name
