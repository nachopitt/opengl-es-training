#version 100

// --- UNIFORMS ---
// Conditionally compiled based on the features you enable from C++.
#ifdef HAS_MVP
// A single MVP matrix is more efficient than 3 separate ones.
// Consider calculate it on the CPU: mvp = projection * view * model
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;
#endif

// --- ATTRIBUTES ---
// a_Position is the only mandatory attribute.
attribute vec3 a_Position;

#ifdef HAS_COLOR
attribute vec4 a_Color;
#endif

#ifdef HAS_TEXTURE
attribute vec2 a_TexCoord;
#endif

// --- VARYINGS ---
// These pass data to the fragment shader. They are only needed if
// the corresponding feature is enabled.
#ifdef HAS_COLOR
varying vec4 v_Color;
#endif

#ifdef HAS_TEXTURE
varying vec2 v_TexCoord;
#endif


void main()
{
    // Calculate final vertex position.
#ifdef HAS_MVP
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
#else
	// If no MVP matrix, just use the raw position (for 2D or screen-space UI).
	gl_Position = vec4(a_Position, 1.0);
#endif

	// Pass color and texture coordinates to the fragment shader if enabled.
#ifdef HAS_COLOR
	v_Color = a_Color;
#endif

#ifdef HAS_TEXTURE
	v_TexCoord = a_TexCoord;
#endif
}
