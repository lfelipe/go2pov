#ifndef __PARSER_H__
#define __PARSER_H__

#define MAXPARSER 100
#include "gofile.h"
#include "goparser.h"

using namespace std;

/** The parser, the reader of a Go-file. This parser
    will instantiate the objects of available parsers
    of the abstract GoParser. The GoParser can be SGF
    or any other type of parser.

    @author Hans-Peter Jacobs, last change : $Author: weasel75 $
    @date March 2001, last change: $Date: 2001/03/14 11:20:17 $
    @version $Revision: 1.1 $
*/
class Parser
{
 public:
  /** You should use this static constructor.*/
  static Parser *New();

  /** Destructor.*/
  ~Parser();

  /** Will read the file if possible.
      @param _filename name of the file
      @return "1" if success, "0" else*/
  GoFile *parseFile(char *_filename);

 private:
  /** Constructor.*/
  Parser();

  /** Must be called right after construction.*/
  int init();

  GoParser *parserlist[MAXPARSER];
  int       parsercount;
};

#endif
