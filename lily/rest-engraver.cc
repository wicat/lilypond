/*
  rest-grav.cc -- implement Rest_engraver

  source file of the GNU LilyPond music typesetter

  (c)  1997--2002 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/
#include "item.hh"
#include "staff-symbol-referencer.hh"
#include "musical-request.hh"
#include "dots.hh"
#include "rhythmic-head.hh"
#include "engraver.hh"


class Rest_engraver : public Engraver
{
  Rest_req *rest_req_l_;
  Item * dot_p_;
  Grob* rest_p_;
protected:
  virtual bool try_music (Music *);
  virtual void stop_translation_timestep ();
  virtual void start_translation_timestep ();
  virtual void process_music ();

public:
  TRANSLATOR_DECLARATIONS(Rest_engraver);
};


/*
  Should merge with Note_head_engraver
 */
Rest_engraver::Rest_engraver ()
{
  rest_req_l_ =0;
  rest_p_ =0;
  dot_p_ =0;
}

void
Rest_engraver::start_translation_timestep ()
{
  rest_req_l_ =0;
}

void
Rest_engraver::stop_translation_timestep ()
{
  if (rest_p_)
    {
      typeset_grob (rest_p_);
      rest_p_ =0;
    }
  if (dot_p_)
    {
      typeset_grob (dot_p_);
      dot_p_ =0;
    }    
}

void
Rest_engraver::process_music ()
{
  if (rest_req_l_ && !rest_p_) 
    {
      rest_p_ = new Item (get_property ("Rest"));
      Rhythmic_head::set_interface (rest_p_);

      
      int durlog  = unsmob_duration (rest_req_l_->get_mus_property ("duration"))-> duration_log ();
      
      rest_p_->set_grob_property ("duration-log",
				  gh_int2scm (durlog));

      int dots =unsmob_duration (rest_req_l_->get_mus_property ("duration"))->dot_count ();
      
      if (dots)
	{
	  dot_p_ = new Item (get_property ("Dots"));

	  Rhythmic_head::set_dots (rest_p_, dot_p_);
	  dot_p_->set_parent (rest_p_, Y_AXIS);
	  dot_p_->set_grob_property ("dot-count", gh_int2scm (dots));
	  announce_grob (dot_p_, SCM_EOL);
	}

      Pitch *p = unsmob_pitch (rest_req_l_->get_mus_property ("pitch"));

      /*
	This is ridiculous -- rests don't have pitch, but we act as if
	our nose is bleeding.
       */
      if (p)
	{
	  int pos= p->steps ();
	  SCM c0 = get_property ("centralCPosition");
	  if (gh_number_p (c0))
	    pos += gh_scm2int (c0);
	  
	  rest_p_->set_grob_property ("staff-position", gh_int2scm (pos));
	}
      
      announce_grob(rest_p_, rest_req_l_->self_scm());
    }
}

bool
Rest_engraver::try_music (Music *m)
{
  if (Rest_req *r = dynamic_cast <Rest_req *> (m))
    {
      rest_req_l_ = r;
      return true;
    }  
  return false;
}



ENTER_DESCRIPTION(Rest_engraver,
/* descr */       "",
/* creats*/       "Rest Dots",
/* acks  */       "",
/* reads */       "centralCPosition",
/* write */       "");
