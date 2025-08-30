# Hangbag!

## Compiling

### Using Docker
You can use docker to build the game. First, from the current directory, build the container:
```sh
docker build -t hangbag-builder .
```
If you only want the NES ROM, run:
```sh
docker run --rm -v .:/hangbag hangbag-builder
```
If you also want an HTML file with the ROM embedded, run:
```sh
docker run --rm -v .:/hangbag hangbag-builder html
```

### Manually Building
To get started, on your machine you will need to have installed:
* CMake
* GNU Make or another build tool supported by CMake
* cc65, cloned from the GitHub repository and built

Assuming you have cloned and build cc65 in `/opt/cc65`, run from the current directory to prepare the build directory:
```sh
CC65_PATH=/opt/cc65 cmake -B build
```
If you only want the NES ROM, run:
```sh
cmake --build build
```
If you also want an HTML file with the ROM embedded, run:
```sh
cmake --build build --target html
```
