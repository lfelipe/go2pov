#include <stdlib.h>
#include <string.h>
#include "propstring.h"

PropString::PropString()
{
  m_name=NULL;
  m_string=NULL;
  m_ret=NULL;
}

PropString::~PropString()
{
  free(m_name);
  free(m_string);
  free(m_ret);
}


void PropString::setName(char *_n)
{
  free(m_name);
  m_name=strdup(_n);
}

int PropString::set(char *_s)
{
  free(m_string);
  m_string=strdup(_s);
  return 1;
}

const char *PropString::getAsString()
{
  free(m_ret);
  m_ret=(char *)malloc(strlen(m_name) + strlen(m_string) + 3);
  strcpy(m_ret, m_name);
  strcat(m_ret,": ");
  strcat(m_ret, m_string);
  return (const char *)m_ret;
}
