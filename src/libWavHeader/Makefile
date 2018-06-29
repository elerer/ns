INCLUDES = ../../include
LIBS = 
LIBS_PATH = 
SRC = WavHeader.cpp WavHeaderTemplate.cpp
OBJECTS = $(SRC:.cpp=.o)    
FLAGS = -c -Wall -Werror -fpic -std=c++14 -g

all: shared

shared : build
	gcc -shared -o libwavheader.so $(OBJECTS)

build:
	g++ -I$(INCLUDES) $(FLAGS) $(SRC) -L$(LIBS_PATH) -l$(LIBS)
