CPP = main.cpp KernelParser.cpp OpenCLMgr.cpp MNISTData.cpp
FLAGS = -g -std=c++14
LIBS = -l OpenCL

program: $(CPP) *.h
	g++ -o program $(CPP) $(FLAGS) $(LIBS)

clean:
	rm program