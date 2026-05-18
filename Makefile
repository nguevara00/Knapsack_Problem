CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

TARGET = knapsack

SRCS = main.cpp \
       DynamicKnapsack.cpp \
       Greedy.cpp \
       HashTable.cpp \
       Heap.cpp \
       SpaceEfficient.cpp \
       Utils.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)