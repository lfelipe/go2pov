#include <stdlib.h>
#include <stdio.h>
#include "goboard.h"

GoBoard::GoBoard()
{
  m_size=-1;
  m_board=NULL;
}

int GoBoard::setSize(int _newsize)
{
  int x, y;

  if (m_board && m_size>0)
    {
      for (x=0; x<m_size; x++)
	free(m_board[x]);
    }
  free(m_board);

  if (_newsize<1) return 0;

  m_size=_newsize;
  m_board=(Stone **)malloc(sizeof(Stone *) * m_size);
  for (x=0; x<m_size; x++)
    {
      m_board[x]=(Stone *)malloc(sizeof(Stone) * m_size);
      for (y=0; y<m_size; y++)
	m_board[x][y]=empty;
    }

  return 1;
}


int GoBoard::addStone(Stone _color, int _x, int _y)
{
  if (_x<0 || _x>=m_size || _y<0 || _y>=m_size)
    return 0;
  m_board[_x][_y]=_color;
  return 1;
}


int GoBoard::delStone(int _x, int _y)
{
  if (_x<0 || _x>=m_size || _y<0 || _y>=m_size)
    return 0;
  m_board[_x][_y]=empty;
  return 1;
}

void GoBoard::print(FILE *_fp)
{
  int x,y;

  for (y=0; y<m_size; y++)
    {
      for(x=0; x<m_size; x++)
	{
	  if (m_board[x][y]==empty)
	    fprintf(_fp, ".");
	  else if (m_board[x][y]==black)
	    fprintf(_fp, "x");
	  else
	    fprintf(_fp, "o");
	}
      fprintf(_fp,"\n");
    }
}


Stone GoBoard::get(int _x, int _y)
{
  if (_x<0 || _x>=m_size || _y<0 || _y>=m_size)
    return empty;
  return m_board[_x][_y];
}
