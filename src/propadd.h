#ifndef __PROP_ADD_H__
#define __PROP_ADD_H__

#include "goboard.h"

class PropAdd : public NodeProperty
{
 public:
  PropAdd();

  const char *getName() {return "add";}
  const char *getAsString();

  int add(Stone _color, int _x, int _y);
  int reset();

  void  setColor(Stone _c) {m_color=_c;}
  Stone getColor() {return m_color;}

  int getNOF() {return nof_stones;}
  int getStone(int _id, int *_x, int *_y);

 private:
  char  *m_ret;
  Stone  m_color;
  int   *x, *y;
  int    nof_stones;
};


#endif
