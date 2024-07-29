# Ray tracer

`build.bat` includes an NPM package `gnomon` to time the build process.

## Building
```bash
# Clone the repository
git clone https://github.com/bissakov/raytracer-cpp.git

# Change directory
cd raytracer-cpp

# Install gnomon
npm install -g gnomon

# Build (modify the batch script if you want to remove gnomon and/or target x86)
./build.bat

# Run
./build/raytracer.exe --root path/to/root/dir

# Run tests
./build/raytracer.exe --root path/to/root/dir --test
```
