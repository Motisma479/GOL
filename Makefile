PROGRAM=GameOfLife

# Add your objs to generate in OBJS var
OBJS=src/main.o src/GOL.o

CXX?=g++
TARGET?=$(shell $(CC) -dumpmachine)

CXXFLAGS=-O0 -fopenmp -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)


ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all server clean

all: $(PROGRAM)

-include $(DEPS)

%.o: %.c
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

server: $(SOBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o Server

clean:
	rm -f $(OBJS) $(SOBJS) $(DEPS) $(PROGRAM) Server