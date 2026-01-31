# sudo apt update
# sudo apt install \
#     libxrandr-dev \
#     libxcursor-dev \
#     libxi-dev \
#     libudev-dev \
#     libfreetype-dev \
#     libflac-dev \
#     libvorbis-dev \
#     libgl1-mesa-dev \
#     libegl1-mesa-dev \
#     libfreetype-dev

cmake -S . -B build
cmake --build build

./build/bin/main
