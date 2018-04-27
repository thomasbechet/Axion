CXX := g++
CXXFLAGS := -Wall -fPIC -std=gnu++14 -pedantic -D AXION_CORE_EXPORT
LDFLAGS := -shared
INCLUDES := -I../
TARGET := libaxion-core.so
SRCS := $(wildcard **/*.cpp) #Any depth
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
HDRS := $(wildcard **/*.hpp)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp $(HDRS)
	$(CXX) -c $< $(CXXFLAGS) $(INCLUDES) -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
	
.PHONY: all clean