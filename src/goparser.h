#ifndef __GO_PARSER_H__
#define __GO_PARSER_H__

#include "gofile.h"

/** This class defines, how a GoParser should look like.
    @date $Date: 2001/03/14 11:20:17 $
    @version $Revision: 1.1 $
    @author Hans-Peter Jacobs, last modification : $Author: weasel75 $
*/
class GoParser
{
 public:
  /** This function takes a file and will generate a gametree from this
      file (if possible).
      @param _filename name of the file to be parsed
      @return a pointer to the gametree, NULL if the parser failed*/
  virtual GoFile *parseFile(char *_filename) = 0;

  /** This function will check the filename or the contents itself for
      grammar. So it will return "1" if the parser can understand the format.
      @param _filename filename of the file to be tested
      @return 1 for a parseable file, 0 else*/
  virtual int tryFile(char *_filename) = 0;

  /** Will return the name of the name of the parser.
      @return pointer to a constant string*/
  virtual const char *getName() = 0;
};

#endif
