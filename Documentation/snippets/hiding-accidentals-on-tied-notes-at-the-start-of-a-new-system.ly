% Do not edit this file; it is automatically
% generated from Documentation/snippets/new
% This file is in the public domain.
%% Note: this file works from version 2.13.36
\version "2.13.36"
\header {
%% Translation of GIT committish: a874fda3641c9e02f61be5c41b215b8304b8ed00

  texidoces = "
Aquí se muestra la manera de ocultar las alteraciones de las notas
ligadas al comienzo de un sistema nuevo.

"

  doctitlees = "Ocultar las alteraciones sobre notas ligadas al principio de un sistema nuevo"


%% Translation of GIT committish: 31097723b2b816696ad61696630a80ff17a39557
  texidocfr = "Cet exemple illustre comment, lorsqu'une note affublée
  d'une altération accidentelle est prolongée, ne pas répéter cette
  altération après un saut de ligne.
"
  doctitlefr = "Non répétition de l'altération après saut de ligne
  sur liaison de prolongation"


  lsrtags = "pitches"
  texidoc = "This shows how to hide accidentals on tied notes at the beginning of a
new system."
  doctitle = "Hiding accidentals on tied notes at the beginning of a new system"
} % begin verbatim


\relative c'' {
  \override Accidental #'hide-tied-accidental-after-break = ##t
  cis1~ cis~
  \break
  cis
}

