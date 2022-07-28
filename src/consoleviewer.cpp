#include "consoleviewer.h"
#include "propadd.h"
#include "propintvalue.h"
#include "propmove.h"
#include "propstring.h"

ConsoleViewer::ConsoleViewer()
{
  m_board=NULL;
}

int ConsoleViewer::viewGame(GameTree *_tree, BoardWriter *_writer, int steps)
{
  GoBoard       board;
  GameNode     *node;
  NodeProperty *prop;
  PropAdd      *pa;
  GameTree     *tree;
  Stone         c;
  int           i, j, done, x,y;
  char          a, *s;
  bool		limited_steps = false;
  

  if (steps > 0) limited_steps = true;
  //_tree->print(stderr); getchar();
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
      s=(char *)prop->getName();
      if (strcmp("boardsize",s)==0)
	{
	  fprintf(stderr, "BoardSize\n");
	  board.setSize(((PropIntValue*)prop)->getValue());
	}
    }

  
  fprintf(stderr, "boardsize : %i\n", board.getSize());

  done=0;
  i=0;
  tree=_tree;
  while(!done)
    {

      // if no more properties, check variations .. if no variations -> end of game
      while (i >= tree->getNumberNodes())
	{
	  i=0;
	  if (tree->getNumberVariations() < 1);
	    {done=1; break;}
	  tree=tree->getVariation(0);
	}
      if (done) break;

      node=tree->getNode(i);
      //fprintf(stderr, "%i properties\n", node->getNumberProperties());
      for(j=0; j < node->getNumberProperties(); j++)
	{
	  prop=node->getProperty(j);

	  if (strcmp("add", prop->getName()) == 0)
	    {
	      pa=(PropAdd *)prop;
	      c=pa->getColor();
	      fprintf(stderr, "adding %i stones: ", pa->getNumberStones());
	      for (j=0; j<pa->getNumberStones(); j++)
		{
		  pa->getStone(j, &x,&y);
		  board.addStone(c,x,y);
		  fprintf(stderr, "%i,%i ",x,y);
		}
	      fprintf(stderr, "\n");
	      continue;
	    }

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
	      continue;
	    }
	  if (strcmp("comment",prop->getName())==0)
	    {
	      s=(char *)((PropString *)prop)->get();
	      fprintf(stderr, "Comment :\n%s\n", s);
	      continue;
	    }
	}
      board.print(stdout);
      if (limited_steps) {
	      if (steps) {
		      steps--;
		      i++;
		      continue;
	      } else {
		      _writer->writeBoard(&board);fprintf(stderr, "Saving...\n");
		      _writer->writeBoardStatus(&board);
		      return 1;
	      }
      }
      a=getchar();
      if (a=='q') {done=1;}
      if (a=='s') {_writer->writeBoard(&board);fprintf(stderr, "Saving...\n");}
      i++;
    }

  return 1;
}
