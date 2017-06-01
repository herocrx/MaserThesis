CSRCS=main.cpp

CFLAGS =  -c -O3 -DNDEBUG -fPIC

INCLUDE = -I. -I/usr/include/ -I/usr/include/X11/ -I/usr/local/include/GL -L~/home/yoctoadm/Programming/augmr_source/MasterThesis/OpenSceneGraph-Data-3.0.0
INCOSG = -I $(HOME)/Programming/OpenSceneGraph/OpenScenegraph-3.4.0/include
LDLIBS = -lm -ldl -lGL -lGLU -lpthread -lXext -lX11

LDFLAGS =  -L. -L/usr/lib -L/usr/X11R6/lib -L/usr/local/lib -L/home/yoctoadm/Programming/augmr_source/MasterThesis
LDOSG = -losg -losgViewer -losgSim -losgUtil -losgGA -losgDB -losgAnimation
COBJS=$(patsubst %.cpp,%.o,$(CSRCS))

CC = g++

EXE=Thesis

all: $(EXE)

$(EXE): $(COBJS) 
	g++ -o$(EXE) $(COBJS) $(INCLUDE) $(INCOSG) $(LDFLAGS) $(LDLIBS) $(LDOSG)
$(COBJS): %.o : %.cpp 
	$(CC) $(CFLAGS) -o $@ $< 


