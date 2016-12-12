set terminal epslatex
set output "EllTraj.tex"
set format xy "$%g$"
set xlabel "$x$"
set ylabel "$y$"
set object 1 ellipse center 0,0 size 2*a,2*b lc rgb "black"
a = 1
b = 2
frac = a/b
set size ratio frac 
set xrange [-0.5-b:b+0.5]
set yrange [-0.5-a:a+0.5]
plot "gnuEllipse.txt" with lines

set terminal x11
set format xy "%g"
set xlabel "x"
set ylabel "y"
set object 1 ellipse center 0,0 size 2*a,2*b lc rgb "black"
a = 1
b = 2
frac = a/b
set size ratio frac
set xrange [-0.5-b:b+0.5]
set yrange [-0.5-a:a+0.5]
plot "gnuEllipse.txt" with lines
