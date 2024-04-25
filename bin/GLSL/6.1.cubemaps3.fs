#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragWorldPos;
    vec3 WorldNormal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_height1;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
	vec3 color = texture(texture_diffuse1, fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragWorldPos);
    vec3 normal = normalize(fs_in.WorldNormal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(cameraPos - fs_in.FragWorldPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color
	
	
	vec3 I = normalize(fs_in.FragWorldPos - cameraPos);
    vec3 R = reflect(I, normalize(normal));
	vec3 reflection = vec3(texture(texture_height1, fs_in.TexCoords)*texture(skybox, R)).rgb;
	
    FragColor = vec4(ambient + diffuse + specular + reflection, 1.0);
}