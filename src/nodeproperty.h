#ifndef __NODE_PROPERTY_H__
#define __NODE_PROPERTY_H__

/** A node consists of properties. Normally
    each node has one move stored.
    $Author: weasel75 $ (last change), Hans-Peter Jacobs
    $Date: 2001/03/20 01:45:01 $ (last change), March 2001
*/
class NodeProperty
{
 public:
  virtual ~NodeProperty() {};

  /** Returns the name of the property. This can be used for
      finding out, what type of object it is. So the
      GameNode can store a list of properties and the viewer
      can request one by one to evaluate this properties.
      @return pointer to a string, do not try to modify the string*/
  virtual const char *getName() = 0;

  /** Returns the contents of the property. The object itself
      has to format the string. This can be used to debug
      the gametree or for a logfile.
      @return pointer to the formated contents*/
  virtual const char *getAsString() = 0;
};

#endif
