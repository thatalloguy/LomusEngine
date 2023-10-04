#version 330 core

struct Light {
    vec3 lightPosition;
    vec3 lightColor;
    float lightInten;
};

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

in vec4 fragPosLight;
in vec3 fragPos;
in mat3 TBN;


in vec3 TangentViewPos;
in vec3 TangentFragPos;

// Gets the Texture Units from the main function
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;

uniform sampler2D shadowMap;
uniform samplerCube shadowCubeMap;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
uniform float lightInten;

// Gets the position of the camera from the main function
uniform vec3 camPos;
uniform bool isTransparent;
uniform float farPlane;
uniform int lightType;
uniform vec2 fog;
uniform int castShadow;

uniform float gamma;
uniform float sSamples;
uniform float sBaises;
uniform float sOffset;
uniform float lAmbient;
uniform float shadowAmbient;

uniform int numLights;
uniform Light lights[100];


vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float distributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float denom = NdotH2 * (a2 - 1.0) + 1.0;
    return a2 / (3.141592 * denom * denom);
}

float geometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float denom = NdotV * (1.0 - k) + k;
    return NdotV / denom;
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = geometrySchlickGGX(NdotV, roughness);
    float ggx2 = geometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}


float ShadowCubeCalculation(vec3 fragPos)
{
    //vec3(light.lightPosition.x, light.lightPosition.x, light.lightPosition.x);
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    // use the light to fragment vector to sample from the depth map
    float closestDepth = texture(shadowCubeMap, fragToLight).r;
    // it is currently in linear range between [0,1]. Re-transform back to original value
    closestDepth *= farPlane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // now test for shadows
    float shadow  = 0.0;
    float bias    = sBaises;//100;
    float samples = sSamples;//4.0;
    float offset  = sOffset;//30.7;
    for(float x = -offset; x < offset; x += offset / (samples * 0.5))
    {
        for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        {
            for(float z = -offset; z < offset; z += offset / (samples * 0.5))
            {
                float closestDepth = texture(shadowCubeMap, fragToLight + vec3(x, y, z)).r;
                closestDepth *= farPlane;   // undo mapping [0;1]
                if(currentDepth - bias > closestDepth)
                shadow += 1.0;
            }
        }
    }
    shadow /= (samples * samples * samples);

    return shadow;
}


void main()
{
    // Normalize the surface normal
    vec3 normal = texture(texture_normal0, texCoord).rgb ;//normalize(Normal);
    normal =normal * 2.0 - 1.0;
    normal = normalize(TBN * normal);


    vec3 lightPosition = vec3(0.0, 5.0, 0.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.1;

    float metallic = texture(texture_specular0, texCoord).b;
    float roughness = 0.2;
    vec3 ambient = texture(texture_diffuse0, texCoord).rgb;

    vec3 finalColor = vec3(0);

    for (int i=0;i<numLights;i++) {
        // Calculate the light direction and distance
        vec3 lightDir = normalize(lights[i].lightPosition - (fragPos));

        // Calculate the view direction
        vec3 viewDir = normalize(-(TBN * fragPos));

        // Calculate the halfway vector
        vec3 halfwayDir = normalize(lightDir + viewDir);

        // Calculate the Fresnel reflectance
        vec3 F0 = vec3(0.04); // Schlick's approximation for dielectric reflectance
        vec3 F = fresnelSchlick(max(dot(normal, viewDir), 0.0), F0);

        // Calculate the specular intensity
        float roughnessFactor = roughness;
        float metallicFactor = metallic;
        vec3 specular = vec3(0.0);
        if (metallicFactor > 0.0) {
            float D = distributionGGX(normal, halfwayDir, roughnessFactor);
            float G = geometrySmith(normal, viewDir, lightDir, roughnessFactor);
            vec3 numerator = D * G * F;
            float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * max(dot(normal, lightDir), 0.0);
            specular = numerator / max(denominator, 0.001);
        }

        // Calculate the diffuse intensity using Lambertian reflection model
        vec3 diffuse = lights[i].lightColor.xyz * (1.0 - metallicFactor) * max(dot(normal, lightDir), 0.0) * lights[i].lightInten;

        // Calculate the ambient intensity
        //ambient *= lights[i].lightColor.xyz * ambientStrength;

        // Calculate the final color
        finalColor = (ambient + diffuse + specular) * (1 - (ShadowCubeCalculation(fragPos) * 0.95));
    }



    // Output the color
    FragColor = vec4(finalColor, 1.0);
}