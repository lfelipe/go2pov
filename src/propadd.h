#ifndef __PROP_ADD_H__
#define __PROP_ADD_H__

#include <vector>
#include "goboard.h"
#include "nodeproperty.h"

class PropAdd : public NodeProperty
{
 public:
  PropAdd(Stone _c);
  ~PropAdd();

  const char *getName() {return (const char *)"add";}
  const char *getAsString();

  int add(int _x, int _y, bool _move=true);
  int reset();

  void  setColor(Stone _c) {m_color=_c;}
  Stone getColor() {return m_color;}

  int getNumberStones() {return x.size();}
  int getStone(int _id, int *_x, int *_y);

  bool isMove() {return m_move;}
 private:
  char  *m_ret;
  Stone  m_color;
  bool   m_move;
  vector<int> x;
  vector<int> y;

};


#endif
