#ifndef __NODE_PROPERTY_H__
#define __NODE_PROPERTY_H__

class NodeProperty
{
 public:
  virtual ~NodeProperty() {};

  virtual const char *getAsString() = 0;
  virtual const char *getName() = 0;
};

#endif
