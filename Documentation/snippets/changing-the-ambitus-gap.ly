% Do not edit this file; it is automatically
% generated from Documentation/snippets/new
% This file is in the public domain.
%% Note: this file works from version 2.13.36
\version "2.13.36"
\header {
%% Translation of GIT committish: a874fda3641c9e02f61be5c41b215b8304b8ed00

  texidoces = "
Es posible ajustar la separación en las indicaciones de tesitura.

"

  doctitlees = "Modificación de la separación en las indicaciones de tesitura"

%% Translation of GIT committish: 31097723b2b816696ad61696630a80ff17a39557
  texidocfr = "L'affichage d'un @emph{ambitus} peut s'affiner pour
  répondre à vos préférences en matière d'esthétique.
"

  doctitlefr = "Réglage de l'affichage d'un ambitus"


  lsrtags = "pitches"
  texidoc = "It is possible to change the default gap setting for
ambitus."

  doctitle = "Changing the ambitus gap"
} % begin verbatim



\layout {
  \context {
    \Voice
    \consists "Ambitus_engraver"
  }
}

\new Staff {
  \time 2/4
  % Default setting
  c'4 g''
}

\new Staff {
  \time 2/4
  \override AmbitusLine #'gap = #0
  c'4 g''
}

\new Staff {
  \time 2/4
  \override AmbitusLine #'gap = #1
  c'4 g''
}

\new Staff {
  \time 2/4
  \override AmbitusLine #'gap = #1.5
  c'4 g''
}
