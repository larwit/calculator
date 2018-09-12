add_executable(
    test_calculator 
        "src/test_calculator.cpp"
		"../calculator/src/calculator.cpp"
		"../calculator/src/token.cpp"
)

include_directories("../calculator/src")
