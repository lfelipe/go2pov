#include <stdio.h>
#include <stdlib.h>
#include "gamenode.h"

GameNode::GameNode()
{
  comment=NULL;
}

GameNode::~GameNode()
{
  free(comment);
}
