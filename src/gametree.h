#ifndef __GAMETREE_H__
#define __GAMETREE_H__

#include <vector>
#include <stdio.h>
#include "gamenode.h"

/** This class contains a complete game.
    The tree stores all the moves, comments, etc..
    $Date: 2001/03/20 01:45:01 $ (last change), March 2001
    @version $Revision: 1.2 $
    $Author: weasel75 $ (last change), Hans-Peter Jacobs
*/
class GameTree {
 public:
  ~GameTree();

  /** This function should be called instead of a constructor.
      If NULL is returned the initialization went wrong.
      @return Pointer to the new GameTree*/
  static GameTree *New();

  int getNumberVariations() {return m_variations.size();}
  GameTree *getVariation(int _id);

  int getNumberNodes() {return m_nodes.size();}
  GameNode *getNode (int _id);

  int addNode(GameNode *_node);
  int addVariation(GameTree *_tree);

  void print(FILE *_fp);

  int size;

 private:
  GameTree();
  int init();

  vector<GameNode *> m_nodes;
  vector<GameTree *> m_variations;
};

#endif
