set terminal epslatex
set output "CircTraj.tex"
set format xy "$%g$"
set xlabel "$x$"
set ylabel "$y$"
set size square 
set xrange [-1.5:1.5]
set yrange [-1.5:1.5]
plot [0:2*pi] cos(t),sin(t) lc rgb "black",\
"gnuCircle.txt" with lines

set terminal x11
set format xy "%g"
set xlabel "x"
set ylabel "y"
set size square
set xrange [-1.5:1.5]
set yrange [-1.5:1.5]
plot [0:2*pi] cos(t),sin(t) lc rgb "black",\
"gnuCircle.txt" with lines
