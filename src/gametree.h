#ifndef __GAMETREE_H__
#define __GAMETREE_H__

#include "gamenode.h"

/** This class contains a complete game.
    The tree stores all the moves, comments, etc..
    @date $Date: 2001/03/14 11:20:17 $
    @version $Revision: 1.1 $
    @author Hans-Peter Jacobs, last modification : $Author: weasel75 $
*/
class GameTree {
 public:
  ~GameTree();

  /** This function should be called instead of a constructor.
      If NULL is returned the initialization went wrong.
      @return Pointer to the new GameTree*/
  static GameTree *New();

  int getNumberVariations() {return nof_variations;}
  GameTree *getVariation(int _id);

  int getNumberNodes() {return nof_nodes;}
  GameNode *getNode (int _id);

  int addNode(GameNode *_node);
  int addVariation(GameTree *_tree);

 private:
  GameTree();
  int init();

  GameNode  **m_nodes;
  GameTree  **m_variations;
  int         nof_nodes, nof_variations;
};

#endif
