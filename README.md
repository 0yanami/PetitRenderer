# PetitRenderer

Features:
- Tessellation (PN,BumpMap)
- Shadow Map
- HDR/tonemapping
- SSAO
- Normal Map
- CubeMap
- Basic UI

### Build
Builds on Windows 10 with MSVC from Visual Studio 2019

Example:
```
cd PetitRenderer
mkdir build
cd build
cmake . -G "Visual Studio 16 2019" ..
cmake --build . --target PetitRenderer --config Release -j 16
cd PetitRenderer/Release/
PetitRenderer.exe
```
