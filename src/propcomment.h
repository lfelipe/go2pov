#ifndef __PROP_COMMENT_H__
#define __PROP_COMMENT_H__

#include "goboard.h"

class PropComment : public NodeProperty
{
 public:
  PropComment();

  const char *getName() {return "comment";}
  const char *getAsString();

  int set(char *_s);

 private:
  char  *m_string, *m_ret;
};


#endif
