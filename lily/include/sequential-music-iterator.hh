/*
  Sequential_music-iterator.hh -- declare Sequential_music_iterator

  source file of the GNU LilyPond music typesetter

  (c)  1997--2001 Han-Wen Nienhuys <hanwen@cs.uu.nl>
*/

#ifndef SEQUENTIAL_MUSIC_ITERATOR_HH
#define SEQUENTIAL_MUSIC_ITERATOR_HH

#include "music-iterator.hh"


struct Grace_skip 
{
  Moment start_;
  Rational length_;
  Rational grace_length_;  
  Grace_skip *next_;
};

/** Sequential_music iteration: walk each element in turn, and
  construct an iterator for every element.
  
 */
class Sequential_music_iterator :  public Music_iterator
{
public:
  Grace_skip * grace_skips_;
  
  VIRTUAL_COPY_CONS (Music_iterator);
  static SCM constructor_cxx_function;
  Sequential_music_iterator ();
  Sequential_music_iterator (Sequential_music_iterator const&);
  virtual ~Sequential_music_iterator ();

  virtual void construct_children ();
  virtual Moment pending_moment () const;
  virtual bool ok () const;
  virtual void skip (Moment);
  virtual SCM get_music (Moment)const;

protected:
  virtual void process (Moment);
  virtual Music_iterator *try_music_in_children (Music *) const;

private:
  Moment here_mom_;
  SCM cursor_;
  Music_iterator * iter_p_;

  void next_element ();
  void descend_to_child ();
};

#endif // SEQUENTIAL_MUSIC_ITERATOR_HH
