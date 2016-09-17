@echo off
cls

mkdir build

cd ./build

rm -f CMakeCache.txt 
rm -rf CMakeFiles 

cmake ../src

cd ..

pause