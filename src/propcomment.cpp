#include <stdlib.h>
#include <string.h>
#include "propcomment.h"

PropComment::PropComment()
{
  m_string=NULL;
  m_ret=NULL;
}

PropComment::~PropComment()
{
  free(m_string);
  free(m_ret);
}


int PropComment::set(char *_s)
{
  free(m_string);
  m_string=strdup(_s);
  return 1;
}

const char *PropComment::getAsString()
{
  free(m_ret);
  m_ret=(char *)malloc(strlen("comment:") + strlen(m_string) + 2);
  strcpy(m_ret, "comment:");
  strcat(m_ret, m_string);
  return (const char *)m_ret;
}
