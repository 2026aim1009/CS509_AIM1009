CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

COMMON = common/csr

A1_SRC = assignment_01/src
A1_DRIVER = assignment_01/driver

A2_SRC = assignment_02/src
A2_DRIVER = assignment_02/driver

A3_SRC = assignment_03/src
A3_DRIVER = assignment_03/driver

GEMM = $(A1_DRIVER)/gemm_driver
CSR = $(A1_DRIVER)/csr_driver
BELLMAN_FORD = $(A2_DRIVER)/bellman_ford_driver
FLOYD_WARSHALL = $(A2_DRIVER)/floyd_warshall_driver
MST = $(A3_DRIVER)/mst_driver
WRAPPER = common_wrapper/wrapper

all: gemm csr bellman_ford floyd_warshall mst wrapper

gemm:
	$(CXX) $(CXXFLAGS) -I$(A1_SRC) $(A1_DRIVER)/gemm_driver.cpp $(A1_SRC)/gemm.cpp -o $(GEMM)

csr:
	$(CXX) $(CXXFLAGS) -I$(COMMON) $(A1_DRIVER)/csr_driver.cpp $(COMMON)/csr.cpp -o $(CSR)

bellman_ford:
	$(CXX) $(CXXFLAGS) -I$(COMMON) -I$(A2_SRC) $(A2_DRIVER)/bellman_ford_driver.cpp $(A2_SRC)/bellman_ford.cpp $(COMMON)/csr.cpp -o $(BELLMAN_FORD)

floyd_warshall:
	$(CXX) $(CXXFLAGS) -I$(A2_SRC) $(A2_DRIVER)/floyd_warshall_driver.cpp $(A2_SRC)/floyd_warshall.cpp -o $(FLOYD_WARSHALL)

mst:
	$(CXX) $(CXXFLAGS) -I$(COMMON) -I$(A3_SRC) $(A3_DRIVER)/mst_driver.cpp $(A3_SRC)/mst.cpp $(COMMON)/csr.cpp -o $(MST)

wrapper:
	$(CXX) $(CXXFLAGS) common_wrapper/wrapper.cpp -o $(WRAPPER)

clean:
	rm -f $(GEMM) $(CSR) $(BELLMAN_FORD) $(FLOYD_WARSHALL) $(MST) $(WRAPPER)

.PHONY: all gemm csr bellman_ford floyd_warshall mst wrapper clean