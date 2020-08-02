# An example demo game

This is a tiny sample game built using SimulationStarterKit. A [binary release of the game is available here](https://benmorris.itch.io/sample-game).

# Build from source (Windows)

- Download and install [SimulationStarterKit!](http://www.fireflytech.org)
- Download and install Visual Studio 2017
- Download and install CMake
```
git clone https://github.com/bensanmorris/SimulationStarterKit.git
cd SimulationStarterKit
cmake -G "Visual Studio 15 2017" -A x64 -Bbuild
```
- Open build/Project.sln in Visual Studio 2017 and build under the ***Release or RelWithDebInfo*** build configuration.
