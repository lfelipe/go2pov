#include <stdio.h>
#include <stdlib.h>
#include "gametree.h"

GameTree::GameTree()
{
  m_nodes=NULL;
  nof_nodes=0;

  m_variations=NULL;
  nof_variations=0;
}


GameTree::~GameTree()
{
  int i;

  for (i=0; i<nof_nodes; i++)
    free(m_nodes[i]);

  for (i=0; i<nof_variations; i++)
    free(m_variations[i]);

  free(m_nodes);
  free(m_variations);
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
  GameNode **t;

  nof_nodes++;
  t=(GameNode **)realloc(m_nodes, sizeof(GameNode *) * nof_nodes);
  if (t==NULL) {m_nodes--;return 0;}

  m_nodes=t;
  m_nodes[nof_nodes-1]=_node;
  return 1;
}

GameNode *GameTree::getNode(int _id)
{
  if (_id<0 || _id>=nof_nodes)
    return NULL;
  return m_nodes[_id];
}


int GameTree::addVariation(GameTree *_tree)
{
  GameTree **t;

  nof_variations++;
  t=(GameTree **)realloc(m_variations, sizeof(GameTree *) * nof_variations);
  if (t==NULL) {m_variations--;return 0;}

  m_variations=t;
  m_variations[nof_variations-1]=_tree;
  return 1;
}

GameTree *GameTree::getVariation(int _id)
{
  if (_id<0 || _id>=nof_variations)
    return NULL;
  return m_variations[_id];
}
