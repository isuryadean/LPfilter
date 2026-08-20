# LPfilter

```
cd ~/my-plugin
cmake -B build-win -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw64.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build-win
```