#ifndef __GAMEINFO_H__
#define __GAMEINFO_H__

/** This stores all the little infos of a game.
    @author Hans-Peter Jacobs, last change : $Author: weasel75 $
    @date March 2001, last change: $Date: 2001/03/14 11:20:18 $
    @version $Revision: 1.1 $
*/
class GameInfo
{
 public:
  GameInfo();
  ~GameInfo();

  char *player1, *player2;
  char *place, *date;
  char *comment;
  int   boardsize;
};

#endif
