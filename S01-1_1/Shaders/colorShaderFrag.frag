#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform float delta;

void main() {
  //color = vec4(1.0,0.0,1.0,1.0);
  //color = fragmentColor;
  color = fragmentColor + vec4(
    1.0 * ( cos ( delta ) + 1.0 ) * 0.5,
    1.0 * ( cos ( delta + 2.0 ) + 1.0 ) * 0.5,
    1.0 * ( cos ( delta + 1.0 ) + 1.0 ) * 0.5,
    0.0
  );
}