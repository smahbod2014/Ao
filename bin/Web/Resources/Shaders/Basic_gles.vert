attribute highp vec4 position;
attribute highp vec2 uv;
attribute highp float tid;
attribute highp vec4 color;

uniform highp mat4 projMatrix;
//view matrix coming soon!
//uniform highp mat4 vw_matrix;

varying highp vec2 vs_uv;
varying highp float vs_tid;
varying highp vec4 vs_color;

void main()
{
	gl_Position = projMatrix * position;
	vs_uv = uv;
	vs_tid = tid;
	vs_color = color;
}