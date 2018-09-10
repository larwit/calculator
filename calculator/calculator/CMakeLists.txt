# CMakeList.txt: CMake-Projekt für "calculator". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (calculator "main.cpp" "calculator.cpp" "calculator.h")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
