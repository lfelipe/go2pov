#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "gametree.h"
#include "povwriter.h"

void printUsage(char *_comline)
{
  char *a=strrchr(_comline, '/');

  fprintf(stderr, "usage: %s <go-file>\n", (a==NULL) ? _comline : a);
}


int main(int _argc, char *_argv[])
{
  Parser    *parser=Parser::New();
  GoFile    *file=NULL;
  PovWriter  writer;
  GoBoard    board;
  int        i;

  if (_argc < 2)
    {
      printUsage(_argv[0]);
      return 0;
    }

  // test parser
  file=parser->parseFile(_argv[1]);
  delete parser;
  delete file;

  // test the board
  board.setSize(19);
  /*
  for (i=0; i<19; i++)
    {
      if (i%2)
	{
	  board.addStone(white,i,i);
	  board.addStone(white,i,18-i);
	  board.addStone(white,i,0);
	}
      else
	{
	  board.addStone(black,i,i);
	  board.addStone(black,i,18-i);
	  board.addStone(black,0,i);
	}
	}*/
  board.addStone(black,3,1);
  board.addStone(black,3,2);
  board.addStone(white,2,2);
  board.print(stdout);

  // test the board-writer
  writer.writeBoard(&board, "test");

  return 1;
}
