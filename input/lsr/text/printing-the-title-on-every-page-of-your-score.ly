%%  Do not edit this file; it is auto-generated from LSR!
\version "2.11.23"

\header { texidoc = "
With this trick, the title of your work will be printed in small on top
of every page, using evenHeaderMarkup and oddHeaderMarkup.
" }

\paper{
oddHeaderMarkup = \markup
\fill-line {
\fromproperty #'header:title
" " % This will make sure that the header is never completely empty, to
% avoid some layout problems. Also, moving it in between the title and
% the page number, makes these be typeset left and right aligned, respectively.
\on-the-fly #print-page-number-check-first \fromproperty #'page:page-number-string
}

evenHeaderMarkup = \markup
\fill-line {
\on-the-fly #print-page-number-check-first \fromproperty #'page:page-number-string
" "
\fromproperty #'header:title
}
}
\header {
       title = "This title will be repeated"
       subtitle = "whereas this subtitle won't"
         }
         
         \score { \new Staff {\repeat unfold 8 { c'8 c'8 c'8 c'8 } \pageBreak
\repeat unfold 8 { c'8 c'8 c'8 c'8 } \pageBreak
\repeat unfold 8 { c'8 c'8 c'8 c'8 } \pageBreak
\repeat unfold 8 { c'8 c'8 c'8 c'8 } \pageBreak
         } }
