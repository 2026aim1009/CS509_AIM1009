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
        cout << "5. MST (Kruskal & Prim)" << endl;
        cout << "6. Vertex Coloring (Greedy / Welsh-Powell)" << endl;
        cout << "7. PageRank" << endl;
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
            cout << "\nEnter GEMM test case number (e.g., 01): ";
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
            cout << "\nEnter CSR test case number (e.g., 01 ): ";
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
            cout << "\nEnter Bellman-Ford test case number (e.g., 10 ): ";
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
            cout << "\nEnter Floyd-Warshall test case number (e.g., 10 ): ";
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
        // MST (Kruskal & Prim)
        // --------------------------------------------------
        else if (choice == 5) {
            cout << "\nAvailable MST test files:" << endl;
            runCommand("ls assignment_03/tests/mst_*.txt");

            string testSize;
            cout << "\nEnter MST test case size (e.g., 10, 100, 10000): ";
            cin >> testSize;
            string filename = "mst_" + testSize + ".txt";

            cout << "\nCompiling MST...\n" << endl;
            runCommand("make mst");

            cout << "\nRunning Kruskal's and Prim's MST on " << filename << "...\n" << endl;
            runCommand(
                "./assignment_03/driver/mst_driver " +
                string("assignment_03/tests/") +
                filename
            );
        }

        // --------------------------------------------------
        // Vertex Coloring
        // --------------------------------------------------
        else if (choice == 6) {
            cout << "\nAvailable Vertex Coloring test files:" << endl;
            runCommand("ls assignment_04/tests/color_*.txt");

            string testSize;
            cout << "\nEnter Vertex Coloring test case size (e.g., 10, 100, 10000): ";
            cin >> testSize;
            string filename = "color_" + testSize + ".txt";

            cout << "\nCompiling Vertex Coloring...\n" << endl;
            runCommand("make vertex_coloring");

            cout << "\nRunning Greedy Vertex Coloring on " << filename << "...\n" << endl;
            runCommand(
                "./assignment_04/driver/vertex_coloring_driver " +
                string("assignment_04/tests/") +
                filename
            );
        }

        // --------------------------------------------------
        // PageRank
        // --------------------------------------------------
        else if (choice == 7) {
            cout << "\nAvailable PageRank test files:" << endl;
            runCommand("ls assignment_04/tests/pagerank_*.txt");

            string testSize;
            cout << "\nEnter PageRank test case size (e.g., 10, 100, 1000): ";
            cin >> testSize;
            string filename = "pagerank_" + testSize + ".txt";

            cout << "\nCompiling PageRank...\n" << endl;
            runCommand("make pagerank");

            cout << "\nRunning PageRank on " << filename << "...\n" << endl;
            runCommand(
                "./assignment_04/driver/pagerank_driver " +
                string("assignment_04/tests/") +
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