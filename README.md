# TRPG

TRPG is a 2D RPG game with Top-Down perspective. The game is built using C++ and SDL3.

## Getting Started

### Prerequisites

- C++ Compiler
- CMake
- SDL3
- SDL3_image
- nlohmann/json

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/TerraFaster/TRPG.git --recursive
    cd TRPG
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake .. -DSDL3IMAGE_VENDORED=ON -DBUILD_SHARED_LIBS=OFF
    ```

4. Navigate back to the root directory:
    ```sh
    cd ..
    ```

4. Build the project with powershell script (Game will run after building):
    ```sh
    .\build.ps1
    ```

### Running the Game

After building, you can run the game executable found in the `build` directory or run build script again.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- [CMake](https://cmake.org/)
- [SDL3](https://github.com/libsdl-org/SDL)
- [SDL3_image](https://github.com/libsdl-org/SDL_image)
- [nlohmann/json](https://github.com/nlohmann/json)

Enjoy your adventure in TRPG!
