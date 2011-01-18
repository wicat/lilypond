%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.12.2"

\header {
  lsrtags = "editorial-annotations, vocal-music"

  texidoc = "
This example shows how to put crosses on stems.  Mark the beginning of
a spoken section with the @code{\\speakOn} keyword, and end it with the
@code{\\speakOff} keyword.

"
  doctitle = "Marking notes of spoken parts with a cross on the stem"
} % begin verbatim

speakOn = {
  \override Stem #'stencil =
    #(lambda (grob)
       (let* ((x-parent (ly:grob-parent grob X))
              (is-rest? (ly:grob? (ly:grob-object x-parent 'rest))))
         (if is-rest?
             empty-stencil
             (ly:stencil-combine-at-edge
              (ly:stem::print grob)
              Y
              (- (ly:grob-property grob 'direction))
              (grob-interpret-markup grob
                                    (markup #:center-align #:fontsize -4
                                            #:musicglyph "noteheads.s2cross"))
              -2.3 0))))
}

speakOff = {
  \revert Stem #'stencil
}

\score {
  \new Staff {
    \relative c'' {
      a4 b a c
      \speakOn
      g4 f r g
      b4 r d e
      \speakOff
      c4 a g f
    }
  }
}

