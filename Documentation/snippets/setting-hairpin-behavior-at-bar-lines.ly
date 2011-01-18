%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.12.2"

\header {
  lsrtags = "expressive-marks, tweaks-and-overrides"

%% Translation of GIT committish: a874fda3641c9e02f61be5c41b215b8304b8ed00
  texidoces = "
Si la nota que da fin a un regulador cae sobre la primera parte de
un compás, el regulador se detiene en la línea divisoria
inmediatamente precedente.  Se puede controlar este comportamiento
sobreescribiendo la propiedad @code{'to-barline}.

"
  doctitlees = "Establecer el comportamiento de los reguladores en las barras de compás"


%% Translation of GIT committish: 0a868be38a775ecb1ef935b079000cebbc64de40
texidocde = "
Wenn die Note, an welcher eine Crescendo-Klammer endet, die erste Note
eines Taktes ist, wird die Klammer an der vorhergehenden Taktlinie
beendet.  Dieses Verhalten kann auch mit der Eigenschaft
@code{'to-barline} geändert werden:
"
  doctitlede = "Das Verhalten von Crescendo-Klammern an Taktlinien beeinflussen"

%% Translation of GIT committish: 217cd2b9de6e783f2a5c8a42be9c70a82195ad20
  texidocfr = "
En principe, un soufflet -- (de)crescendo imprimé sous forme graphique --
commence au bord gauche de la note de départ, et se termine au
bord droit de la note d'arrivée.  Cependant, si la note d'arrivée
est sur un premier temps, le soufflet s'arrêtera au niveau de la
barre de mesure qui la précède.  Ce comportement peut être annulé
en assignant @emph{faux} (@code{#f}) à la propriété @code{'to-barline} :

"
  doctitlefr = "Soufflets et barres de mesure"


  texidoc = "
If the note which ends a hairpin falls on a downbeat, the hairpin stops
at the bar line immediately preceding.  This behavior can be controlled
by overriding the @code{'to-barline} property.

"
  doctitle = "Setting hairpin behavior at bar lines"
} % begin verbatim

\relative c'' {
  e4\< e2.
  e1\!
  \override Hairpin #'to-barline = ##f
  e4\< e2.
  e1\!
}
