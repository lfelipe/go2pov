#ifndef __GOFILE_H__
#define __GOFILE_H__

#include <vector>
#include "gametree.h"
#include "gameinfo.h"

/** This is a collection of all games within a GO-file.
    If there are more than one games stored (possible in SGF)
    this object will have the number and the pointers to them.
    @author Hans-Peter Jacobs, last change : $Author: weasel75 $
    @date March 2001, last change: $Date: 2001/03/20 01:45:01 $
    @version $Revision: 1.2 $
*/
class GoFile
{
 public:
  GoFile();
  ~GoFile();

  int getNumberGames() {return (int)m_trees.size();}
  GameTree *getGame(int _id);
  GameInfo *getGameInfo(int _id);

  int addGame(GameTree *_tree);

 private:
  vector<GameTree*> m_trees;
};

#endif
