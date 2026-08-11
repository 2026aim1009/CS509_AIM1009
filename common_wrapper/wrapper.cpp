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
        cout << "3. Bellman-Ford" << endl;
        cout << "4. Floyd-Warshall" << endl;
        cout << "0. Exit" << endl;

        cout << "\nEnter choice: ";
        cin >> choice;

        // --------------------------------------------------
        // GEMM
        // --------------------------------------------------
        if (choice == 1) {
            cout << "\nAvailable GEMM test files:" << endl;
            runCommand("ls assignment_01/tests/gemm_test_*.txt");

            string testNumber;
            cout << "\nEnter GEMM test case number (e.g., 01 or 12): ";
            cin >> testNumber;
            string filename = "gemm_test_" + testNumber + ".txt";

            int blockSize;
            cout << "\nEnter block size for GEMM Blocking: ";
            cin >> blockSize;

            cout << "\nCompiling GEMM..." << endl;
            runCommand("make gemm");

            cout << "\nRunning GEMM on " << filename << " with block size " << blockSize << "...\n" << endl;
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

            string testNumber;
            cout << "\nEnter CSR test case number (e.g., 01 or 12): ";
            cin >> testNumber;
            string filename = "csr_test_" + testNumber + ".txt";

            cout << "\nCompiling CSR..." << endl;
            runCommand("make csr");

            cout << "\nRunning CSR conversion on " << filename << "...\n" << endl;
            runCommand(
                "./assignment_01/driver/csr_driver " +
                string("assignment_01/tests/") +
                filename
            );
        }

        // --------------------------------------------------
        // Bellman-Ford
        // --------------------------------------------------
        else if (choice == 3) {
            cout << "\nAvailable Bellman-Ford test files:" << endl;
            runCommand("ls assignment_02/tests/bf_*.txt");

            string testNumber;
            cout << "\nEnter Bellman-Ford test case number (e.g., 10 or 100): ";
            cin >> testNumber;
            string filename = "bf_" + testNumber + ".txt";

            cout << "\nCompiling Bellman-Ford..." << endl;
            runCommand("make bellman_ford");

            cout << "\nRunning Bellman-Ford on " << filename << "...\n" << endl;
            runCommand(
                "./assignment_02/driver/bellman_ford_driver " +
                string("assignment_02/tests/") +
                filename
            );
        }

        // --------------------------------------------------
        // Floyd-Warshall
        // --------------------------------------------------
        else if (choice == 4) {
            cout << "\nAvailable Floyd-Warshall test files:" << endl;
            runCommand("ls assignment_02/tests/fw_*.txt");

            string testNumber;
            cout << "\nEnter Floyd-Warshall test case number (e.g., 10 or 100): ";
            cin >> testNumber;
            string filename = "fw_" + testNumber + ".txt";

            cout << "\nCompiling Floyd-Warshall..." << endl;
            runCommand("make floyd_warshall");

            cout << "\nRunning Floyd-Warshall on " << filename << "...\n" << endl;
            runCommand(
                "./assignment_02/driver/floyd_warshall_driver " +
                string("assignment_02/tests/") +
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