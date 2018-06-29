INCLUDES = ../../include
LIBS = -lportaudio -lwavheader
LIBS_PATH = -L/home/eranl/portaudio/lib/.libs/ -L/home/eranl/go/src/github.com/ElExternalAudioSource/src/libWavHeader
SRC = AudioInterfaceManager.cpp StreamCallbacks.cpp
OBJECTS = $(SRC:.cpp=.o)    
FLAGS = -c -Wall -Werror -fpic -std=c++14 -g

all: shared

shared : build
	gcc -shared -o libelexternalsource.so $(OBJECTS)

build:
	g++ -I$(INCLUDES) $(FLAGS) $(SRC) $(LIBS_PATH) $(LIBS)