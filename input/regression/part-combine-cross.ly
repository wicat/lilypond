
\header {
    texidoc ="The part combiner stays apart for crossing voices.
"
    }

\version "2.3.4"

vone =  \relative a' { g4 g f f e e d d }
vtwo =  \relative a' { e4 e f f g g a a }

\score {
   \partcombine \vone \vtwo
   \paper { raggedright = ##t } 
}
 
