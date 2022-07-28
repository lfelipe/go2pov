// test-room for go2pov-board
// NEEDS POV3.1 or above !
//
//
#include "goboard.inc"

#declare wood_tex = pigment {
    wood color_map {
      [0.5 color rgb<0.3,0.2,0>]
      [1 color rgb<0.2,0.2,0>]
    }
    turbulence 0.8 scale 0.1
}

#declare table_in = object {
  box{<-2,-0.3,-2><2,0,2>}
    pigment {
      granite color_map {
        [0.   color rgb <0.9,1.,0.9>]
        [0.5 color rgb<0,0,0>]
      }
      turbulence 0.5 scale 1.5
  }
  finish {
   phong 0.3
   phong_size 100
   specular .75
   roughness .001
   reflection .5
  }
}

#declare table = object {
  union {
    object{
      difference{
        box {<-2.2,-1,-2.2><2.2,0,2.2>}
        object {table_in translate<0,0.1,0>}
      }
    }
    object {table_in}
    object {cylinder {<-2.2,-3,-2.0><-2,-1,-2> 0.1} }
    object {cylinder {< 2.2,-3,-2.0>< 2,-1,-2> 0.1} }
    object {cylinder {< 2.2,-3, 2.0>< 2,-1, 2> 0.1} }
    object {cylinder {<-2.2,-3, 2.0><-2,-1, 2> 0.1} }
  }
  pigment {wood_tex}
  finish {phong 0.5 phong_size 200}
}


#declare Flame = sphere {
  <0, 0, 0>, 1
  hollow no_shadow
  finish{ambient .5}
  pigment {color rgbf <1,1,.7,.99>}
  pigment { gradient y color_map
    { [0 color rgbf <1, .8, 1, .95>][.5 color rgbf <1,.5,.7, .9>]
      [.95 color rgbf <.7,.7,.5,.7>]} turbulence .5 scale <.3,.31,.3> }
  finish {phong 1 phong_size 100 specular .75 roughness .001 reflection .5}

  interior{media{
      emission 1
      emission rgb <1,1,.7>
      density { spherical
        color_map{
          [0.0 rgb <1,0,1>]
          [0.5 rgb <1, 1,0>]
          [1.0 rgb <1,0,0>]
        } turbulence 0.5}
      density { spherical
        color_map{
          [0.0 rgb <1,1,0>]
          [0.6 rgb <1,1, 0>]
          [1.0 rgb <1,0,1>]
        }
        turbulence 0.7
      }
    }
  }
}

#declare Candle = union{
  object {
    cylinder {<0,0,0><0,.7,0>0.1}
    pigment {color rgb<1,1,1>}
    normal {dents 1 scale 0.1 turbulence 0.3}
    finish {phong 0.1}
  }
  object {
    cylinder {<0,0,0><0,0.75,0>0.01}
    pigment {color rgb<0,0,0>}
  }
  object {Flame scale <.03,0.3,.03> translate <0,.92,0>}
  light_source {<0,1,0> color rgb<1,1,0.7>}
}

#declare CandleHolder = object
{
  lathe { quadratic_spline 5,
    <0,0> <0.2,0> <0.3,.3> <0.5,.4> <0.4,.05>
  }
  pigment { color rgb <0.4,.4,.2>}
  finish {phong 2 phong_size 200}
  normal {dents .5 scale <1,1,4> turbulence .3}
}

#declare CandleUnit = union
{
  object {CandleHolder scale<0.5,.3,.5>}
  object {Candle}
}


#declare w1_box = object {
  lathe{ quadratic_spline 5,
    <0,0> <0.4,0> <0.5,0.3> <0.4,0.5> <0,0.5>
  }
  pigment {wood color_map {
      [0.0 color rgb< 0.7,0.6,0.2>]
      [0.8 color rgb< 0.65,0.5,0.1>]
    } turbulence 0.4 scale <1,0.4,1>
  }
  finish {phong 0.2 phong_size 200}
  normal {dents 0.2 scale .1}
}

#declare s_box =
union{
  difference {
    object {w1_box}
    object {w1_box scale .95}
    object {cylinder {<0,.4,0> <0,0.6,0> .39}}
  }
  cylinder {<0,0,0><0,0.02,0> 0.4}}


#declare black_box = union
{
  object {s_box scale <.33,0.5,.33> translate <0,-.1,0>}
  object {bs translate<0,.1,0>}
  object {bs translate<.1,.1,0>}
  object {bs translate<.05,.1,.07>}
  object {bs translate<.02,.05,.03>}
  object {bs translate<-.1,.1,0>}
  object {bs translate<-.05,.1,.03>}
  object {bs translate<-.02,.05,.07>}
  object {bs translate<-.1,.05,0>}
  object {bs translate<-.05,.1,-.03>}
  object {bs translate<-.02,.05,-.07>}
}

#declare white_box = union
{
  object {s_box scale <.33,0.5,.33> translate <0,-.1,0>}
  object {ws translate<0,.1,0>}
  object {ws translate<.1,.1,0>}
  object {ws translate<.05,.1,.07>}
  object {ws translate<.02,.05,.03>}
  object {ws translate<-.1,.1,0>}
  object {ws translate<-.05,.1,.03>}
  object {ws translate<-.02,.05,.07>}
  object {ws translate<-.1,.05,0>}
  object {ws translate<-.05,.1,-.03>}
  object {ws translate<-.02,.05,-.07>}
}


object {table}
object {goboard}
object {CandleUnit scale .5 translate <1.5,0,.1>}
object {CandleUnit scale .5 translate <-1.5,0,-.1>}

object {ws translate <0,sheight/2,-1.2>}
object {ws translate <0.4,sheight/2,-1.2>}
object {ws translate <0.2,sheight/2,-1.3>}
object {ws translate <0.4,sheight/2,-1.4>}
object {white_box rotate <0,60,0> translate <1,0.1,-1.5>}

object {bs translate <0,sheight/2,1.2>}
object {bs translate <-0.3,sheight/2,1.1>}
object {bs translate <-0.2,sheight/2,0.9>}
object {black_box translate <-1.3,0.1,1.1>}


light_source {<1.2,5,0> color rgb <1,1,1>}
camera { location <1,2,2.5> look_at<0,0,0> }

sky_sphere {
  pigment {
    gradient y color_map {[0 color rgb<0.3,.3,.4>]
	[1 color rgb <0,.6,.7>]}
    scale 2
    translate -1
  }

  pigment { bozo turbulence 0.65 octaves 6
    omega 0.7 lambda 2 color_map {
      [0.0 0.1 color rgb <0.85, 0.85, 0.85> color rgb <0.75, 0.75, 0.75>]
      [0.1 0.5 color rgb <0.75, 0.75, 0.75> color rgbt <1, 1, 1, 1>]
      [0.5 1.0 color rgbt <1, 1, 1, 1> color rgbt <1, 1, 1, 1>]
    } scale <0.2, 0.5, 0.2>}
  rotate -135*x
}

plane { <0, 1, 0>, -1 translate <0,-3,0>
  pigment { color rgb <0,0.2,0>}
}
