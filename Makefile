CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

COMMON = common/csr
A1_SRC = assignment_01/src
A1_DRIVER = assignment_01/driver

GEMM = $(A1_DRIVER)/gemm_driver
CSR  = $(A1_DRIVER)/csr_driver
WRAPPER = common_wrapper/wrapper


all: gemm csr wrapper


gemm:
	$(CXX) $(CXXFLAGS) -I$(A1_SRC) \
		$(A1_DRIVER)/gemm_driver.cpp \
		$(A1_SRC)/gemm.cpp \
		-o $(GEMM)


csr:
	$(CXX) $(CXXFLAGS) -I$(COMMON) \
		$(A1_DRIVER)/csr_driver.cpp \
		$(COMMON)/csr.cpp \
		-o $(CSR)


wrapper:
	$(CXX) $(CXXFLAGS) \
		common_wrapper/wrapper.cpp \
		-o $(WRAPPER)


clean:
	rm -f $(GEMM) $(CSR) $(WRAPPER)


.PHONY: all gemm csr wrapper clean