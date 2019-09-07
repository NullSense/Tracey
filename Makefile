SOURCES=$(shell find . -name "*.cpp")
OBJECTS=$(SOURCES:%.cpp=%.o)
TARGET=output_test_file
CXXFLAGS += -std=c++17
LDLIBS += -lpthread

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: run
run:
	./output_test_file
