
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
        cout << " CS509 Assignment (INDIVIDUAL) - Common Wrapper" << endl;
        cout << "=================================================" << endl;

        cout << "1. GEMM (Simple + Blocking)" << endl;
        cout << "2. CSR Conversion" << endl;
        cout << "0. Exit" << endl;

        cout << "\nEnter choice: ";
        cin >> choice;

        // --------------------------------------------------
        // GEMM
        // --------------------------------------------------
        if (choice == 1) {

            cout << "\nAvailable GEMM test files:" << endl;
            runCommand("ls assignment_01/tests/gemm_test_*.txt");

            string filename;

            cout << "\nEnter test file name (e.g., gemm_test_01.txt): ";
            cin >> filename;

            int blockSize;

            cout << "\nEnter block size for GEMM Blocking: ";
            cin >> blockSize;

            cout << "\nCompiling GEMM..." << endl;
            runCommand("make gemm");

            cout << "\nRunning GEMM on "
                 << filename
                 << " with block size "
                 << blockSize
                 << "...\n"
                 << endl;

            runCommand(
                "./assignment_01/driver/gemm_driver " +
                string("assignment_01/tests/") +
                filename +
                " " +
                to_string(blockSize)
            );
        }

        // --------------------------------------------------
        // CSR
        // --------------------------------------------------
        else if (choice == 2) {

            cout << "\nAvailable CSR test files:" << endl;
            runCommand("ls assignment_01/tests/csr_test_*.txt");

            string filename;

            cout << "\nEnter test file name (e.g., csr_test_01.txt): ";
            cin >> filename;

            cout << "\nCompiling CSR..." << endl;
            runCommand("make csr");

            cout << "\nRunning CSR conversion on "
                 << filename
                 << "...\n"
                 << endl;

            runCommand(
                "./assignment_01/driver/csr_driver " +
                string("assignment_01/tests/") +
                filename
            );
        }

        // --------------------------------------------------
        // Exit
        // --------------------------------------------------
        else if (choice == 0) {

            cout << "Exiting." << endl;
            break;
        }

        // --------------------------------------------------
        // Invalid choice
        // --------------------------------------------------
        else {

            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

