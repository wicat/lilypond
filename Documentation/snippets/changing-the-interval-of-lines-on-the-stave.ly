%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.12.2"

\header {
  lsrtags = "pitches"

  texidoc = "
@code{staffLineLayoutFunction} is used to change the position of notes.
This snippet shows setting its value to @code{ly:pitch-semitones} in
order to produce a chromatic scale with the distance between each space
and line of the stave equal to one semitone.

"
  doctitle = "Changing the interval of lines on the stave"
} % begin verbatim

scale = \relative c' {
  a4 ais b c
  cis4 d dis e
  f4 fis g gis
  a1
}

\new Staff \with {
  \remove "Accidental_engraver"
  staffLineLayoutFunction = #ly:pitch-semitones
}
{
  <<
    \scale
    \context NoteNames {
      \set printOctaveNames = ##f
      \scale
    }
  >>
}

