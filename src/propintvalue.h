#ifndef __PROP_INTVAL_H__
#define __PROP_INTVAL_H__

#include "nodeproperty.h"

class PropIntValue : public NodeProperty
{
 public:
  PropIntValue();
  ~PropIntValue();

  const char *getName() {return (const char *)m_name;}
  const char *getAsString();
  int getValue() {return m_value;}

  int setValue(int _value);
  int setName(char *_name);

 protected:
  char *m_name, *m_ret;
  int  m_value;

};

#endif
