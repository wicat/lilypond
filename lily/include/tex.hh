/*
  tex.hh -- declare various functions for TeX output

  source file of the LilyPond music typesetter

  (c) 1997 Han-Wen Nienhuys <hanwen@stack.nl>
*/



#ifndef TEX_HH
#define TEX_HH

#include "string.hh"
#include "boxes.hh"
#include "scalar.hh"

/** parameter substitution in TeX_strings.
  this function provides a simple macro mechanism:

  if source == "tex%bla%", then
  substitute_args (source, {"X","Y"})  == "texXblaY"
  */
String
substitute_args (String source, Array<String> args);

/// parameter substitution in TeX_strings
String
substitute_args (String source, Array<Scalar> args);

/// #h# is in points
String vstrut (Real h);


#endif
