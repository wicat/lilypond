/*   
  separating-line-group-grav.cc --  implement Separating_line_group_engraver
  
  source file of the GNU LilyPond music typesetter
  
  (c) 1998--2000 Han-Wen Nienhuys <hanwen@cs.uu.nl>
  
 */

#include "separating-line-group-engraver.hh"
#include "separating-group-spanner.hh"
#include "single-malt-grouping-item.hh"
#include "paper-column.hh"
#include "paper-def.hh"

Separating_line_group_engraver::Separating_line_group_engraver ()
{
  sep_span_p_ = 0;
  break_malt_p_ = 0;
  nobreak_malt_p_ =0;
}

void
Separating_line_group_engraver::do_creation_processing ()
{
  sep_span_p_ = new Separating_group_spanner (SCM_EOL);
  announce_element (Score_element_info (sep_span_p_, 0));
  sep_span_p_->set_bound (LEFT, unsmob_element (get_property ("currentCommandColumn")));
}

void
Separating_line_group_engraver::do_removal_processing ()
{
  sep_span_p_->set_bound (RIGHT, unsmob_element (get_property ("currentCommandColumn")));
  typeset_element (sep_span_p_);
  sep_span_p_ =0;
}

void
Separating_line_group_engraver::acknowledge_element (Score_element_info i)
{
  Item * it = dynamic_cast <Item *> (i.elem_l_);
  if (it && !it->parent_l (X_AXIS))
    {
      bool ib =it->breakable_b ();
      Single_malt_grouping_item *&p_ref_ (ib ? break_malt_p_
					  : nobreak_malt_p_);

      if (!p_ref_)
	{
	  p_ref_
	    = new Single_malt_grouping_item
	    (get_property ("basicSingleMaltGroupingItemProperties"));
	  
	  if (ib)
	    p_ref_->set_elt_property ("breakable", SCM_BOOL_T);
	  announce_element (Score_element_info (p_ref_, 0));
	}
      p_ref_->add_item (it);
    }
}

void
Separating_line_group_engraver::do_pre_move_processing ()
{
  if (break_malt_p_)
    {
      sep_span_p_->add_spacing_unit (break_malt_p_);
      
      typeset_element (break_malt_p_);
      break_malt_p_ =0;
    }
  if (nobreak_malt_p_)
    {
      sep_span_p_->add_spacing_unit (nobreak_malt_p_);
      typeset_element (nobreak_malt_p_);
      nobreak_malt_p_ =0;
    }
}



ADD_THIS_TRANSLATOR( Separating_line_group_engraver);

