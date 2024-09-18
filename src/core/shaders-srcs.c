#include <shaders.h>
// File generated with very clever make script. please don't touch with your hands. ;<





// start generate fill_rect_fragment_shader
char fill_rect_fragment_shader[] =
    "#version 330 core \n"
    " \n"
    " \n"
    "in vec2 fragTexCoord; \n"
    "in vec4 fragColor; \n"
    " \n"
    "uniform vec2 upper_left; \n"
    "uniform vec2 width_height; \n"
    "uniform float corner_radius; \n"
    "uniform float border_width; \n"
    "uniform ivec4 border_color; \n"
    " \n"
    "out vec4 color; \n"
    " \n"
    " \n"
    "float sdRoundedBox( in vec2 p, in vec2 b, in float r ) { \n"
    "    vec2 q = abs(p)-b+r; \n"
    "    return min(max(q.x,q.y),0.0) + length(max(q,0.0)) - r; \n"
    "} \n"
    " \n"
    "void main() { \n"
    "    vec2 lower_left = vec2(upper_left.x, upper_left.y - width_height.y); \n"
    " \n"
    "    float border = sdRoundedBox(gl_FragCoord.xy - lower_left - (width_height / 2.0f), \n"
    "        width_height / 2., corner_radius); \n"
    " \n"
    "    float inner = sdRoundedBox(gl_FragCoord.xy - lower_left - (width_height / 2.0f), \n"
    "        width_height / 2. - border_width, corner_radius - border_width); \n"
    " \n"
    "    float b = 1 - step(0.0f, border); \n"
    "    float i = 1 - step(0.0f, inner); \n"
    "    if (i > 0) { \n"
    "        color = vec4(fragColor.rgb, i * fragColor.a); \n"
    "    } else { \n"
    "        color = vec4(border_color.rgb / 255.f, b * fragColor.a); \n"
    "    } \n"
    "} \n"
    " \n"
    "";
const char *get_fill_rect_fragment_shader(void) { return fill_rect_fragment_shader; }
// end generate
