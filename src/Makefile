INCLUDES = -I../include -I/home/eranl/boost_1_65_1/
SRC = main_tester.cpp
LIBS = -lelexternalsource -lportaudio -lsinks
LIBS_PATH = -L./libExternalSource -L./libsinks -L/home/eranl/portaudio/lib/.libs/
FLAGS =  -Wall -Werror -fpic -std=c++14 -g


all: build

build:
	g++ $(INCLUDES) $(FLAGS) $(SRC) $(LIBS) $(LIBS_PATH)