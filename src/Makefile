#
# Makefile in the src-directory
#
TARGET  = go2pov
CC      = g++

OBJECTS =	gameinfo.o gamenode.o\
		gametree.o consoleviewer.o\
		goboard.o gofile.o\
		main.o parser.o\
		povwriter.o\
		propadd.o\
		propcomment.o propmove.o\
		sgfparser.o

SOURCES =	boardwriter.h\
		consoleviewer.h consoleviewer.cpp\
		gameinfo.h gameinfo.cpp\
		gametree.h gametree.cpp\
		gameviewer.h gamewriter.h\
		goboard.h goboard.cpp\
		gofile.h gofile.cpp\
		goparser.h\
		main.cpp\
		nodeproperty.h\
		parser.h parser.cpp\
		povwriter.h povwriter.cpp\
		propadd.h propadd.cpp\
		propcomment.h propcomment.cpp\
		propmove.h propmove.cpp\
		sgfparser.h sgfparser.cpp

CFLAGS  = -Wall -pedantic
HP_DEBUG= -DGNU_C
DEFINES = -DGO2POV_MAIN_VERSION='"$(VERSION)"' -g3
INCLUDE =
LIBS    =
# -g3 -DDEBUG_MTRACE
# LIBS    = -lm -lpng -lz
# -lmcheck
# setenv MALLOC_TRACE mtrace.log
DO_CC   = $(CC) $(CFLAGS) $(HP_DEBUG) $(DEFINES) $(INCLUDE) -o $@ -c $< 


# PHONY: .cpp
.cpp.o:
	$(DO_CC)
.c.o:
	$(DO_CC)

all: $(TARGET) $(SOURCES)
$(TARGET): $(OBJECTS) $(SOURCES)
	$(CC) -Wall $(OBJECTS) -o $(TARGET) $(CFLAGS) $(LIBS)
	cp $(TARGET) ..

clean:
	rm -f $(TARGET) $(OBJECTS) mtrace.log

tidy:
	rm -f $(OBJECTS) $(TARGET) *~ core mtrace.log
	rm -f *.pov

test: $(TARGET)
	go2pov ../samples/kitani.sgf
	x-povray -Itest.pov -geometry 320x240
	ee test.png