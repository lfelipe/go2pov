#include <stdio.h>
#include <stdlib.h>
#include "gametree.h"

GameTree::GameTree()
{
  size=0;
}


GameTree::~GameTree()
{
  int i;

  for (i=0; i<(int)m_nodes.size(); i++)
    free(m_nodes[i]);

  for (i=0; i<(int)m_variations.size(); i++)
    free(m_variations[i]);
}


int GameTree::init()
{
  return 1;
}


GameTree *GameTree::New()
{
  GameTree *tree=new GameTree();

  if (!tree->init())
    {
      delete tree;
      return NULL;
    }
  return tree;
}

int GameTree::addNode(GameNode *_node)
{
  if (_node==NULL) return 0;
  m_nodes.insert(m_nodes.end(), _node);
  return 1;
}

GameNode *GameTree::getNode(int _id)
{
  if (_id<0 || _id>=(int)m_nodes.size())
    return NULL;
  return m_nodes[_id];
}


int GameTree::addVariation(GameTree *_tree)
{
  if (_tree==NULL) return 0;
  m_variations.insert(m_variations.end(), _tree);
  return 1;
}

GameTree *GameTree::getVariation(int _id)
{
  if (_id<0 || _id>=(int)m_variations.size())
    return NULL;
  return m_variations[_id];
}

void GameTree::print(FILE *_fp)
{
  int i;
  fprintf(_fp," Printing %i nodes, %i variations\n", m_nodes.size(), m_variations.size());
  for (i=0; i<(int)m_nodes.size(); i++)
    m_nodes[i]->print(_fp);
  for (i=0; i<(int)m_variations.size(); i++)
    m_variations[i]->print(_fp);
}
