#
# YOU DONT NEED TO TOUCH ANYTHING BELOW
#
BASE   = $(shell basename `pwd`)
VERSION= 0.1
TARGET = go2pov
DATE   = $(shell date +%Y%m%d_%H%M)
DIRNAME= $(BASE)-$(VERSION)
ARCHIVE= docs/AUTHOR docs/BUGS docs/Doxyfile\
		docs/FAQ docs/GPL docs/HOWTO docs/INSTALL\
		docs/TODO docs/VERSION\
		src/*.cpp src/*.h src/Makefile\
		samples/*.pov samples/*.inc\
		Makefile

export VERSION

all: $(TARGET)
$(TARGET):
	rm -f $(TARGET)
	cd src && $(MAKE)
	strip $(TARGET)

clean:
	cd src && $(MAKE) clean
	rm -f $(TARGET) mtrace.log

tidy:
	cd src &&  $(MAKE) tidy
	rm -f *~ $(TARGET) mtrace.log
	rm -f *.pov
	rm -f -r docs/autodoc.html

archive: tidy
	@find $(ARCHIVE) -not -type d | sed s:^:$(DIRNAME)/: >MANIFEST
	(cd ..; ln -s $(BASE) $(DIRNAME))
	@(cd ..; tar -czf $(BASE)/$(DIRNAME).tar.gz `cat $(BASE)/MANIFEST`)
	@(cd ..; rm $(DIRNAME))
	rm MANIFEST

release: archive

test:$(TARGET)
	cd src && make test
