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

in vec3 WorldPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 fragPosLight;

// Gets the Texture Units from the main function
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_metaliness0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_emissive0;

// IBL
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;


uniform vec3 camPos;

uniform bool useNormalMap;
uniform bool useMRMap;
uniform bool useAOMap;
uniform bool useEMap;

uniform float metalAmplifier;
uniform float roughnessAmplifier;
uniform float aoAmplifier;
uniform float emissiveAmplifier;


uniform float gamma;
uniform float sSamples;
uniform float sBaises;
uniform float sOffset;
uniform float lAmbient;
uniform float shadowAmbient;
uniform float sampleSize;

uniform float numLights;
uniform Light lights[100];

const float PI = 3.14159265359;

float VanDerCorput(uint n, uint base)
{
    float invBase = 1.0 / float(base);
    float denom   = 1.0;
    float result  = 0.0;

    for(uint i = 0u; i < 32u; ++i)
    {
        if(n > 0u)
        {
            denom   = mod(float(n), 2.0);
            result += denom * invBase;
            invBase = invBase / 2.0;
            n       = uint(float(n) / 2.0);
        }
    }

    return result;
}
// ----------------------------------------------------------------------------
vec2 Hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N), VanDerCorput(i, 2u));
}

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(texture_normal0, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

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

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}




void main() {
    vec3 albedo     = pow(texture(texture_diffuse0, TexCoords).rgb, vec3(2.2));
    vec3 N;
    float metallic;
    float roughness;
    float ao;
    vec3 emissivity; 
    ao = aoAmplifier;

    if (useNormalMap) {
        N     = getNormalFromMap(); // N = Normals
    }else {
        N = normalize(Normal);
    }
    if (useMRMap) {
       metallic  = texture(texture_metaliness0, TexCoords).g * metalAmplifier;
       roughness = texture(texture_metaliness0, TexCoords).b * roughnessAmplifier;
    } else {
         metallic = max(metalAmplifier, 0.001);
         roughness = roughnessAmplifier;
    }
	
    if (useEMap) {
        emissivity  = texture(texture_emissive0, TexCoords).rgb;
    } else {
        emissivity = vec3(0.1, 0.1, 0.1);
    }

    vec3 V = normalize(camPos - WorldPos); // View Pos;
    vec3 R = reflect(-V, N);

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);
    for (int i = 0; i < 2; i++) {

            
        if (lights[i].lightType == 1) { // Direct Light
           vec3 L = normalize(-lights[i].lightAngle);
           vec3 H = normalize(V + L);

           vec3 radiance = lights[i].lightColor * lights[i].lightInten;

           float NDF = DistributionGGX(N, H, roughness);
           float G   = GeometrySmith(N, V, L, roughness);
           vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

           vec3 numerator    = NDF * G * F;
           float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
           vec3 specular = numerator / denominator;

           vec3 kS = F;

           vec3 kD = vec3(1.0) - kS;

           kD *= 1.0 - metallic;

           float NdotL = max(dot(N, L), 0.0);



           Lo += ((kD * albedo / PI + specular) * radiance * NdotL);

        } else if (lights[i].lightType == 2) { // Point Light
            vec3 L = normalize(-lights[i].lightPosition - WorldPos);
            vec3 H = normalize(V + L);
            float distance = length(-lights[i].lightPosition - WorldPos);
            float attenuation = 1.0 / (distance * distance);
            vec3 radiance = lights[i].lightColor * lights[i].lightInten  * 100 * attenuation;

           float NDF = DistributionGGX(N, H, roughness);
           float G   = GeometrySmith(N, V, L, roughness);
           vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

           vec3 numerator    = NDF * G * F;
           float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
           vec3 specular = numerator / denominator;

           vec3 kS = F;

           vec3 kD = vec3(1.0) - kS;

           kD *= 1.0 - metallic;

           float NdotL = max(dot(N, L), 0.0);

           Lo += ((kD * albedo / PI + specular) * radiance * NdotL);

        }
    }
    vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);

    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;

    vec3 irradiance = texture(irradianceMap, N).rgb * aoAmplifier;
    vec3 diffuse      = irradiance * albedo;

    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf  = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * ao;

    vec3 color = ambient + Lo + emissivity;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color , 1.0);
}













































