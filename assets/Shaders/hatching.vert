#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

// point lights
struct PointLight
{
  vec3 position;
  float intensity;
};

uniform PointLight pointLight;

float CalculateLightWeight()
{
  vec4 pos = vec4(pointLight.position, 1.0);

  // calculate light vector in view space
  vec4 lightVec = (view * pos) - viewPos;
  vec4 lightUnitVec = normalize(lightVec);

  vec4 viewNorm = view * aNorm;

  // calculate diffuse color
  float diffuseFactor = light.intensity * max(dot(viewNorm, lightUnitVec), 0);

  // calculate light source attenuation
  vec4 d = lightVec;
  float dL = sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
  float lightAtt = min( 1.0 / (c1 + c2*dL + c3*dL*dL), 1);
  
  float lightWeight = lightAtt * diffuseFactor;

  return lightWeight;
}

void main(void)
{
  // calculate diffuse contribution (0 to 1)
  float diffuseFactor = CalculateLightWeight();

  // multiply by 6 to choose tone level (which texture to use, light to dark hatching, 0 to 6)
  float toneLevel = 6.0 * diffuseFactor;

  // find floor and ceiling texture for vertex, supply normalized weights for those two textures
  

  TexCoords = aTexCoords;
  gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
