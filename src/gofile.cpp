#include <stdio.h>
#include <stdlib.h>
#include "gofile.h"

GoFile::GoFile()
{
}

GoFile::~GoFile()
{
  int i;
  for (i=0; i<(int)m_trees.size(); i++)
    free(m_trees[i]);
}


int GoFile::addGame(GameTree *_tree)
{
  m_trees.insert(m_trees.end(), _tree);
  return 1;
}

GameTree* GoFile::getGame(int _id)
{
  if (_id<0 || _id>=(int)m_trees.size())
    return NULL;
  return m_trees[_id];
}
