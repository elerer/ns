INCLUDES = ../../include
LIBS = wavheader
LIBS_PATH = /home/eranl/go/src/github.com/ElExternalAudioSource/src/libWavHeader
SRC = WavHeader.cpp WavHeaderTemplate.cpp
UTIL_SRC = wav_utils.cpp
OBJECTS = $(SRC:.cpp=.o)    
FLAGS = -Wall -Werror -fpic -std=c++14 -g
LIB_FLAGS = -c 

all: shared

shared : build
	gcc -shared -o libwavheader.so $(OBJECTS)
	g++ -I$(INCLUDES) $(FLAGS) $(UTIL_SRC) -L$(LIBS_PATH) -l$(LIBS)  -o wav_util

build:
	g++ -I$(INCLUDES) $(FLAGS) $(LIB_FLAGS) $(SRC) 

