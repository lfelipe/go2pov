#include <stdio.h>
#include <stdlib.h>
#include "gameinfo.h"

GameInfo::GameInfo()
{
  comment=NULL;
  date=NULL;
  place=NULL;
  player1=NULL;
  player2=NULL;
}


GameInfo::~GameInfo()
{
  free(comment);
  free(date);
  free(place);
  free(player1);
  free(player2);
}
