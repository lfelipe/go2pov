#include "propmove.h"

PropMove::PropMove()
{
  m_color=empty;
  x=0;y=0;
}

PropMove::~PropMove()
{
}


int PropMove::set(Stone _color, int _x, int _y)
{
  m_color=_color;
  x=_x;
  y=_y;
  return 1;
}

Stone PropMove::get(int *_x, int *_y)
{
  *_x=x;
  *_y=y;
  return m_color;
}


const char *PropMove::getAsString()
{
  char a;

  if (m_color==white)
    a='w';
  else if (m_color==black)
    a='b';
  else a='n';

  sprintf(m_string, "%c:%02i,%02i", a,x,y);

  return (const char *)m_string;
}
