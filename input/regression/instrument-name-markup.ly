\header {

texidoc = "Instrument names are set with @code{Staff.instrument} and
@code{Staff.instr}. You can enter markup texts to create more funky names,
including alterations. "

}


\version "2.3.4"


textFlat = \markup {\smaller \flat}

\score {
   \new Staff {
    \set Staff.instrument = \markup { \column < "Clarinetti" { "in B" \textFlat } > }
    \set Staff.instr = \markup { \smaller  { "Cl(B" \textFlat ")" } }

    { c''1 \break c'' }

  }
  \paper { raggedright = ##t }
}


