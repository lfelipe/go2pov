#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "povwriter.h"
#include "consoleviewer.h"

void printUsage(char *_comline)
{
  char *a=strrchr(_comline, '/');

  fprintf(stderr, "usage: %s <go-file>\n", (a==NULL) ? _comline : a);
}


int main(int _argc, char *_argv[])
{
  Parser        *parser=Parser::New();
  GoFile        *file=NULL;
  ConsoleViewer  viewer;
  PovWriter      writer;

  if (_argc < 2)
    {
      printUsage(_argv[0]);
      return 1;
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

  if (file->getNumberGames())
    viewer.viewGame(file->getGame(0), &writer);

  delete file;
  return 0;
}
