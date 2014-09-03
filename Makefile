SHELL = /bin/bash
LIB = lib
CODE = src
INC = include

CXX        = g++
LD         = g++

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)

CXXFLAGS   = -O2 -Wall $(ROOTCFLAGS)

LIBS	   = $(ROOTLIBS) 
GLIBS	   = $(ROOTGLIBS) 
INCLUDES = -I$(ROOTSYS)/include -I$(INC)


################################################################################
# Rules
################################################################################

all: $(LIB)/libSmartHistos.so 

$(LIB)/libSmartHistos.so: $(INC)/SmartHistos.h $(CODE)/SmartHistos.cxx
		@mkdir -p lib
		$(CXX) -fPIC $(CXXFLAGS) $(INCLUDES) -c $(CODE)/SmartHistos.cxx -o $(LIB)/libSmartHistos.so \

clean:
	rm -f lib/*
