#include <stdio.h>
#include <stdlib.h>
#include "gamenode.h"

GameNode::GameNode()
{
}

GameNode::~GameNode()
{
  int i;
  for (i=0; i<(int)props.size(); i++)
    free(props[i]);
}

int GameNode::addProperty(NodeProperty *_n)
{
  if (_n==NULL) return 0;
  props.insert(props.end(), _n);
  return 1;
}

NodeProperty *GameNode::getProperty(int _id)
{
  if (_id<0 || _id >=(int)props.size())
    return NULL;

  return props[_id];
}

void GameNode::print(FILE *_fp)
{
  int i;
  for (i=0; i<(int)props.size(); i++)
    {
      fprintf(_fp, "%s\n", props[i]->getAsString());
    }
}
