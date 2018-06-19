SUBDIRS := ./src/libExternalSource ./src/libWavHeader ./src/libsinks  ./src 

.PHONY : all $(SUBDIRS)
all : $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) -C $@ all