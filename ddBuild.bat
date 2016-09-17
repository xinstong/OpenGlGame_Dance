cls

cd ./build

rm -f CMakeCache.txt 
rm -rf CMakeFiles 

cmake ..\src

cd ..

pause