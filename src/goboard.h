#ifndef __GO_BOARD_H__
#define __GO_BOARD_H__

#include <stdio.h>

/// Enum for the stones
enum Stone {empty=0, black=1, white=2};

/** This class stores a board. Its just stored "static", so
    by looking at the board you will see the current game-state.
    @author Hans-Peter Jacobs, last change: $Author: weasel75 $
    @date March 2001, last change: $Date: 2001/03/15 02:29:22 $*/
class GoBoard
{
 public:
  GoBoard();

  int setSize(int _newsize);

  int addStone(Stone _color, int _x, int _y);
  int delStone(int _x, int _y);

  void print(FILE *_fp);

 private:
  int     m_size;
  Stone **m_board;
};

#endif