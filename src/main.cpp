#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "povwriter.h"
#include "consoleviewer.h"

#ifndef GO2POV_MAIN_VERSION
#define GO2POV_MAIN_VERSION "cvs $Revision: 1.8 $"
#endif

void printUsage(char *_comline)
{
  char *a=strrchr(_comline, '/');

  fprintf(stderr, "usage: %s <go-file> [-s <steps>]\n", (a==NULL) ? _comline : a);
  fprintf(stderr, "\t<go-file>:\tmandatory SGF file for parsing\n");
  fprintf(stderr, "\t-s <steps>:\toptional number of steps to automatically run through and output\n");
}


int main(int _argc, char *_argv[])
{
  Parser        *parser=Parser::New();
  GoFile        *file=NULL;
  ConsoleViewer  viewer;
  PovWriter      writer;
  int steps = -1;

  fprintf(stderr, "go2pov (%s)\n", GO2POV_MAIN_VERSION);
  if ((_argc < 2) || (_argc == 3) || (_argc > 4))
    {
      printUsage(_argv[0]);
      return 1;
    }

  if (_argc == 4) {
      if (!strcmp(_argv[2], "-s")) { 
	      printUsage(_argv[0]);
      }
      steps = atoi(_argv[3]);
      if (steps <= 0) {
	      printUsage(_argv[0]);
      }
  }


  // test parser
  file=parser->parseFile(_argv[1]);
  if (file==NULL)
    {
      fprintf(stderr, "found no reader\n");
      return 1;
    }
  printf("%i game(s) loaded from file\n", file->getNumberGames());
  delete parser;

  // parsed a game ?
  if (file->getNumberGames())
    {
      //writer.setFilename("board");writer.setExtension("inc");
      viewer.viewGame(file->getGame(0), &writer, steps);
    }

  delete file;
  return 0;
}
