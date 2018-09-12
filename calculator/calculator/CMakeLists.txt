# CMakeList.txt: CMake-Projekt für "calculator". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (calculator "src/main.cpp" "src/calculator.cpp" "src/calculator.h")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
