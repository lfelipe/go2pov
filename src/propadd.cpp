#include <stdlib.h>
#include <string.h>
#include "propadd.h"

PropAdd::PropAdd(Stone _c)
{
  m_color=_c;
  m_move = 1;
}

PropAdd::~PropAdd()
{
  reset();
}


int PropAdd::reset()
{
  free(m_ret);
  m_ret=NULL;
 
  x.erase(x.begin(), x.end());
  y.erase(y.begin(), y.end());
  return 1;
}

int PropAdd::add(int _x, int _y, bool _move)
{
  x.insert(x.end(),_x);
  y.insert(y.end(),_y);
  m_move=_move;
  return 1;
}

int PropAdd::getStone(int _id, int *_x, int *_y)
{
  if (_id<0 || _id>=(int)x.size())
    return 0;

  *_x=x[_id];
  *_y=y[_id];
  return 1;
}


const char *PropAdd::getAsString()
{
  char a, *b=NULL;
  int  i;

  if (m_color==white)
    a='w';
  else if (m_color==black)
    a='b';
  else a='n';

  free(m_ret);

  m_ret=(char *)malloc(strlen("addSton:") + 6*x.size() + 3);
  sprintf(m_ret, "addStone:%c:", a);
  
  for (i=0; i<(int)x.size(); i++)
    {
      b=strdup(" xx,yy");
      sprintf(b, " %02i,%02i", x[i],y[i]);
      strcat(m_ret,b);
      free(b);
      b=NULL;
    }
  return (const char *)m_ret;
}
