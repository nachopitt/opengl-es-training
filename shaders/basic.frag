#version 100

precision mediump float;

// Conditionally include varyings and uniforms
#ifdef HAS_COLOR
varying vec4 v_Color;
#endif

#ifdef HAS_TEXTURE
varying vec2 v_TexCoord;
uniform sampler2D u_Texture;
#endif

#ifdef HAS_LIGHTING
varying vec3 v_Normal;
varying vec3 v_FragPos;
uniform vec3 u_LightDirection;
uniform vec3 u_LightColor;
#endif

void main()
{
    // Start with a default color (white).
    // If HAS_COLOR is not defined, this will be the base color.
    vec4 baseColor = vec4(1.0);

    // If the shader was compiled with color support, use the vertex color.
#ifdef HAS_COLOR
    baseColor = v_Color;
#endif

    // If the shader was compiled with texture support...
#ifdef HAS_TEXTURE
    // ...multiply the texture color by the base color.
    // If HAS_COLOR is on, this tints the texture.
    // If HAS_COLOR is off, this is just the texture color (since baseColor is white).
    gl_FragColor = texture2D(u_Texture, v_TexCoord) * baseColor;
#else
    // If no texture support, just use the base color.
    gl_FragColor = baseColor;
#endif

#ifdef HAS_LIGHTING
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;
    gl_FragColor.rgb *= diffuse;
#endif
}
