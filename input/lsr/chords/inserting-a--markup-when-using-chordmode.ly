%%  Do not edit this file; it is auto-generated from LSR!
\version "2.11.23"

\header { texidoc = "
A way to insert a \markup @{ . . . @}string in \chords @{ . . . @}. 
" }

% Note what happens if \hspace #-2 is deleted or set to +n.
% If "tacet" instead of "Tacet" a little bit of "C" peeks around the \whiteout.
CMString  = { <c e g>-\markup { \whiteout { \hspace #-2 "Tacet" } } }
CMStringX = #(append (sequential-music-to-chord-exceptions CMString #t)
           ignatzekExceptions)
<< { \chords { c1
   \set   chordNameExceptions = #CMStringX c
   \unset chordNameExceptions c }
 } { \relative c'' { c c c } } >>



