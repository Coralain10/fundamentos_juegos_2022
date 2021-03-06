#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float delta;
uniform sampler2D myImage;

void main() {
  //color = vec4(1.0,0.0,1.0,1.0);
  //color = fragmentColor;
  //color = fragmentColor + vec4(
    //1.0 * ( cos ( delta ) + 1.0 ) * 0.5,
    //1.0 * ( cos ( delta + 2.0 ) + 1.0 ) * 0.5,
    //1.0 * ( cos ( delta + 1.0 ) + 1.0 ) * 0.5,
    //0.0
  //);

  vec4 textureColor = texture(myImage,fragmentUV);

  color = vec4(fragmentColor.r * (cos(fragmentPosition.x*4.0 + delta) + 1) * 0.5,
		fragmentColor.g * (cos(fragmentPosition.y * 8.0 + delta) *0.5),
		fragmentColor.b * (cos(fragmentPosition.y * 2.0 + delta) *0.5),
		fragmentColor.a
	) * textureColor;
}