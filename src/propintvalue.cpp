#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "propintvalue.h"

PropIntValue::PropIntValue()
{
  m_name=NULL;
  m_ret=NULL;
  m_value=0;
}

PropIntValue::~PropIntValue()
{
  free(m_name);
  free(m_ret);
}


int PropIntValue::setName(char *_name)
{
  free(m_name);
  m_name=strdup(_name);
  return 1;
}

int PropIntValue::setValue(int _v)
{
  m_value=_v;
  return 1;
}

const char *PropIntValue::getAsString()
{
  char tmp[1024];
  free(m_ret);
  sprintf(tmp, "intval : %i", m_value);
  m_ret=strdup(tmp);
  return (const char *)m_ret;
}
