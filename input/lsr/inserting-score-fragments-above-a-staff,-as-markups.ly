%% Do not edit this file; it is auto-generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.11.38"

\header {
  lsrtags = "staff-notation"

  texidoc = "
The @code{\\markup} command is quite versatile. In this snippet, it
contains a @code{\\score} block instead of texts or marks.

"
  doctitle = "Inserting score fragments above a staff, as markups"
} % begin verbatim
tuning = \markup {
  \score {
    \new Staff \with { \remove "Time_signature_engraver" }
    {
      \clef bass  <c, g, d g>1
    }
    \layout { ragged-right = ##t }
  }
}

\header {
  title = "Solo Cello Suites"
  subtitle = "Suite IV"
  subsubtitle = \markup { "Originalstimmung:" \general-align #Y #CENTER \tuning }
}

\layout { ragged-right = ##f }

\relative {
  \time 4/8
  \times 2/3 { c'8 d e } \times 2/3 { c d e }
  \times 2/3 { c8 d e } \times 2/3 { c d e }
  g8 a8 g8 a
  g8 a8 g8 a
}
