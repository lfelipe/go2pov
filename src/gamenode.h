#ifndef __GAMENODE_H__
#define __GAMENODE_H__

#include <stdio.h>
#include <vector>
#include "nodeproperty.h"

using std::vector;

typedef vector<NodeProperty *> PropList;

/** A node is a single move/step in a game.
    Nodes can be commented or they can contain setup-infos.
    $Author: weasel75 $ (last changes), Hans-Peter Jacobs
    $Date: 2001/03/20 01:45:01 $ (last change), March 2001
*/
class GameNode
{
 public:
  GameNode();
  ~GameNode();

  /** Can be used to step thru the properties of
      a node.
      @return the number of properties stored in the node*/
  int getNumberProperties() {return (int)props.size();}

  /** Adds a property to the node.
      @param _p pointer to the new property
      @return "1" for success, "0" else*/
  int  addProperty(NodeProperty *_p);

  /** Returns the desired node from the list.
      @param _id index
      @return pointer to the property, NULL for failure*/
  NodeProperty *getProperty(int _id);

  /** Prints the contents of the current node.
      @param _fp pointer to a file-pointer (e.g. stderr, stdout)*/
  void print(FILE *_fp);

 protected:
  PropList  props;
};

#endif
