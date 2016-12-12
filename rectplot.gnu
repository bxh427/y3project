set terminal epslatex
set output "RectTraj.tex"
set format xy "$%g$"
set xlabel "$x$"
set ylabel "$y$"
a = 1
b = 2
frac = a/b
set size ratio frac 
set xrange [-0.5:b+0.5]
set yrange [-0.5:a+0.5]
set arrow 1 from 0,0 to b,0 nohead lw 0.1 lc rgb "black"
set arrow 2 from 0,a to b,a nohead lw 0.1 lc rgb "black"
set arrow 3 from 0,0 to 0,a nohead lw 0.1 lc rgb "black"
set arrow 4 from b,0 to b,a nohead lw 0.1 lc rgb "black"
plot "gnuRectangle.txt" with lines

set terminal x11
set format xy "%g"
set xlabel "x"
set ylabel "y"
a = 1
b = 2
frac = a/b
set size ratio frac
set xrange [-0.5:b+0.5]
set yrange [-0.5:a+0.5]
set arrow 1 from 0,0 to b,0 nohead lw 0.1 lc rgb "black"
set arrow 2 from 0,a to b,a nohead lw 0.1 lc rgb "black"
set arrow 3 from 0,0 to 0,a nohead lw 0.1 lc rgb "black"
set arrow 4 from b,0 to b,a nohead lw 0.1 lc rgb "black"
plot "gnuRectangle.txt" with lines
