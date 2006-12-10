/*
  stream-event.cc -- implement Scheme bindings for Stream_event

  source file of the GNU LilyPond music typesetter

  (c) 2006 Erik Sandberg  <mandolaerik@gmail.com>
*/

#include "stream-event.hh"

LY_DEFINE (ly_make_stream_event, "ly:make-stream-event",
	   1, 1, 0, (SCM cl, SCM proplist),
	   "Creates a stream event of class @var{cl} with the given mutable property list.\n" )
{
  SCM_ASSERT_TYPE (scm_is_symbol (cl), cl, SCM_ARG1, __FUNCTION__, "symbol");
  if (proplist != SCM_UNDEFINED)
    {
      SCM_ASSERT_TYPE (scm_list_p (proplist), proplist, SCM_ARG2, __FUNCTION__, "association list");
    }
  else
    proplist = SCM_EOL;
  Stream_event *e = new Stream_event (cl, proplist);
  return e->unprotect ();
}

LY_DEFINE (ly_event_property, "ly:event-property", 
           2, 0, 0, (SCM sev, SCM sym),
	   "Get the property @var{sym} of stream event @var{mus}.\n"
	   "If @var{sym} is undefined, return @code{'()}.\n")
{
  Stream_event *e = unsmob_stream_event (sev);
  SCM_ASSERT_TYPE (e, sev, SCM_ARG1, __FUNCTION__, "stream event");
  SCM_ASSERT_TYPE (scm_is_symbol (sym), sym, SCM_ARG2, __FUNCTION__, "symbol");

  return e->internal_get_property (sym);
}

LY_DEFINE (ly_event_set_property, "ly:event-set-property!",
           3, 0, 0, (SCM ev, SCM sym, SCM val),
           "Set property @var{sym} in event @var{ev} to @var{val}."){
  Stream_event *sc = unsmob_stream_event (ev);
  SCM_ASSERT_TYPE (sc, ev, SCM_ARG1, __FUNCTION__, "event");
  return ly_prob_set_property_x (ev, sym, val);
}
