#include "consoleviewer.h"
#include "propintvalue.h"
#include "propmove.h"
#include "propstring.h"

ConsoleViewer::ConsoleViewer()
{
  m_board=NULL;
}

int ConsoleViewer::viewGame(GameTree *_tree, BoardWriter *_writer)
{
  GoBoard       board;
  GameNode     *node;
  NodeProperty *prop;
  GameTree     *tree;
  Stone         c;
  int           i, j, done, x,y;
  char          a, *s;
  
  board.setSize(19);
  if (_tree->getNumberNodes()<1)
    {
      fprintf(stderr, "root appears to be empty\n");
      return 0;
    }

  node=_tree->getNode(0);
  fprintf(stderr, "root has %i properties\n", node->getNumberProperties());
  for(i=0; i<node->getNumberProperties(); i++)
    {
      prop=node->getProperty(i);
      if (strcmp("boardsize",prop->getName())==0)
	board.setSize(((PropIntValue*)prop)->getValue());
    }

  
  fprintf(stderr, "boardsize : %i\n", board.getSize());

  done=0;
  i=0;
  tree=_tree;
  while(!done)
    {

      while (i >= tree->getNumberNodes())
	{
	  i=0;
	  j=tree->getNumberVariations();
	  if (j<1)
	    {done=1; break;}
	  tree=tree->getVariation(0);
	}
      if (done) break;

      node=tree->getNode(i);
      for(j=0; j < node->getNumberProperties(); j++)
	{
	  prop=node->getProperty(j);
	  if (strcmp("move",prop->getName())==0)
	    {
	      c=((PropMove *)prop)->get(&x, &y);
	      if (x<0 || y<0 || x>=board.getSize() || y>=board.getSize())
		{
		  fprintf(stderr, "Pass !\n");
		} else {
		  board.addStone(c,x,y);
		  if (board.get(x-1,y)!=c && board.getLiberties(x-1,y)==0)
		    {
		      fprintf(stderr, "killing at %i,%i\n", x-1,y);
		      board.removeGroup(x-1,y);
		    }
		  if (board.get(x+1,y)!=c && board.getLiberties(x+1,y)==0)
		    {
		      fprintf(stderr, "killing at %i,%i\n", x+1,y);
		      board.removeGroup(x+1,y);
		    }
		  if (board.get(x,y-1)!=c && board.getLiberties(x,y-1)==0)
		    {
		      fprintf(stderr, "killing at %i,%i\n", x,y-1);
		      board.removeGroup(x,y-1);
		    }
		  if (board.get(x,y+1)!=c && board.getLiberties(x,y+1)==0)
		    {
		      fprintf(stderr, "killing at %i,%i\n", x,y+1);
		      board.removeGroup(x,y+1);
		    }
		  // assume suicide if no liberties
		  if (board.getLiberties(x,y)==0)
		    {
		      fprintf(stderr, "suicide at %i,%i\n", x,y);
		      board.removeGroup(x,y);
		    }
		}
	    }
	  if (strcmp("comment",prop->getName())==0)
	    {
	      s=(char *)((PropString *)prop)->get();
	      fprintf(stderr, "Comment :\n%s\n", s);
	    }
	}
      board.print(stdout);
      a=getchar();
      if (a=='q') {done=1;}
      if (a=='s') {_writer->writeBoard(&board);fprintf(stderr, "Saving...\n");}
      i++;
    }

  return 1;
}
