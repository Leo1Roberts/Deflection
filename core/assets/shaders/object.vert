layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec4 inColor;

out vec2 fragUV;
out vec3 fragNormal;
out vec3 fragColor;

uniform mat3 uBodyToViewRot;
uniform mat4 uBodyToView;
uniform mat4 uProjection;

void main() {
    fragUV = inUV;
    fragNormal = uBodyToViewRot * inNormal;
    fragColor = inColor.rgb;
    gl_Position = uProjection * uBodyToView * vec4(inPos, 1.0);
}