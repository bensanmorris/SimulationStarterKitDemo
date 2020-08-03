# An example demo game

This is a tiny sample game built using SimulationStarterKit. The game was built in the editor and then published as a code project from the editor's ***File -> Publish*** menu. 
A [binary release of the game is available here](https://benmorris.itch.io/sample-game).

# Build from source (Windows)

First, install pre-requisites:

- Download and install [SimulationStarterKit!](http://www.fireflytech.org)
- Download and install [Visual Studio 2017](https://visualstudio.microsoft.com/vs/older-downloads/)
- Download and install [CMake](https://cmake.org/download/)

Then:

```
git clone https://github.com/bensanmorris/SimulationStarterKit.git
cd SimulationStarterKit
cmake -G "Visual Studio 15 2017" -A x64 -Bbuild
cd build
cmake --build . --config Release
Release\Game1.exe
```
NB. You can also open build\Project.sln once generated (by cmake -G ... step above) in Visual Studio 2017 and build under the ***Release or RelWithDebInfo*** build configuration.
