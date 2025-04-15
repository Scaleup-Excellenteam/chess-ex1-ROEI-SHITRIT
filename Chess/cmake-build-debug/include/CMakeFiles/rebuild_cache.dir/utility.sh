set -e

cd /cygdrive/c/Users/ORLY/CLionProjects/chess-ex1/Chess/cmake-build-debug/include
/cygdrive/c/Users/ORLY/AppData/Local/JetBrains/CLion2023.3/cygwin_cmake/bin/cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
