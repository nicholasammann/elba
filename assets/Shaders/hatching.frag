#version 330 core
layout(location=0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 pos;
in vec3 norm;

// light textures
uniform sampler2D lightTextures;

// dark textures
uniform sampler2D darkTextures;

uniform mat4 model;
uniform mat4 view;

// point lights
struct PointLight
{
  vec3 position;
  float intensity;
};

uniform PointLight pointLight;

float CalculateLightWeight()
{
  vec4 viewPos = view * model * vec4(pos, 1.0);
  vec4 viewNorm = normalize(view * model * vec4(norm, 0.0));

  // calculate light vector in view space
  vec4 lightPos = vec4(pointLight.position, 1.0);
  vec4 lightVec = (view * lightPos) - viewPos;
  vec4 lightUnitVec = normalize(lightVec);

  // calculate diffuse color
  float diffuseFactor = pointLight.intensity * max(dot(viewNorm, lightUnitVec), 0);

  // calculate light source attenuation
  vec4 d = lightVec;
  float dL = sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
  float lightAtt = min( 1.0 / (0.3 + 0.1*dL + 0.0005*dL*dL), 1);
  
  float lightWeight = lightAtt * diffuseFactor;

  return lightWeight;
}

void main(void)
{
  // calculate diffuse contribution (0 to 1)
  float diffuseFactor = CalculateLightWeight();

  // multiply by 6 to choose tone level (which texture to use, light to dark hatching, 0 to 6)
  float toneLevel = 6.0 * diffuseFactor;

  float col = 0.0;

  vec4 lightPix = texture(lightTextures, TexCoords.st);
  vec4 darkPix = texture(darkTextures, TexCoords.st);

  col = mix(darkPix.r, lightPix.b, 0.5);

  if (toneLevel < 1.0)
  {
    col = mix(darkPix.b, darkPix.g, toneLevel);
  }
  else if (toneLevel < 2.0)
  {
    col = mix(darkPix.g, darkPix.r, toneLevel - 1.0);
  }
  else if (toneLevel < 3.0)
  {
    col = mix(darkPix.r, lightPix.b, toneLevel - 2.0);
  }
  else if (toneLevel < 4.0)
  {
    col = mix(lightPix.b, lightPix.g, toneLevel - 3.0);
  }
  else if (toneLevel < 5.0)
  {
    col = mix(lightPix.g, lightPix.r, toneLevel - 4.0);
  }
  else
  {
    col = mix(lightPix.r, 1.0, toneLevel - 5.0);
  }

  FragColor = vec4(col, col, col, 1.0);
}
