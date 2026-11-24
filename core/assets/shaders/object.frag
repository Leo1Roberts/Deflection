precision mediump float;

in vec2 fragUV;
in vec3 fragNormal;
in vec3 fragColor;

uniform sampler2D uTexture;
uniform vec3 uSunColor;
uniform vec3 uSunDirection;
uniform vec3 uUpDirection;
uniform vec3 uGroundColor;
uniform vec3 uSkyColor;
uniform float uAlpha;

out vec4 outColor;

void main() {
    vec3 normal = normalize(fragNormal);

    float upDot = dot(normal, uUpDirection) * 0.5 + 0.5;
    vec3 ambientColor = mix(uGroundColor, uSkyColor, upDot);

    float sunWrap = dot(normal, uSunDirection) * 0.5 + 0.5;
    float ldotn = sunWrap * sunWrap;
    vec3 sunComponent = uSunColor * ldotn;

    vec3 viewDir = vec3(0.0, 0.0, 1.0);
    vec3 halfwayDir = normalize(uSunDirection + viewDir);

    float ldoth = max(dot(normal, halfwayDir), 0.0);
    vec3 specular = uSunColor * pow(ldoth, 30.0) * (30.0 + 1.0) / 200.0;

    vec3 diffuseColor = texture(uTexture, vec2(fragUV.x, 1.0 - fragUV.y)).rgb * fragColor;

    outColor = vec4(diffuseColor * (ambientColor + sunComponent) + specular, uAlpha);
#ifdef GL_ES
    outColor.rgb = pow(outColor.rgb, vec3(1.0/2.2));
#endif
}