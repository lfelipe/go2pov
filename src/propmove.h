#ifndef __PROP_MOVE_H__
#define __PROP_MOVE_H__

#include "goboard.h"
#include "nodeproperty.h"

/** A move in GO is done by putting a stone at a specific
    position. The position is adressed by x,y-coords (regular size 19x19)
    $Author: weasel75 $ (last change), Hans-Peter Jacobs
    $Date: 2001/03/25 01:38:44 $ (last change), March 2001
*/
class PropMove : public NodeProperty
{
 public:
  PropMove();
  ~PropMove();

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
