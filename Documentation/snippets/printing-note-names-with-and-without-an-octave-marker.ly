%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.12.2"

\header {
  lsrtags = "tweaks-and-overrides"

%% Translation of GIT committish: a874fda3641c9e02f61be5c41b215b8304b8ed00
  texidoces = "
Se puede usar el contexto @code{NoteNames} para imprimir el valor
textual de las notas.  La propiedad @code{printOctaveNames} activa o
desactiva la representación de la octava de las notas.

"
  doctitlees = "Impresión de los nombres de las notas con o sin indicación de la octava"



  texidoc = "
The @code{NoteNames} context can be used to print the text value of
notes.  The @code{printOctaveNames} property turns on or off the
representation of the octave of the note.

"
  doctitle = "Printing note names with and without an octave marker"
} % begin verbatim

scale = \relative c' {
  a4 b c d
  e4 f g a
}

\new Staff {
  <<
    \scale
    \context NoteNames {
      \set printOctaveNames = ##f
      \scale
    }
  >>
  R1
  <<
    \scale
    \context NoteNames {
      \set printOctaveNames = ##t
      \scale
    }
  >>
}

