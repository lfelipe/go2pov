#include "propadd.h"

PropAdd::PropAdd()
{
  m_color=empty;
  x=NULL;
  y=NULL;
  nof_stones=0;
}

PropMove::~PropMove()
{
  reset();
}


int PropMove::reset()
{
  free(x);
  free(y);
  free(m_ret);
  x=NULL;
  y=NULL;
  m_ret=NULL;
  m_color=undefined;
  nof_stones=0;
  return 1;
}

int PropMove::add(int _x, int _y)
{
  int *xt, *yt;

  xt=(int *)realloc(x, sizeof(int) * (nof_stones + 1));
  yt=(int *)realloc(y, sizeof(int) * (nof_stones + 1));

  if (xt==NULL || yt==NULL)
    {
      free(xt); free(yt);
      return 0;
    }
  x=xt;
  y=yt;
  x[nof_stones]=_x;
  y[nof_stones]=_y;
  nof_stones++;
  return 1;
}

int PropMove::get(int _id, int *_x, int *_y)
{
  if (_id<0 || _id>=nof_stones)
    return 0;

  *_x=x[_id];
  *_y=y[_id];
  return 1;
}


const char *PropMove::getAsString()
{
  char a, *b=NULL;

  if (m_color==white)
    a='w';
  else if (m_color==black)
    a='b';
  else a='n';

  free(m_ret);

  m_ret=(char *)malloc(strlen("addSton:") + 6*nof_stones + 3);
  sprintf(m_ret, "addStone:%c:", a);
  
  for (i=0; i<nof_stones; i++)
    {
      b=strdup(" xx,yy");
      sprintf(b, " %02i,%02i", x[i],y[i]);
      strcat(m_ret,b);
      free(b);
      b=NULL;
    }
  return (const char *)m_ret;
}
