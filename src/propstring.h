#ifndef __PROP_STRING_H__
#define __PROP_STRING_H__

#include "goboard.h"
#include "nodeproperty.h"

class PropString : public NodeProperty
{
 public:
  PropString();
  ~PropString();

  void setName(char *_name);
  const char *getName() {return m_name;}

  int set(char *_s);
  const char *get() {return (const char *)m_string;}

  const char *getAsString();

 private:
  char  *m_name, *m_string, *m_ret;
};


#endif
