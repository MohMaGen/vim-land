#version 330 core


in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 upper_left;
uniform vec2 width_height;
uniform float corner_radius;
uniform float border_width;
uniform vec4 border_color;

out vec4 color;


float sdRoundedBox( in vec2 p, in vec2 b, in float r ) {
    vec2 q = abs(p)-b+r;
    return min(max(q.x,q.y),0.0) + length(max(q,0.0)) - r;
}

void main() {
    vec2 lower_left = vec2(upper_left.x, upper_left.y - width_height.y);

    float border = sdRoundedBox(gl_FragCoord.xy - lower_left - (width_height / 2.0f),
        width_height / 2., corner_radius);

    float inner = sdRoundedBox(gl_FragCoord.xy - lower_left - (width_height / 2.0f),
        width_height / 2. - border_width, corner_radius - border_width);

    float b = 1 - step(0.0f, border);
    float i = 1 - step(0.0f, inner);
    if (i > 0) {
        color = vec4(fragColor.rgb, i * fragColor.a);
    } else {
        color = vec4(border_color.rgb, b * fragColor.a);
    }
    //color = vec4(border_color.rgb, b);
}

