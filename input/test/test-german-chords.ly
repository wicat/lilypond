\version "1.3.146"
\include "german-chords.ly"

% #(set! german-Bb #t)

ch = \chords { beses1/+beses bes/+bes b/+b bis/+bis ases/+ases as/+as a/+a ais/+ais fisis/+fisis }

\score {
   <
   \context ChordNames=chn {\ch}
   \context Staff=stf {\clef "G_8" \ch }
   >
   \paper {}
}

