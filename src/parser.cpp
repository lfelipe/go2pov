#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "sgfparser.h"


Parser::Parser()
{
  parsercount=0;
}


int Parser::init()
{
  GoParser *t;

  // SGF
  t=new SGFParser;
  parserlist[parsercount]=t;
  parsercount++;

  return 1;
}

Parser *Parser::New()
{
  Parser *p=new Parser;
  if (!p->init())
    {
      delete p;
      return NULL;
    }
  return p;
}


Parser::~Parser()
{
  int i;
  for (i=0; i<parsercount; i++)
    free(parserlist[i]);
  parsercount=0;
}


GoFile *Parser::parseFile(char *_filename)
{
  int i;
  GoFile *file=NULL;

  for (i=0; i<parsercount; i++)
    {
      if (!parserlist[i]->tryFile(_filename))
	continue;

      fprintf(stderr, "found parser : %s\n", parserlist[i]->getName());
      file=parserlist[i]->parseFile(_filename);
      return file;
    }
  return NULL;
}
