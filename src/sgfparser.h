#ifndef __SGF_PARSER_H__
#define __SGF_PARSER_H__

#include "gofile.h"
#include "goparser.h"

/** This is a Go_Parser for SGF-files. All games from a
    file will be stored in the GoFile - object.<br>
    GameTree is the tree of moves (nodes) of a game, while
    GameInfo contains informations about players, date,
    event, boardsize, etc..
    @author Hans-Peter Jacobs, last change : $Author: weasel75 $
    @date March 2001, last change: $Date: 2001/03/14 11:20:17 $
    @version $Revision: 1.1 $
*/
class SGFParser : public GoParser
{
 public:
  SGFParser();
  virtual ~SGFParser();

  GoFile     *parseFile(char *_filename);
  int         tryFile(char *_filename);
  const char *getName() {return (const char *) name;}

 private:
  char      getNextChar(char **_p1, char *_pe);
  GameTree *parseTree(char **_p1, char *_pe);
  GameNode *parseNode(char **_p1, char *_pe);
  int       parseProperty(char **_p1, char *_pe, char *_id, GameNode *_n);
  char     *name;
  GameInfo *m_info;
};

#endif
