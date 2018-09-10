# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 2.6)

project ("calculator")

# Schließen Sie Unterprojekte ein.
add_subdirectory ("calculator")
add_subdirectory("tests")
