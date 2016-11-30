set parametric
set xrange [-1:3]
set yrange [-0.5:2.5]
set arrow 1 from 0,0 to 2,0 nohead
set arrow 2 from 0,1 to 2,1 nohead
plot [-pi/2:pi/2] -0.5*cos(t),0.5+0.5*sin(t),\
[-pi/2:pi/2] 2+0.5*cos(t),0.5+0.5*sin(t)\
"gnuStadium.txt" with lines;