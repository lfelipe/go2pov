#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "gametree.h"


void printUsage(char *_comline)
{
  char *a=strrchr(_comline, '/');

  fprintf(stderr, "usage: %s <go-file>\n", (a==NULL) ? _comline : a);
}


int main(int _argc, char *_argv[])
{
  Parser   *parser=Parser::New();
  GoFile   *file=NULL;

  if (_argc < 2)
    {
      printUsage(_argv[0]);
      return 0;
    }
  file=parser->parseFile(_argv[1]);

  delete parser;
  delete file;

  return 1;
}
