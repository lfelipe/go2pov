#ifndef __POV_WRITER_H__
#define __POV_WRITER_H__

#include "boardwriter.h"

/** This is a derived class from BoardWriter. So please look there
    for detailed documentation.*/
class PovWriter : public BoardWriter
{
 public:
  PovWriter();

  const char *getName() {return (const char *) m_name;}
  const char *getExtension() {return (const char *) m_extension;}

  void setFilename(char *_filename);
  void setExtension(char *_extension);

  int  writeBoard(GoBoard *_board);

 private:
  char  *m_name, *m_filename, *m_extension;
  float  m_thickness, m_boardheight;
};


#endif
