/*
  breathing_sign.cc -- implement Breathing_sign

  Copyright (C) 1999 Michael Krause

  written for the GNU LilyPond music typesetter

  TODO: --> see breathing-sign-engraver.cc

*/

#include "staff-symbol-referencer.hh"
#include "directional-element-interface.hh"
#include "breathing-sign.hh"
#include "string.hh"
#include "molecule.hh"
#include "paper-def.hh"
#include "lookup.hh"
#include "debug.hh"
#include "dimensions.hh"
#include "direction.hh"


Breathing_sign::Breathing_sign (SCM  s)
  : Item (s)
{
}



MAKE_SCHEME_SCORE_ELEMENT_CALLBACK(Breathing_sign,brew_molecule);

SCM 
Breathing_sign::brew_molecule (SCM smob)
{
  Score_element * sc = unsmob_element (smob);
  Staff_symbol_referencer_interface si (sc);
  
  Real space = si.staff_space();

  // todo: cfg'able.
  Interval i1(0, space / 6), i2(-space / 2, space / 2);
  Box b(i1, i2);

  return sc->lookup_l()->filledbox(b).create_scheme ();
}

GLUE_SCORE_ELEMENT(Breathing_sign,after_line_breaking);
SCM
Breathing_sign::member_after_line_breaking ()
{
  Real space = staff_symbol_referencer (this).staff_space();
  Direction d = Directional_element_interface (this). get ();
  if (!d)
    {
      d = UP;
      Directional_element_interface (this).set (d);
    }

  translate_axis(2.0 * space * d, Y_AXIS);

  return SCM_UNDEFINED;
}

