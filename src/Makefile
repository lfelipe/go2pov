#
# Makefile in the src-directory
#
TARGET  = go2pov
CC      = gcc

OBJECTS =	gameinfo.o gamenode.o\
		gametree.o gofile.o\
		main.o parser.o\
		sgfparser.o

SOURCES =	gameinfo.h gameinfo.cpp\
		gameinfo.h gameinfo.cpp\
		gametree.h gametree.cpp\
		gofile.h gofile.cpp\
		goparser.h\
		main.cpp\
		parser.h parser.cpp\
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


.cpp.o:
	$(DO_CC)

all: $(TARGET) $(SOURCES)
$(TARGET): $(OBJECTS) $(SOURCES)
	$(CC) -Wall $(OBJECTS) -o $(TARGET) $(CFLAGS) $(LIBS)
	cp $(TARGET) ..
#	cp VERSION ../docs
#	cp TODO ../docs

clean:
	rm -f $(TARGET) $(OBJECTS) mtrace.log

tidy:
	rm -f $(OBJECTS) $(TARGET) *~ core mtrace.log
