# Raylib Tic Tac Toe

A tic-tac-toe game powered by [raylib](https://www.raylib.com/), compiling for both desktop and web using emscripten.

## Motivation

Practice my C programming skills.

## Prerequisites

1. Install [raylib](https://www.raylib.com/)
2. Install [CMake](https://cmake.org/)
3. [emsdk](https://emscripten.org/docs/getting_started/downloads.html) is required for web builds
4. Install the `just` command runner (optional)

## Compiling

### Using `just`

1. **List Commands**: To see a list of available commands:
   ```bash
   just help
   ```

2. **Build for Desktop**:
    **Debug**:
    ```bash
    just build-debug
    ```
    **Release**:
    ```bash
    just build-release
    ```

3. **Build for Web**: Before building for the web, ensure that the emsdk environment is correctly set up on your system.
   ```bash
   just build-web
   ```

4. **Clean**: To remove the build and out directories:
   ```bash
   just clean
   ```

### Manual Building

If you don't want to use `just`, you can also follow these manual steps:

#### Desktop Build

1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

2. Run CMake:
   ```bash
   cmake ..
   ```

3. Build the project:
   ```bash
   cmake --build . --config [Debug/Release] --target raylib-tic-tac-toe -j 10
   ```

#### Web Build

1. Activate emsdk:
   ```bash
   sudo emsdk activate latest
   source "/usr/lib/emsdk/emsdk_env.sh"
   ```

2. Create the web build directory:
   ```bash
   mkdir build-web && cd build-web
   ```

3. Ensure the resources folder is copied:
   ```bash
   rm -rf resources || true
   cp -R ../resources .
   ```

4. Run emscripten's CMake:
   ```bash
   emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-s USE_GLFW=3" -DCMAKE_EXECUTABLE_SUFFIX=".html"
   ```

5. Compile the project:
   ```bash
   emmake make
   ```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/wilsonsilva/raylib-tic-tac-toe.
This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere
to the [code of conduct](https://github.com/wilsonsilva/raylib-tic-tac-toe/blob/main/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the raylib-tic-tac-toe project's codebases, issue trackers, chat rooms and mailing lists is expected
to follow the [code of conduct](https://github.com/wilsonsilva/raylib-tic-tac-toe/blob/main/CODE_OF_CONDUCT.md).