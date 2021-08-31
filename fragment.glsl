#version 120
uniform float u_time;
uniform vec2 u_resolution;
void main(void) {
	vec2 st = gl_FragCoord.xy / u_resolution.xy;
	gl_FragColor[0] = abs(sin(u_time + st.x));
	gl_FragColor[1] = abs(sin((u_time * 1.5) + st.y));
	gl_FragColor[2] = abs(sin((u_time * 0.7) + ((st.x + st.y) / 2)));
}
