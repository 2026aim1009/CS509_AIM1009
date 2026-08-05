#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void runCommand(const string& cmd) {
    int result = system(cmd.c_str());
    if (result != 0) {
        cerr << "Command failed: " << cmd << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n=================================================" << endl;
        cout << " CS509 Assignment (INDIVIDUAL)- Common Wrapper" << endl;
        cout << "===================================================" << endl;
        cout << "1. GEMM (Simple + Blocking)" << endl;
        cout << "2. CSR Conversion" << endl;
        cout << "0. Exit" << endl;
        cout << "\n\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n\nAvailable GEMM test files:" << endl;
            runCommand("ls ../assignment_01/tests/gemm_test_*.txt");

            string filename;
            cout << "\n\nEnter test file name (e.g., gemm_test_01.txt): ";
            cin >> filename;

            int blockSize;
            cout << "\n\nEnter block size for GEMM Blocking (e.g., 2, 16, 32, 64): ";
            cin >> blockSize;

            cout << "\n\nCompiling GEMM..." << endl;
            runCommand("g++ -o ../assignment_01/driver/gemm_driver "
                        "../assignment_01/driver/gemm_driver.cpp "
                        "../assignment_01/src/gemm.cpp");

            cout << "Running GEMM on " << filename << " with block size " << blockSize << "...\n" << endl;
            runCommand("../assignment_01/driver/gemm_driver ../assignment_01/tests/" + filename
                        + " " + to_string(blockSize));
        }
        else if (choice == 2) {
            cout << "\n\nAvailable CSR test files:" << endl;
            runCommand("ls ../assignment_01/tests/csr_test_*.txt");
            string filename;
            cout << "\n\nEnter test file name (e.g., csr_test_01.txt): ";
            cin >> filename;
            cout << "\n\nCompiling CSR..." << endl;
            runCommand("g++ -o ../assignment_01/driver/csr_driver "
                        "../assignment_01/driver/csr_driver.cpp "
                        "../assignment_01/src/csr.cpp");
            cout << "\n\nRunning CSR conversion on " << filename << "...\n" << endl;
            runCommand("../assignment_01/driver/csr_driver ../assignment_01/tests/" + filename);
        }
        else if (choice == 0) {
            cout << "Exiting." << endl;
            break;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}