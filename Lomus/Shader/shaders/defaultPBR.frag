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
in vec3 fragPos; // unused
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

uniform int numLights;
uniform Light lights[100];

//These should be replaced with uniforms later on :/
vec3 baseReflectance = vec3(0.04,0.04,0.04);
vec3 emissivityMesh = vec3(0.1, 0.1, 0.1);




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
    vec3 lightDir = normalize(lightPos - crntPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
    shadow = 0.0;

    return shadow;
}

float ShadowCubeCalculation(vec3 fragPos, Light light)
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
    float bias    = 100;
    float samples = 4.0;
    float offset  = 30.7;
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

vec4 pointLightB(Light light) {

    vec3 lightVec = light.lightPosition - crntPos;

    // intensity of light with respect to distance
    float dist = length(lightVec);
    float a = 0.0003f;
    float b = 0.00002f;
    float inten = light.lightInten / (a * dist * dist + b * dist + 1.0f);

    // ambient lighting
    float ambient = 0.40f;

    // diffuse lighting


    //Normal maps
    vec3 normal = texture(texture_normal0, texCoord).rgb ;//normalize(Normal);
    normal =normal * 2.0 - 1.0;
    normal = normalize(TBN * normal);




    vec3 lightDirection = normalize(light.lightPosition - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // specular lighting
    float specular = 0.2f;
    if (diffuse != 0.0f)
    {
        float specularLight = 0.50f;
        vec3 viewDirection = normalize((TBN * camPos) - (TBN * crntPos));
        vec3 halfwayVec = normalize(viewDirection + lightDirection);
        float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
        specular = specAmount * specularLight;
    };
    float shadow = 0;
    if (castShadow == 1) {
        shadow = ShadowCubeCalculation(crntPos, light) * 0.85;
    }


    //
    //texture(texture_diffuse0, texCoord);
    return (texture(texture_diffuse0, texCoord) * (diffuse * (1.0f - shadow) * inten + ambient) + texture(texture_specular0, texCoord).b * specular * (1.0f - shadow) * inten) * vec4(light.lightColor, 1);


}
vec4 directLight(Light light)
{

    vec3 color = vec3(1, 1, 1);//texture(diffuse0, texCoord).rgb;
    vec3 normal = normalize(Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.5 * color;
    // diffuse
    vec3 lightDir = normalize(vec3(light.lightPosition[0], light.lightPosition[1], light.lightPosition[2]) - crntPos);
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

    //corect the normal stuff
    //camPos = TBN * camPos;
    //crntPos = TBN * crntPos;


    vec4 color = vec4(0);
    // outputs final color
    float depth = logisticDepth(gl_FragCoord.z);
    if (fog.x != 0) {
        if (lightType == 0) {
            //////////// THE DIRECT LIGHT IS SET BE DEFAULT TO THE FIRST CREATED LIGHT PLEASE CHANGE THIS ONCE YOU HAVE A PROPER IMPLEMNTATION
            color += directLight(lights[0]) * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
        } else {
            for (int i = 0; i < numLights; i++) {
                color += pointLightB(lights[i]) * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
            }
        }
    } else {
        if (lightType == 0) {
            color += directLight(lights[0]);
        } else {
            for (int i = 0; i < numLights; i++) {
                color += pointLightB(lights[i]);
            }
        }
    }
    color.a = 1;
    FragColor =  vec4(pow(color.xyz, vec3(1.0f / gamma)), 1.0);

}