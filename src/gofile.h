#ifndef __GOFILE_H__
#define __GOFILE_H__

#include "gametree.h"
#include "gameinfo.h"

//#include <vector>
//using namespace std;

/** This is a collection of all games within a GO-file.
    If there are more than one games stored (possible in SGF)
    this object will have the number and the pointers to them.
    @author Hans-Peter Jacobs, last change : $Author: weasel75 $
    @date March 2001, last change: $Date: 2001/03/14 11:20:17 $
    @version $Revision: 1.1 $
*/
class GoFile
{
 public:
  GoFile();
  ~GoFile();

  int getNumberGames() {return nof_games;}
  GameTree *getGame(int _id);
  GameInfo *getGameInfo(int _id);

  int addGame(GameTree *_tree, GameInfo *_info);

 private:
  GameInfo **m_infos;
  GameTree **m_trees;
  int        nof_games;

  //vector<GameInfo *>infos;
};

#endif
