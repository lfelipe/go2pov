#ifndef __GAMEVIEWER_H__
#define __GAMEVIEWER_H__

#include "gametree.h"
#include "boardwriter.h"

/** Prototype for viewing a game. While stepping thrue
    the game the user can select to write the current
    board-state to a file,
    $Author: weasel75 $ (last change)
    Hans-Peter Jacobs
    $Date: 2001/03/19 02:05:30 $ (last change)
    written March 2001
*/
class GameViewer
{
 public:
  virtual int viewGame(GameTree *_game, BoardWriter *_writer) = 0;
};

#endif
