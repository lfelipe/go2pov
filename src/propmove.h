#ifndef __PROP_MOVE_H__
#define __PROP_MOVE_H__

#include "goboard.h"

class PropMove : public NodeProperty
{
 public:
  PropMove();

  const char *getName() {return "move";}
  const char *getAsString();

  int set(Stone _color, int _x, int _y);
  Stone get(int *_x, int *_y);

 private:
  char   m_string[13];
  Stone  m_color;
  int    x,y;
};


#endif
