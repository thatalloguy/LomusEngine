#version 330 core

struct Light {
    vec3 lightPosition;
    vec3 lightColor;
    float lightInten;
    vec3 lightAngle;
    int lightType;
    bool castShadow;
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
uniform sampler2D shadowMap;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;

//uniform samplerCube shadowCubeMap;
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
uniform float randomOffset;

uniform bool useNormalMap;

#define PI 3.1415926538
uniform int shadeLevels;// 5


float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// Fresnel-schlick function the real one fr fr
vec3 F(vec3 F0, vec3 V, vec3 H) {
    return F0 + (vec3(1.0) - F0) * pow(1 - max(dot(V, H), 0.0), 5.0);
}




float ShadowCalculation(vec4 fragPosLightSpace, Light light)
{
    vec3 lightPos = vec3(light.lightPosition[0], light.lightPosition[1], light.lightPosition[2]);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-light.lightAngle - crntPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x , y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
    shadow = 0.0;

    return shadow;
}

vec4 pointLightB(Light light) {
    vec3 fixedLightPos = vec3(light.lightPosition.x, light.lightPosition.y, light.lightPosition.z);
    vec3 lightVec = fixedLightPos - fragPos;

    // intensity of light with respect to distance
    float dist = length(lightVec);
    float a = 0.0003f;
    float b = 0.00002f;
    float inten = light.lightInten / (a * dist * dist + b * dist + 1.0f);

    // ambient lighting
    float ambient = lAmbient;//0.40f;

    // diffuse lighting

    vec3 normal;
    //Normal maps
    if (useNormalMap) {
        normal = texture(texture_normal0, texCoord).rgb ;//normalize(Normal);
        normal =normal * 2.0 - 1.0;
        normal = normalize(TBN * normal);
    } else {
        normal = normalize(Normal);
    }






    vec3 lightDirection = normalize(light.lightAngle * fragPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    float level = floor(diffuse * shadeLevels);
    //diffuse;// = level / shadeLevels;

    vec3 newFragPos = fragPos;
    vec3 newCamPos = camPos;
    if (useNormalMap) {
        newFragPos = TBN * fragPos;
        newCamPos = TBN * camPos;
    }
    // specular lighting
    float specular = 0.0f;
    if (diffuse != 0.0f)
    {
        float specularLight = 0.50f;
        vec3 viewDirection = normalize(camPos - newFragPos);
        vec3 halfwayVec = normalize(viewDirection + lightDirection);
        float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
        specular = specAmount * specularLight;
    };
    float shadow = 0;
    //if (castShadow == 1) {
    //    shadow = ShadowCubeCalculation(fragPos) * shadowAmbient;
    //}


    //
    //texture(texture_diffuse0, texCoord);
    float intensity = dot(lightDirection, normal);
    vec4 color = (texture(texture_diffuse0, texCoord) * (diffuse * (1.0f - shadow) * inten + ambient) + texture(texture_specular0, texCoord).b * specular * (1.0f - shadow) * inten) * vec4(light.lightColor, 1);

    return color;




}

vec4 directLight(Light light) {

    vec3 color = texture(texture_diffuse0, texCoord).rgb;
    vec3 normal = normalize(Normal);
    vec3 lightColor = light.lightColor * light.lightInten;
    // ambient
    vec3 ambient = 0.2 * color;
    // diffuse
    vec3 lightDir = normalize(-light.lightAngle * fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(camPos - crntPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // calculate shadow
    float shadow = ShadowCalculation(fragPosLight, light);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    return vec4(lighting, 1);
}


float linearizeDepth(float depth)
{
    float near = fog.x;
    float far = fog.y;
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth)
{
    float steepness = 0.5f;
    float offset = 5.0f;
    float zVal = linearizeDepth(depth);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{

    vec4 color = vec4(0);
    // outputs final color
    float depth = logisticDepth(gl_FragCoord.z);
    for (int i=0; i<numLights; i++) {
        Light light = lights[i];
        if (light.lightType == 1) {
            color += directLight(light);
        } else if (light.lightType == 2) {
            color += pointLightB(light);
        } else {
            color = vec4(1, 0, 0.68, 1);
        }

    }
    color.a = 1;
    FragColor =  vec4(pow(color.xyz, vec3(1.0f / gamma)), 1.0);

}