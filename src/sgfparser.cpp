#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgfparser.h"
#include "propcomment.h"
#include "propintvalue.h"
#include "propmove.h"
#include "propstring.h"

SGFParser::SGFParser()
{
  name=strdup("SGF-Parser");
}


SGFParser::~SGFParser()
{
  free(name);
}


int SGFParser::tryFile(char *_filename)
{
  if (strstr(_filename, ".sgf")!=NULL)
    return 1;
  if (strstr(_filename, ".SGF")!=NULL)
    return 1;
  return 0;
}


char SGFParser::getNextChar(char **_p1, char *_pe)
{
  char *p;

  if (*_p1==_pe) return 0;

  p=*_p1;
  while(*p<=32 && p!=_pe)
    p++;


  *_p1=p+1;
  if (p+1==_pe)
    return 0;
  if (p==_pe)
    {
      *_p1=p;
      return 0;
    }
  else return *p;
}



GoFile *SGFParser::parseFile(char *_filename)
{
  FILE     *fp;
  GoFile   *file=new GoFile();
  long int  length;
  char      *m1, *p1, *pe, done;

  // copy file to memory
  fp=fopen(_filename, "rt");
  if (fp==NULL)
    {
      fprintf(stderr, "Cant open the input-file '%s'.\n", _filename);
      return NULL;
    }
  fseek(fp,0,2);
  length=ftell(fp);
  fseek(fp,0,0);
  m1=(char *)malloc(length);
  fread(m1,1,length,fp);
  fclose(fp);

  // parse all available games from the file
  done=0;
  p1=m1;
  pe=p1+length;
  while(!done)
    {
      m_info=new GameInfo();
      root=GameTree::New();
      root=parseTree(&p1, pe);
      if (root==NULL)
	{
	  delete m_info;
	  done=1;
	} else {
	  file->addGame(root);
	  fprintf(stderr,"GameTree added\n");
	}
    }  
  return file;
}


GameTree *SGFParser::parseTree(char **_p1, char *_pe)
{
  GameTree *tree=NULL;
  GameTree *t;
  GameNode *n;
  char     a, *p1, *p2, done, splitted=0;

  done=0;
  p1=*_p1;

  // find start of the tree
  a=getNextChar(&p1, _pe);
  while(a!='(')
    {
      a=getNextChar(&p1, _pe);
      if (a==0) return NULL;
    }

  // parse tree
  fprintf(stderr, "Tree opened '%c'\n", a);
  tree=GameTree::New();
  done=0;
  while(!done && p1!=_pe)
    {
      p2=p1;
      a=getNextChar(&p1, _pe);
      //if (a==0) {done=1; continue;}
      switch(a)
	{
	case ';':
	  if (splitted)
	    {
	      fprintf(stderr, "Found a node after a tree-split !!\n");
	      return NULL;
	    }
	  n=parseNode(&p1, _pe);
	  if (p1==_pe) done=1;
	  else
	    {
	      tree->addNode(n);
	    }
	  break;
	case '(':
	  p1=p2;
	  splitted=1;
	  t=parseTree(&p1,_pe);
	  if (t==NULL || p1==_pe) done=1;
	  else
	    {
	      tree->addVariation(t);
	    }
	  break;
	case ')':
	  fprintf(stderr, "Tree closed\n");
	  done=1;
	  break;
	case '\0':
	  done=1;
	  break;
	default:
	  fprintf(stderr,"Found an error ... (%i, %x, %c)", a,a,a);  delete tree;  return NULL;
	}
    }
  *_p1=p1;
  return tree;
}

GameNode *SGFParser::parseNode(char **_p1, char *_pe)
{
  GameNode *n=new GameNode();
  char a,*p1, *p2, done, pi[3], nof_pi=0;

  //  fprintf(stderr, "  Parsing Node\n");
  p1=*_p1;
  done=0;
  pi[0]=0;
  pi[1]=0;
  pi[2]=0;
  while(!done && p1!=_pe)
    {
      p2=p1;
      a=getNextChar(&p1, _pe);
      switch(a)
	{
	case ')':
	case '(':
	case ';':
	  p1=p2;
	  //fprintf(stderr, "    breaking -> found '%c'\n", a);
	  done=1;
	  break;
	case '[':
	  p1=p2;
	  parseProperty(&p1, _pe, pi, n);
	  nof_pi=0;
	  pi[0]=0;
	  pi[1]=0;
	  pi[2]=0;
	  break;
	default:
	  if (a>='A' && a<='Z')
	    pi[nof_pi++]=a;
	  //fprintf(stderr, "%c", a);
	}
    }
  *_p1=p1;
  return n;
}


int SGFParser::parseProperty(char **_p1, char *_pe, char *_id, GameNode *_n)
{
  char *p1, *p2, *p3, opened, untouched, done;

  p1=*_p1;
  p2=p1;
  //fprintf(stderr, "      parsing PropID: %s -> ", _id);

  untouched=1;
  opened=0;
  done=0;
  while(p1!=_pe && !done)
    {
      if (opened)
	{
	  if (*p1==']' && *(p1-1)!='\\')
	    opened--;
	} else if (!opened && *p1=='[')
	  {
	    opened++;
	    untouched=0;
	  } else if (!opened && *p1!=32) done=1;
      if (!done) p1++;
    }

  p3=(char *)malloc(p1-p2+1);
  memcpy(p3,p2, p1-p2);
  p3[p1-p2]=0;
  //fprintf(stderr, "%s\n", p3);
  evalProperty(_n, _id, p3);
  free(p3);

  *_p1=p1;
  return 1;
}

int SGFParser::evalProperty(GameNode *_n, char *_id, char *_s)
{
  PropComment  *pc;
  PropIntValue *pi;
  PropMove     *pm;
  PropString   *ps;
  int           x,y;

  switch (_id[0])
    {
    case 'A':
      switch (_id[1])
	{
	case 'B':
	  fprintf(stderr, "Add black -> %s\n", _s);
	  return 1;
	case 'E':
	  fprintf(stderr, "Remove Stones -> %s\n", _s);
	  return 1;
	case 'W':
	  fprintf(stderr, "Add white -> %s\n", _s);
	  return 1;
	default:
	  return 0;
	}
    case 'B':
      switch (_id[1])
	{
	case 0:
	  fprintf(stderr, "Black move -> %s\n", _s);
	  pm=new PropMove();
	  // check for a pass of the player
	  if (_s[1]==']')
	    {
	      x=root->size;
	      y=root->size;
	    } else {
	      if (_s[1] <= 'Z' && _s[1]>='A')
		x=_s[1]-'A' + 26;
	      else
		x=_s[1]-'a';

	      if (_s[2] <= 'Z' && _s[2]>='A')
		y=_s[2]-'A' + 26;
	      else
		y=_s[2]-'a';
	    }
	  pm->set(black, x,y);
	  _n->addProperty(pm);
	  return 1;
	case 'M':
	  fprintf(stderr, "Bad move\n");
	  return 1;
	default:
	  return 0;
	}
    case 'C':
      switch (_id[1])
	{
	case 0:
	  //fprintf(stderr, "Comment -> %s\n", _s);
	  ps=new PropString;
	  ps->setName("comment");
	  ps->set(_s);
	  _n->addProperty(ps);
	  return 1;
	default:
	  return 0;
	}
    case 'D':
      switch(_id[1])
	{
	case 'O':
	  fprintf(stderr, "Doubtful move\n");
	  return 1;
	default:
	  return 0;
	}
    case 'G':
      switch(_id[1])
	{
	case 'B':
	  fprintf(stderr, "Good black move\n");
	  return 1;
	case 'M':
	  fprintf(stderr, "Game : %s\n", _s);
	  return 1;
	case 'W':
	  fprintf(stderr, "Good white move\n");
	  return 1;	  
	default:
	  return 0;
	}
    case 'H':
      switch (_id[1])
	{
	case 'O':
	  fprintf(stderr, "HotSpot !\n");
	  return 1;
	default:
	  return 0;
	}
    case 'I':
      switch (_id[1])
	{
	case 'T':
	  fprintf(stderr, "Interesting\n");
	  return 1;
	default:
	  return 0;
	}
    case 'N':
      switch(_id[1])
	{
	case 0:
	  fprintf(stderr, "Nodename -> %s\n", _s);
	  ps=new PropString;
	  ps->setName("nodename");
	  ps->set(_s);
	  _n->addProperty(ps);
	  return 1;
	default:
	  return 0;
	}
    case 'S':
      switch(_id[1])
	{
	case 'Z':
	  fprintf(stderr, "Size : %s\n", _s);
	  sscanf(_s, "[%i]", &x);
	  pi=new PropIntValue();
	  pi->setName("boardsize");
	  pi->setValue(x);
	  _n->addProperty(pi);
	  return 1;
	default:
	  return 0;
	}
    case 'T':
      switch(_id[1])
	{
	case 'E':
	  fprintf(stderr, "Tesuji\n");
	  return 1;
	default:
	  return 0;
	}
    case 'U':
      switch(_id[1])
	{
	case 'C':
	  fprintf(stderr, "Unclear !\n");
	  return 1;
	default:
	  return 0;
	}
    case 'V':
      switch(_id[1])
	{
	case 0:
	  fprintf(stderr, "Value -> %s\n", _s);
	  return 1;
	default:
	  return 0;
	}
    case 'W':
      switch(_id[1])
	{
	case 0:
	  fprintf(stderr, "White move -> %s\n", _s);
	  pm=new PropMove();
	  // check for a pass of the player
	  if (_s[1]==']')
	    {
	      x=root->size;
	      y=root->size;
	    } else {
	      if (_s[1] <= 'Z' && _s[1]>='A')
		x=_s[1]-'A' + 26;
	      else
		x=_s[1]-'a';

	      if (_s[2] <= 'Z' && _s[2]>='A')
		y=_s[2]-'A' + 26;
	      else
		y=_s[2]-'a';
	    }
	  pm->set(white, x,y);
	  _n->addProperty(pm);
	  return 1;
	}
    default:
      return 0;
  }
  return 0;
}
