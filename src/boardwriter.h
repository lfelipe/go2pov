#ifndef __BOARD_WRITER_H__
#define __BOARD_WRITER_H__

#include "goboard.h"

/** This is the virtual class for all
    "Board-Writers". This means, that the childs of
    this class just need to write a board-position,
    without the knowledge of the whole game.
@author Hans-Peter Jacobs, last change: $Author: weasel75 $
@date March 2001, last change: $Date: 2001/03/15 02:29:22 $ */
class BoardWriter
{
 public:
  /** Returns the name of the writer.*/
  virtual const char *getName() = 0;

  /** Each writer must have a default-extension. However, with
      this function the user should be able to change this extension.
      @param _extension new extension for this writer.*/
  virtual void setExtension(char *_extension) = 0;

  /** Return the current extension of the writer.
   @return pointer to a string*/
  virtual const char *getExtension() = 0;

  /** Writes a goboard into a file.
      @param _board pointer to a GoBoard
      @param _filename filename without the "." and the extension
      @return "1" on success, "0" else*/
  virtual int writeBoard(GoBoard *_board, char *_filename) = 0;
};

#endif
