# opengl-demo

Scratchpad project for experimenting with OpenGL

# Build

Ideally you should be building this in its own directory. On all platforms, run this command:

`mkdir build && cd build`

In order to generate the debug version of the project, run this command on *nix:

`cmake -DCMAKE_BUILD_TYPE=Debug ..`

For the release version on *nix, run this command:

`cmake -DCMAKE_BUILD_TYPE=Release ..`

On Windows for both versions, run this command:

`cmake ..`

In order to actually build the project, run this on *nix:

`cmake --build .`

On Windows, for the debug build, run this command:

`cmake --build . --config Debug`

On Windows, for the release build, run this command:

`cmake --build . --config Release`
