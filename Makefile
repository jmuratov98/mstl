CONFIG := debug
ifeq ($(config), release)
	CONFIG := release
endif

SRC		:= src
INCLUDE	:= include/mstl

BIN		:= bin
BINOBJ	:= bin-obj

TESTS	:= $(BIN)/test11.exe $(BIN)/test14.exe $(BIN)/test17.exe $(BIN)/test20.exe

MSTL_SOURCE_FILES	:= $(shell find ./${SRC}/ -name *.cpp)
MSTL_HEADER_FILES	:= $(shell find ./${INCLUDE}/ -name *.h)

MSTL_SOURCE_FILES	:= $(shell find ./${SRC}/ -name *.cpp)
MSTL_HEADER_FILES	:= $(shell find ./${INCLUDE}/ -name *.h)

MSTL_SOURCE_FILES	:= $(shell find ./${SRC}/ -name *.cpp)
MSTL_HEADER_FILES	:= $(shell find ./${INCLUDE}/ -name *.h)

MSTL_SOURCE_FILES	:= $(shell find ./${SRC}/ -name *.cpp)
MSTL_HEADER_FILES	:= $(shell find ./${INCLUDE}/ -name *.h)
MSTL_OBJECT_FILES	:= $(addprefix $(BINOBJ)/, $(patsubst %.cpp, %.o, $(notdir $(MSTL_SOURCE_FILES))))

TEST_SOURCE_FILES	:= test.cpp
TEST_OBJECT_FILES	:= $(BINOBJ)/test11.o $(BINOBJ)/test14.o $(BINOBJ)/test17.o $(BINOBJ)/test20.o

COMMON   	:= -Wall -march=native # -DNDEBUG
CXXFLAGS 	:= $(CXXFLAGS) $(COMMON)
CC       	:= gcc
CXX      	:= g++
LD       	:= $(CXX)
LDFLAGS  	:= $(LDFLAGS)  # -L/path/to/libs/
LDADD    	:=  # -lrt
INCLUDE  	:= -Iinclude # -I../path/to/headers/
DEFS     	:=  # -DLINUX

TARGET := $(BIN)/mstl.dll

ifeq ($(CONFIG), debug)
	CXXFLAGS += -g -ggdb -O0
	DEFS += -DMSTL_CONFIG_DEBUG
else
	CXXFLAGS += -O2
	DEFS += -DMSTL_CONFIG_RELEASE
endif

.PHONY: mstl tests
all: mstl tests

mstl: $(TARGET)

$(TARGET): $(MSTL_OBJECT_FILES)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDADD)

$(BINOBJ)/%.o: $(SRC)/%.cpp $(MSTL_HEADER_FILES)
	$(CXX) $(DEFS) $(INCLUDE) $(CXXFLAGS) -c $< -o $@

tests: $(TESTS)

$(BIN)/test11.exe: $(BINOBJ)/test11.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LDADD) -L$(BIN)/mstl.dll

$(BIN)/test14.exe: $(BINOBJ)/test14.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LDADD) -L$(BIN)/mstl.dll

$(BIN)/test17.exe: $(BINOBJ)/test17.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LDADD) -L$(BIN)/mstl.dll

$(BIN)/test20.exe: $(BINOBJ)/test20.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LDADD) -L$(BIN)/mstl.dll

$(BINOBJ)/test11.o: test.cpp $(MSTL_HEADER_FILES)
	$(CXX) $(DEFS) $(INCLUDE) -std=c++11 $(CXXFLAGS) -c $< -o $@

$(BINOBJ)/test14.o: test.cpp $(MSTL_HEADER_FILES)
	$(CXX) $(DEFS) $(INCLUDE) -std=c++14 $(CXXFLAGS) -c $< -o $@

$(BINOBJ)/test17.o: test.cpp $(MSTL_HEADER_FILES)
	$(CXX) $(DEFS) $(INCLUDE) -std=c++17 $(CXXFLAGS) -c $< -o $@

$(BINOBJ)/test20.o: test.cpp $(MSTL_HEADER_FILES)
	$(CXX) $(DEFS) $(INCLUDE) -std=c++20 $(CXXFLAGS) -c $< -o $@

.PHONY : init clean
init:
	mkdir ./bin/ ./bin-obj/

clean :
	rm -rf ./bin/* ./bin-obj/*
