// -*-c++-*-
#ifndef LIST_INL
#define LIST_INL
template<class T>
inline
List<T>::List()
{
    set_empty();
}

template<class T>
inline void
List<T>::set_empty()
{
    top_ = bottom_ = 0;
    size_ = 0;
}

template<class T>
inline
List<T>::List( const T& thing )
{
    set_empty();
    add( thing, Cursor<T>( *this, bottom_ ) );
}

template<class T>
inline
List<T>::~List()
{
    Cursor<T> next(*this);
    for ( Cursor<T> c( *this ); c.ok(); c = next ) {
	next = c;
	next++;
	remove( c );
    }
}

template<class T>
inline void
List<T>::add( const T& thing, Cursor<T> after_me )
{
#if 0
    if ( after_me.ok() )
	after_me.pointer()->add( thing );
    else if ( size_ )
        bottom().pointer()->add( thing );
    else
        bottom_ = top_ = new Link<T>( thing );
#endif
    
    if (!size_) {		// not much choice if list is empty
        bottom_ = top_ = new Link<T>( thing );
    } else {			// add at aprioprate place
	Link<T> *p =  ( after_me.ok() ) ?
	    after_me.pointer() : bottom().pointer();
	p->add(thing);
	if (p == bottom_)	// adjust bottom_ if necessary.
	    bottom_ = p->next();
    }

    size_++;
}
/** 

  Procedure:
  \begin{itemize}
  \item if #after_me# is #ok()#, add after #after_me#, else
  \item if list !empty simply add to bottom, else
  \item list is empty: create first \Ref{Link} and initialize 
  #bottom_# and #top_#.
  \end{itemize}
*/

template<class T>
inline void
List<T>::insert( const T& thing, Cursor<T> before_me )
{
    if (!size_) {
	bottom_ = top_ = new Link<T>( thing );
    } else {
	Link<T> *p = 
	    (before_me.ok())?
	    before_me.pointer() : top().pointer();

	p->insert(thing);
	if (p == top_)
	    top_ = p->previous();
    }
	
    size_++;
#if 0 // rewrite hwn 16/9		
    if ( before_me.ok() )
        before_me.pointer()->insert( thing );
    else if ( size_ )
	top().pointer()->insert( thing );
    else
	bottom_ = top_ = new Link<T>( thing );
    size_++;
#endif
}

template<class T>
inline void
List<T>::remove( Cursor<T> me )
{
    if ( me.ok() ){
	Link<T> *lp = me.pointer();	
	lp->remove(*this);
	delete lp;
        size_--;
    }
}

template<class T>
inline int
List<T>::size() const
{ 
    return size_;
}



#endif
