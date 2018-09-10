add_executable(
    test_calculator 
        "src/test_calculator.cpp"
		"../calculator/calculator.cpp"
)

include_directories("../calculator/")
