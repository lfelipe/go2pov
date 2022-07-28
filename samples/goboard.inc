// POV - scene, automatically generated with Go2Pov
// version 
#include "gotexture.inc"

#declare th = 0.004000;
#declare bh = 0.100000;
#declare ssize = 0.088000;
#declare srad = 0.044000;
#declare sheight = 0.029330;

#declare stone = object { intersection {
sphere{<0,0.8,0> 1.0}
sphere{<0,-0.8,0> 1.0}
}
scale <0.8,0.8,0.8>}


#declare bs = object { stone pigment {bs_pigment} scale <ssize, ssize, ssize> finish {bs_finish} }
#declare ws = object { stone pigment {ws_pigment} scale <ssize, ssize, ssize> finish {ws_finish} }
#declare hline = object { box{<--0.882000,0,-th/2> <+-0.882000,bh,+th/2>} }
#declare vline = object { box{<-th/2,0,--0.882000> <+th/2,bh,+-0.882000>} }
#declare hoshi = object { cylinder{<0,0,0><0,bh,0> th*3} }
#declare hoshis = union {
 object {hoshi translate<0.588000,0,-0.588000>}
 object {hoshi translate<-0.000000,0,-0.588000>}
 object {hoshi translate<-0.588000,0,-0.588000>}
 object {hoshi translate<0.588000,0,0.000000>}
 object {hoshi translate<-0.000000,0,0.000000>}
 object {hoshi translate<-0.588000,0,0.000000>}
 object {hoshi translate<0.588000,0,0.588000>}
 object {hoshi translate<-0.000000,0,0.588000>}
 object {hoshi translate<-0.588000,0,0.588000>}
}

#declare stones = union {
object {ws translate <0.686000,bh+sheight/2,-0.392000>}
object {bs translate <0.686000,bh+sheight/2,0.588000>}
object {ws translate <0.588000,bh+sheight/2,-0.686000>}
object {bs translate <0.490000,bh+sheight/2,0.588000>}
object {bs translate <0.196000,bh+sheight/2,-0.686000>}
object {ws translate <0.098000,bh+sheight/2,0.686000>}
object {bs translate <-0.098000,bh+sheight/2,-0.686000>}
object {ws translate <-0.196000,bh+sheight/2,0.588000>}
object {ws translate <-0.196000,bh+sheight/2,0.686000>}
object {bs translate <-0.294000,bh+sheight/2,0.686000>}
object {ws translate <-0.392000,bh+sheight/2,0.392000>}
object {bs translate <-0.392000,bh+sheight/2,0.490000>}
object {bs translate <-0.392000,bh+sheight/2,0.588000>}
object {ws translate <-0.490000,bh+sheight/2,-0.686000>}
object {ws translate <-0.490000,bh+sheight/2,-0.490000>}
object {ws translate <-0.490000,bh+sheight/2,-0.392000>}
object {bs translate <-0.490000,bh+sheight/2,-0.294000>}
object {ws translate <-0.490000,bh+sheight/2,0.490000>}
object {ws translate <-0.588000,bh+sheight/2,-0.588000>}
object {bs translate <-0.588000,bh+sheight/2,-0.490000>}
object {bs translate <-0.588000,bh+sheight/2,-0.392000>}
object {bs translate <-0.588000,bh+sheight/2,-0.294000>}
object {bs translate <-0.588000,bh+sheight/2,-0.098000>}
object {bs translate <-0.588000,bh+sheight/2,0.000000>}
object {ws translate <-0.588000,bh+sheight/2,0.490000>}
object {bs translate <-0.588000,bh+sheight/2,0.588000>}
object {bs translate <-0.588000,bh+sheight/2,0.686000>}
object {ws translate <-0.686000,bh+sheight/2,-0.784000>}
object {ws translate <-0.686000,bh+sheight/2,-0.686000>}
object {bs translate <-0.686000,bh+sheight/2,-0.588000>}
object {bs translate <-0.686000,bh+sheight/2,-0.490000>}
object {ws translate <-0.686000,bh+sheight/2,-0.294000>}
object {ws translate <-0.686000,bh+sheight/2,-0.196000>}
object {bs translate <-0.686000,bh+sheight/2,-0.098000>}
object {ws translate <-0.686000,bh+sheight/2,0.000000>}
object {bs translate <-0.686000,bh+sheight/2,0.098000>}
object {ws translate <-0.686000,bh+sheight/2,0.392000>}
object {bs translate <-0.686000,bh+sheight/2,0.490000>}
object {bs translate <-0.784000,bh+sheight/2,-0.686000>}
object {ws translate <-0.784000,bh+sheight/2,-0.098000>}
object {ws translate <-0.784000,bh+sheight/2,0.098000>}
object {ws translate <-0.784000,bh+sheight/2,0.392000>}
object {bs translate <-0.784000,bh+sheight/2,0.490000>}
object {ws translate <-0.882000,bh+sheight/2,0.000000>}
}


#declare grid = object {union {
object {vline translate <0.882000,0,0>}
 object {hline translate <0,0,-0.882000>}
object {vline translate <0.784000,0,0>}
 object {hline translate <0,0,-0.784000>}
object {vline translate <0.686000,0,0>}
 object {hline translate <0,0,-0.686000>}
object {vline translate <0.588000,0,0>}
 object {hline translate <0,0,-0.588000>}
object {vline translate <0.490000,0,0>}
 object {hline translate <0,0,-0.490000>}
object {vline translate <0.392000,0,0>}
 object {hline translate <0,0,-0.392000>}
object {vline translate <0.294000,0,0>}
 object {hline translate <0,0,-0.294000>}
object {vline translate <0.196000,0,0>}
 object {hline translate <0,0,-0.196000>}
object {vline translate <0.098000,0,0>}
 object {hline translate <0,0,-0.098000>}
object {vline translate <-0.000000,0,0>}
 object {hline translate <0,0,0.000000>}
object {vline translate <-0.098000,0,0>}
 object {hline translate <0,0,0.098000>}
object {vline translate <-0.196000,0,0>}
 object {hline translate <0,0,0.196000>}
object {vline translate <-0.294000,0,0>}
 object {hline translate <0,0,0.294000>}
object {vline translate <-0.392000,0,0>}
 object {hline translate <0,0,0.392000>}
object {vline translate <-0.490000,0,0>}
 object {hline translate <0,0,0.490000>}
object {vline translate <-0.588000,0,0>}
 object {hline translate <0,0,0.588000>}
object {vline translate <-0.686000,0,0>}
 object {hline translate <0,0,0.686000>}
object {vline translate <-0.784000,0,0>}
 object {hline translate <0,0,0.784000>}
object {vline translate <-0.882000,0,0>}
 object {hline translate <0,0,0.882000>}
object {hoshis}
}
pigment {grid_pigment} finish {grid_finish}}

#declare woodboard=object {
 difference {
object{box{<-1,-bh,-1> <1,bh,1>}} object{grid scale<1,1.01,1>} }
pigment{wood_pigment} finish{wood_finish}
}

#declare goboard = union { object{woodboard} object{grid} object{stones}}
