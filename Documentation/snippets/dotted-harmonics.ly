%% Do not edit this file; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% This file is in the public domain.
\version "2.12.2"

\header {
  lsrtags = "unfretted-strings, tweaks-and-overrides"

  texidoc = "
Artificial harmonics using @code{\\harmonic} do not show dots.  To
override this behavior, set the context property @code{harmonicDots}.

"
  doctitle = "Dotted harmonics"
} % begin verbatim

\relative c''' {
  \time 3/4
  \key f \major
  \set harmonicDots = ##t
  <bes f'\harmonic>2. ~
  <bes f'\harmonic>4. <a e'\harmonic>8( <gis dis'\harmonic> <g d'\harmonic>)
  <fis cis'\harmonic>2.
  <bes f'\harmonic>2.
}
