/*
  file-name.cc - implement File_name
   
  source file of the Flower Library
  
  (c) 1997--2004 Han-Wen Nienhuys <hanwen@cs.uu.nl>
                 Jan Nieuwenhuizen <janneke@gnu.org>
*/

//#include "config.hh"
#include "config.h"
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#if HAVE_SYS_STAT_H 
#include <sys/stat.h>
#endif

#ifdef __CYGWIN__
#include <sys/cygwin.h>
#endif

#include "file-name.hh"

/* We don't have multiple roots, set this to '\0'? */
#ifndef ROOTSEP
#define ROOTSEP ':'
#endif

#ifndef DIRSEP
#define DIRSEP '/'
#endif

#ifndef EXTSEP
#define EXTSEP '.'
#endif

#ifdef __CYGWIN__
static String
dos_to_posix (String file_name)
{
  char buf[PATH_MAX];
  char *s = file_name.get_copy_str0 ();
  /* urg, wtf? char const* argument gets modified! */
  cygwin_conv_to_posix_path (s, buf);
  delete s;
  return buf;
}
#endif /* __CYGWIN__ */

/* Join components to full file_name. */
String
File_name::to_string () const
{
  String s;
  if (!root_.is_empty ())
    s = root_ + ::to_string (ROOTSEP);
  if (!dir_.is_empty ())
    s += dir_ + ::to_string (DIRSEP);
  s += base_;
  if (!ext_.is_empty ())
    s += ::to_string (EXTSEP) + ext_;
  return s;
}

char const*
File_name::to_str0 () const
{
  return to_string ().to_str0 ();
}

File_name::File_name (String file_name)
{
#ifdef __CYGWIN__
  /* All system functions would work, even if we don't convert to
     posix file_name, but we'd think that \foe\bar\baz.ly is in the cwd.
     On by default.  */
  file_name = dos_to_posix (file_name);
#endif

  int i = file_name.index (ROOTSEP);
  if (i >= 0)
    {
      root_ = file_name.left_string (i);
      file_name = file_name.right_string (file_name.length () - i - 1);
    }

  i = file_name.index_last (DIRSEP);
  if (i >= 0)
    {
      dir_ = file_name.left_string (i);
      file_name = file_name.right_string (file_name.length () - i - 1);
    }

  i = file_name.index_last ('.');
  if (i >= 0)
    {
      base_ = file_name.left_string (i);
      ext_ = file_name.right_string (file_name.length () - i - 1);
    }
  else
    base_ = file_name;
}
