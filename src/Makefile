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
		propcomment.o\
		propintvalue.o\
		propmove.o\
		propstring.o\
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
		propintvalue.h propintvalue.cpp\
		propmove.h propmove.cpp\
		propstring.h propstring.cpp\
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
	rm -f *.pov *.png

test: $(TARGET)
	./$(TARGET) ../samples/kitani.sgf
	x-povray -Igoboard.pov +W800 +H640 +A0.3
	ee goboard.png