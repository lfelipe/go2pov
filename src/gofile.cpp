#include <stdio.h>
#include <stdlib.h>
#include "gofile.h"

GoFile::GoFile()
{
  nof_games=0;
  m_infos=NULL;
  m_trees=NULL;
}

GoFile::~GoFile()
{
  int i;
  for (i=0; i<nof_games; i++)
    {
      free(m_infos[i]);
      free(m_trees[i]);
    }
  free(m_infos);
  free(m_trees);
}


int GoFile::addGame(GameTree *_tree, GameInfo *_info)
{
  GameTree **t;
  GameInfo **i;

  nof_games++;

  t=(GameTree **)realloc(m_trees, sizeof(GameTree *) * nof_games);
  i=(GameInfo **)realloc(m_infos, sizeof(GameInfo *) * nof_games);

  if (t==NULL || i==NULL) {
    nof_games--;
    free(i);
    free(t);
    return 0;
  }

  t[nof_games-1]=_tree;
  i[nof_games-1]=_info;
  m_trees=t;
  m_infos=i;
  
  return 1;
}
