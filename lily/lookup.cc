/*
  lookup.cc -- implement simple Lookup methods.

  source file of the GNU LilyPond music typesetter

  (c)  1997--1998 Han-Wen Nienhuys <hanwen@cs.uu.nl>

  Jan Nieuwenhuizen <janneke@gnu.org>

  TODO
      Read spacing info from AFMs
      Glissando
*/

#include "lookup.hh"
#include "debug.hh"
#include "dimensions.hh"
#include "symtable.hh"
#include "scalar.hh"
#include "paper-def.hh"
#include "string-convert.hh"
#include "main.hh"
#include "lily-guile.hh"

Lookup::Lookup ()
{
  paper_l_ = 0;
  symtables_p_ = new Symtables;
  afm_p_ =0;
}

Lookup::Lookup (Lookup const& s)
{
  font_ = s.font_;
  font_path_ = s.font_path_;
  paper_l_ = s.paper_l_;
  symtables_p_ = new Symtables (*s.symtables_p_);
  afm_p_ = 0;
}

Lookup::Lookup (Symtables const& s)
{
  font_ = s.font_;
  font_path_ = s.font_path_;
  paper_l_ = 0;
  symtables_p_ = new Symtables (s);
  afm_p_ = 0;
}

Lookup::~Lookup ()
{
  delete afm_p_;
  delete symtables_p_;
}

Molecule
Lookup::accidental (int j, bool cautionary) const
{
  Molecule m(afm_find (String ("accidentals") + String ("-") + to_str (j)));
  if (cautionary) 
    {
      m.add_at_edge(X_AXIS, LEFT, 
                    Molecule(afm_find (String ("accidentals") + String ("-("))))
;
      m.add_at_edge(X_AXIS, RIGHT, 
                    Molecule(afm_find (String ("accidentals") + String ("-)"))))
;
    }
  return m;
}

void
Lookup::add (String s, Symtable*p)
{
  symtables_p_->add (s, p);
}

Atom
Lookup::afm_find (String s, bool warn) const
{
  if (!afm_p_)
    {
      *mlog << "[" << font_path_;
      ( (Lookup*)this)->afm_p_ = new Adobe_font_metric (read_afm (font_path_));
      *mlog << "]" << flush ;
      DOUT << this->afm_p_->str ();
    }
  Adobe_font_char_metric m = afm_p_->find_char (s, warn);

  Atom a;
  if (m.code () < 0)
    return a;
  
  a.dim_ = m.B_;
  a.dim_[X_AXIS] *= 1 / 1000.0;
  a.dim_[Y_AXIS] *= 1 / 1000.0;
  Array<Real> arr;
  arr.push (m.code ());
  a.lambda_ =  (lambda_scm ("char", arr));
  a.str_ = "afm_find: " + s;
  a.font_ = font_;
  return a;
}

Atom
Lookup::ball (int j) const
{
  if (j > 2)
    j = 2;

  return afm_find (String ("balls") + String ("-") + to_str (j));
}

Atom
Lookup::bar (String str, Real h) const
{
  Array<Real> arr;
  arr.push (h);
  Atom a = (*symtables_p_) ("bars")->lookup (str);
  a.lambda_ =  (lambda_scm (a.str_, arr));
  a.str_ = "bar";
  a.dim_.y () = Interval (-h/2, h/2);
  a.font_ = font_;
  return a;
}

Atom 
Lookup::beam (Real slope, Real width, Real thick) const
{
  Real height = slope * width; 
  Real min_y = (0 <? height) - thick/2;
  Real max_y = (0 >? height) + thick/2;

  Array<Real> arr;
  arr.push (width);
  arr.push (slope);
  arr.push (thick);

  Atom a;
  a.lambda_ =  (lambda_scm ("beam", arr));
  a.str_ = "beam";
  a.dim_[X_AXIS] = Interval (0, width);
  a.dim_[Y_AXIS] = Interval (min_y, max_y);
  return a;
}

Atom
Lookup::clef (String st) const
{
  return afm_find (String ("clefs") + String ("-") + st);
}

SCM
offset2scm (Offset o)
{
  return gh_list (gh_double2scm (o[X_AXIS]), gh_double2scm(o[Y_AXIS]), SCM_UNDEFINED);
}

Atom
Lookup::dashed_slur (Array<Offset> controls, Real thick, Real dash) const
{
  assert (controls.size () == 8);
  Offset d = controls[3] - controls[0];
  
  Real dx = d[X_AXIS];
  Real dy = d[Y_AXIS];

  Atom a;
  a.font_ = font_;
  a.dim_[X_AXIS] = Interval (0, dx);
  a.dim_[Y_AXIS] = Interval (0 <? dy,  0 >? dy);

  SCM sc[4];
  for (int i=0; i<  4; i++)
    {
      sc[i] =  offset2scm (controls[i]);
    }

  // (lambda (o) (dashed-slur o thick dash '(stuff))
  a.lambda_ = gh_list (gh_append3 (ly_lambda_o (),
				  ly_func_o ("dashed-slur"),
				  gh_list (gh_double2scm (thick),
					   gh_double2scm (dash),
					   ly_quote_scm (gh_list (sc[0], sc[1], sc[2], sc[3], SCM_UNDEFINED)),
					   SCM_UNDEFINED)
				  ), SCM_UNDEFINED);

  a.str_ = "dashed_slur";
  return a;
}

Atom
Lookup::dots () const
{
  return afm_find (String ("dots") + String ("-") + String ("dot"));
}

Atom
Lookup::dynamic (String st) const
{
  return (*symtables_p_) ("dynamics")->lookup (st);
}

Atom
Lookup::fill (Box b) const
{
  Atom a;
  a.dim_ = b;
  return a;
}

Atom
Lookup::flag (int j, Direction d) const
{
  char c = (d == UP) ? 'u' : 'd';
  Atom a = afm_find (String ("flags") + String ("-") + to_str (c) + to_str (j));
  return a;
}

void
Lookup::print () const
{
#ifndef NPRINT
  DOUT << "Lookup {\n";
  symtables_p_->print ();
  DOUT << "}\n";
#endif
}

Atom
Lookup::rest (int j, bool o) const
{
   return afm_find (String ("rests")
		    + String ("-") + to_str (j) + (o ? "o" : ""));
}

Atom
Lookup::rule_symbol (Real height, Real width) const
{
  Atom a = (*symtables_p_) ("param")->lookup ("rule");
  Array<Real> arr;
  arr.push (height);
  arr.push (width);
  a.lambda_ = (lambda_scm (a.str_, arr));
  a.str_ = "rule_symbol";
  a.dim_.x () = Interval (0, width);
  a.dim_.y () = Interval (0, height);
  return a;
}

Atom
Lookup::script (String str) const
{
  return afm_find (String ("scripts") + String ("-") + str);
}

Atom
Lookup::special_time_signature (String s, Array<int> arr) const
{
  // First guess: s contains only the signature style
  assert (arr.size () >1);
  String symbolname = "timesig-" + s + to_str (arr[0]) + "/" + to_str (arr[1]);
  
  Atom a = afm_find (symbolname, false);
  if (!a.empty ()) 
    return a;

  // Second guess: s contains the full signature name
  a = afm_find ("timesig-"+s, false);
  if (!a.empty ()) 
    return a;

  // Resort to default layout with numbers
  return time_signature (arr);
}

Atom
Lookup::stem (Real y1, Real y2) const
{
  if (y1 > y2)
    {
      Real t = y1;
      y1 = y2;
      y2 = t;
    }
  Atom a;

  a.dim_.x () = Interval (0,0);
  a.dim_.y () = Interval (y1,y2);

  Array<Real> arr;

  Real stem_width = paper_l_->get_var ("stemthickness");
  arr.push (-stem_width /2);
  arr.push (stem_width);
  arr.push (y2);
  arr.push (-y1);

  a.lambda_ = (lambda_scm ("stem", arr));
  a.str_ = "stem";
  a.font_ = font_;
  return a;
}

Atom
Lookup::streepje (int type) const
{
  if (type > 2)
    type = 2;

  return  afm_find ("balls" + String ("-") +to_str (type) + "l");
}

Atom
Lookup::text (String style, String text) const
{
  Array<Scalar> arr;

  arr.push (text);
  Atom a =  (*symtables_p_) ("style")->lookup (style);
  a.lambda_ = lambda_scm (a.str_, arr);
  a.str_ = "text";
  a.font_ = font_;
  return a;
   
}
  

Atom
Lookup::time_signature (Array<int> a) const
{
  Atom s ((*symtables_p_) ("param")->lookup ("time_signature"));
  s.lambda_ =  (lambda_scm (s.str_, a));

  return s;
}

/*
  should be handled via Tex_ code and Lookup::bar ()
 */
Atom
Lookup::vbrace (Real &y) const
{
  Atom a = (*symtables_p_) ("param")->lookup ( "brace");
  Interval ydims = a.dim_[Y_AXIS];
  Real min_y = ydims[LEFT];
  Real max_y = ydims[RIGHT];
  Real step = 1.0 PT;
 
  if (y < min_y)
    {
      warning (_ ("piano brace") 
	       + " " + _ ("too small") +  " (" + print_dimen (y) + ")");
      y = min_y;
    }
  if (y > max_y)
    {
      warning (_ ("piano brace")
	       + " " + _ ("too big") + " (" + print_dimen (y) + ")");
      y = max_y;
    }

  
  int idx = int (rint ( (y- min_y)/step)) + 1;
  
  Array<Real> arr;
  arr.push (idx);
  a.lambda_ = (lambda_scm (a.str_, arr));
  a.str_ = "brace";
  a.dim_[Y_AXIS] = Interval (-y/2,y/2);
  a.font_ = font_;
  return a;
}

Atom
Lookup::hairpin (Real width, bool decresc, bool continued) const
{
  Atom a;  
  Real height = paper_l_->staffheight_f () / 6;
  String ps;
  ps += to_str (width) + " " 
    + to_str (height) + " " 
    + to_str (continued ? height/2 : 0) + 
    + " draw_"  + String (decresc ? "de" : "") + "cresc\n";
  a.str_ = ps;
  a.dim_.x () = Interval (0, width);
  a.dim_.y () = Interval (-2*height, 2*height);
  a.font_ = font_;
  return a;
}

Atom
Lookup::plet (Real dy , Real dx, Direction dir) const
{
  String ps;
    
  ps += String_convert::double_str (dx) + " " 
    + String_convert::double_str (dy) + " "
    + String_convert::int_str ( (int)dir) +
    " draw_plet ";

  Atom a;
  a.str_ = ps;
  return a;
}

Atom
Lookup::slur (Array<Offset> controls) const
{
  assert (controls.size () == 8);

  String ps;
  
  Real dx = controls[3].x () - controls[0].x ();
  Real dy = controls[3].y () - controls[0].y ();
  Atom a;

  SCM scontrols [8];
  int indices[] = {5,6,7,4,1,2,3,0};

  for (int i= 0; i < 8; i++)
    scontrols[i] = offset2scm (controls[indices[i]]);


  a.lambda_ =
    gh_append2 (ly_lambda_o (),
		gh_list (gh_append2 (ly_func_o ("slur"),
				     gh_list (ly_quote_scm (gh_list (scontrols[0],
								     scontrols[1],
								     scontrols[2],
								     scontrols[3],
								     scontrols[4],
								     scontrols[5],
								     scontrols[6],
								     scontrols[7],
								     SCM_UNDEFINED)),
					      SCM_UNDEFINED)
				     ),
			 SCM_UNDEFINED)
		);


  a.str_ = "slur";

  a.dim_[X_AXIS] = Interval (0, dx);
  a.dim_[Y_AXIS] = Interval (0 <? dy,  0 >? dy);
  a.font_ = font_;
  return a;
}

Atom
Lookup::vbracket (Real &y) const
{
  Atom a;
  Real min_y = paper_l_->staffheight_f ();
  if (y < min_y)
    {
      warning (_ ("bracket")
	       + " " + _ ("too small") +  " (" + print_dimen (y) + ")");
      //      y = min_y;
    }
  Array<Real> arr;
  arr.push (y);
  a.lambda_ =  (lambda_scm ("bracket", arr));
  a.str_ = "vbracket";
  a.dim_[Y_AXIS] = Interval (-y/2,y/2);
  a.dim_[X_AXIS] = Interval (0,4 PT);
  return a;
}


