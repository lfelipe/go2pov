#ifndef __CONSOLE_VIEWER_H__
#define __CONSOLE_VIEWER_H__

#include <string.h>
#include "gameviewer.h"

class ConsoleViewer
{
 public:
  ConsoleViewer();

  int viewGame(GameTree *_game, BoardWriter *_writer, int steps);

 private:
  GoBoard *m_board;
};

#endif
