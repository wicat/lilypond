\version "1.5.68"
\header{
texidoc="
Staff margins are also markings attached to barlines.  They should be
left of the staff, and be centered vertically wrt the staff.  They may
be on normal staves, but also on compound staves, like the PianoStaff
"
}

	


\score {

  \notes \context PianoStaff <
    \context Staff = treble    {
      \property PianoStaff.instrument = "Piano "
      \property Staff.instrument = "Right " { c''4 }}
    \context Staff = bass { \property Staff.instrument = "Left " \clef bass c4 }>

\paper {
linewidth=-1.0
}}

