
\version "2.7.14"

\header {

  texidoc = "In tightly engraved music, hyphens are removed, except at the
end of the line.  Normally, lyrics are not typeset so tightly, but by
tuning down @code{padding} of in @code{SeparationItem}, syllables are put 
closer together, and as a result hyphens may disappear.

In some languages (e.g. German and Hungarian), hyphens should not
disappear, since spelling depends on hyphenation. For that purpose,
hyphens can be forced to remain setting @code{spacing-procedure} to
@code{Hyphen_spanner::set_spacing_rods} of the @code{LyricHyphen}
grob.  The @code{minimum-length} property may be used to tune the
amount

"

}


<<
  \new Staff \relative c'' {
    \time 1/4 c16[ c c  c]
    \time 1/4
    c16[ c c c]
    \time 1/4
    c16[ c c c]

  }
  \new Lyrics \with {
				% Otherwise lyrics are so far apart that hyphens don't disappear
    \override SeparationItem #'padding = #0.0
  }
  \lyricmode {
    bla -- bla -- bla -- bla --
    bla -- bla -- bla -- bla --

    \override LyricHyphen  #'minimum-length = #0.7
    \override LyricHyphen  #'springs-and-rods =
    #Hyphen_spanner::set_spacing_rods

    bla -- bla -- bla -- bla 
  }
>>
  \layout   {
    indent = 0.0 \cm
    linewidth = 3.4 \cm

    \context {
      \Staff \remove "Time_signature_engraver"
    }
    
  }
  


  
