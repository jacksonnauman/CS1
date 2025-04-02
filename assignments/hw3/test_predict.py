# DO NOT MODIFY THE CONTENTS OF THIS FILE!
# This script automatically compiles, runs, and compares your program's output with the expected results.  
# You are not required to understand how this script works, as it is beyond the scope of this class.  
# However, you can use it to test your program by running `python test_predict.py` on Eustis.  
# Make sure this script is in the same directory as your `predict.c` file.    

import subprocess
import os

# File paths
C_SOURCE_FILE = "predict.c"  # C source code file
EXECUTABLE = "./predict"  # Name of the compiled executable

# Define test cases (input, expected output)
TEST_CASES = [
    {
        "input": "8\n1 apple 5\n1 ape 3\n1 bat 4\n1 ball 6\n2 a\n2 ap\n2 b\n2 ba\n",
        "expected_output": "apple\napple\nball\nball\n"
    },
    {
        "input": "6\n1 cat 10\n1 car 15\n1 cart 7\n2 c\n2 ca\n2 car\n",
        "expected_output": "car\ncar\ncar\n"
    },
    {
        "input": "5\n1 tree 12\n1 trunk 8\n1 try 9\n2 tr\n2 t\n",
        "expected_output": "tree\ntree\n"
    },
    {
        "input": "4\n1 hello 5\n1 hi 10\n2 h\n2 hel\n",
        "expected_output": "hi\nhello\n"
    },
    {
        "input": "9\n1 apple 50\n1 ape 50\n1 bat 40\n1 ball 60\n2 a\n2 ap\n2 b\n2 ba\n2 c\n",
        "expected_output": "apple\napple\nball\nball\nunknown word\n"
    }
]

def compile_c_program():
    """Compiles the C program."""
    print("Compiling C program...")
    
    compile_command = ["gcc", C_SOURCE_FILE, "-o", EXECUTABLE]
    result = subprocess.run(compile_command, capture_output=True, text=True)
    
    if result.returncode == 0:
        print("Compilation successful!\n")
    else:
        print("Compilation failed!")
        print(result.stderr)
        exit(1)  # Exit if compilation fails

def run_test_case(test_input, expected_output):
    """Runs the C program with test input and compares against expected output."""
    try:
        # Run the compiled C program as a subprocess
        process = subprocess.run(
            EXECUTABLE,  # Call the executable
            input=test_input,  # Pass input as stdin
            text=True,  # Use text mode
            capture_output=True  # Capture stdout and stderr
        )
        
        # Get the actual output
        actual_output = process.stdout.strip()
        expected_output = expected_output.strip()
        
        # Compare actual vs expected
        if actual_output == expected_output:
            print("Test Passed!")
        else:
            print("Test Failed!")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{actual_output}")
    
    except FileNotFoundError:
        print(f"Error: {EXECUTABLE} not found. Make sure compilation succeeded.")

if __name__ == "__main__":
    compile_c_program()  # Step 1: Compile the C program

    print("Running Tests...\n")
    for i, test_case in enumerate(TEST_CASES):
        print(f"Test Case {i + 1}:")
        run_test_case(test_case["input"], test_case["expected_output"])
        print("-" * 40)
