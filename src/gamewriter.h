#ifndef __GAME_WRITER_H__
#define __GAME_WRITER_H__

#include "gametree.h"

/** This is just a virtual class. Maybe later someone wants
    to add conversion to go2pov.*/
class GameWriter
{
 public:
  virtual writeGame(GameTree *_tree) = 0;
  virtual const char *getExtension() = 0;
  virtual setFilename(char *_name) = 0;
};


#endif
