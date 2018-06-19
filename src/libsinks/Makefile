INCLUDES = -I../../include -I/home/eranl/boost_1_65_1
LIBS = 
LIBS_PATH = 
SRC = WavFileSink.cpp
OBJECTS = $(SRC:.cpp=.o)    
FLAGS = -c -Wall -Werror -fpic -std=c++14 -g

all: shared

shared : build
	gcc -shared -o libsinks.so $(OBJECTS)

build:
	g++ $(INCLUDES) $(FLAGS) $(SRC) -L$(LIBS_PATH) -l$(LIBS)