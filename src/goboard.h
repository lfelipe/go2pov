#ifndef __GO_BOARD_H__
#define __GO_BOARD_H__

#include <stdio.h>

/// Enum for the stones
enum Stone {empty=0, black=1, white=2};

/** This class stores a board. Its just stored "static", so
    by looking at the board you will see the current game-state.
    $Author: weasel75 $ (last change), Hans-Peter Jacobs
    $Date: 2001/03/20 09:47:16 $ (last change), March 2001*/
class GoBoard
{
 public:
  GoBoard();


  int addStone(Stone _color, int _x, int _y);
  int delStone(int _x, int _y);

  int setSize(int _newsize);
  int getSize() {return m_size;}

  int getLiberties(int _x, int _y);
  int removeGroup(int _x, int _y);

  void print(FILE *_fp);
  Stone get(int _x, int _y);

 private:
  int     m_size;
  Stone **m_board;
};

#endif
