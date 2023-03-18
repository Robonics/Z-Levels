cmake -G Ninja -B build
cmake --build build
copy .\build\bin\gunslinger.exe .\product\bin\gunslinger.exe
pause
cd product\bin\
gunslinger.exe
cd ../..