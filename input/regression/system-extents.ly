\version "2.3.4"
\header {

    texidoc = "The size of every system is correctly determined; this 
    includes postscript constructs such as slurs."

    }
	  
\score { 
\context Voice
{ \unset Staff.minimumVerticalExtent 
    \slurDown c4 ( g4  c''4)

}

    \paper { 
	 \context {
	     \Score
	     \override System #'print-function = #box-grob-stencil
	     }
    }
}

