INCLUDES = -I../include -I/home/eranl/boost_1_65_1/ -I/home/eranl/websocketpp
SRC = main_tester.cpp
LIBS = -lelexternalsource -lportaudio -lsinks -lwavheader -lboost_system
LIBS_PATH = -L./libExternalSource -L./libsinks -L/home/eranl/portaudio/lib/.libs/ -L/home/eranl/boost_1_65_1/stage/lib/ -L/home/eranl/go/src/github.com/ElExternalAudioSource/src/libWavHeader
FLAGS =  -Wall -Werror -fpic -std=c++14 -g -pthread


all: build

build:
	g++ $(INCLUDES) $(FLAGS) $(SRC) $(LIBS) $(LIBS_PATH)