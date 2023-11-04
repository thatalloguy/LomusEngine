#include"shaderClass.h"


class mat4;

class mat4;

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::cout << "Couldn't load: " << filename << "\n";
	throw(errno);
}

void toekkenize(std::string const& str, const char delim, std::vector<std::string>& out) // For spliting string
{

    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}


int getNumberFromString(std::string str)
{
    std::vector<std::string> output1;
    std::vector<std::string> output2;

    toekkenize(str, '(', output1);
    toekkenize(output1[1], ')', output2);

    std::cout << output2[0] << "\n";

    return std::stoi(output2[0]);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings

    Shader::vertexFile = vertexFile;
    Shader::fragmentFile = fragmentFile;

	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Checks if Shaders linked succesfully
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{

    Shader::vertexFile = vertexFile;
    Shader::fragmentFile = fragmentFile;
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);
	std::string geometryCode = get_file_contents(geometryFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
	const char* geometrySource = geometryCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Geometry Shader Object and get its reference
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	// Attach Geometry Shader source to the Fragment Shader Object
	glShaderSource(geometryShader, 1, &geometrySource, NULL);
	// Compile the Geometry Shader into machine code
	glCompileShader(geometryShader);
	// Checks if Shader compiled succesfully
	compileErrors(geometryShader, "GEOMETRY");

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glAttachShader(ID, geometryShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Checks if Shaders linked succesfully
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}

void Shader::setIntUniform(const char* name, int value)
{

	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setVec3Uniform(const char* name, float x, float y, float z)
{

	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::setVec4Uniform(const char* name, float x, float y, float z, float w)
{

	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::setFloatUniform(const char* name, float f) {

    glUniform1f(glGetUniformLocation(ID, name), f);
}

void Shader::setMat4Uniform(const char *name, glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::getUniformLocation(const char* name)
{

	return glGetUniformLocation(ID, name);
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Deactivate()
{
	glUseProgram(0);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Checks if the different Shaders have compiled properly
bool Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;

	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
            currentErrorMessage = infoLog;
            currentErrorLine = getNumberFromString(infoLog);
            Shader::isBroken = true;
            return false;
		} else if (hasCompiled == GL_TRUE) {
            currentErrorLine = -1;
            Shader::isBroken = false;
        }
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
            currentErrorMessage = infoLog;
            currentErrorLine = getNumberFromString(infoLog);
            Shader::isBroken = true;
            return false;
		} else  if (hasCompiled == GL_TRUE){
            currentErrorLine = -1;
            Shader::isBroken = false;
        }
	}

}

bool Shader::reCompile() {
    // Delete the existing shader program

    // Read the new shader source code
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);
    std::string geometryCode;

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cerr << "Failed to load shader source code." << std::endl;
    }

   // glDeleteProgram(ID);

    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create new shader objects and compile them
    GLuint newVertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint newFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(newVertexShader, 1, &vertexSource, NULL);
    glShaderSource(newFragmentShader, 1, &fragmentSource, NULL);


    glCompileShader(newVertexShader);
    glCompileShader(newFragmentShader);


    // Check for compilation errors
    compileErrors(newVertexShader, "VERTEX");
    compileErrors(newFragmentShader, "FRAGMENT");

    // Create a new shader program and link the shaders
    ID = glCreateProgram();
    glAttachShader(ID, newVertexShader);
    glAttachShader(ID, newFragmentShader);


    glLinkProgram(ID);

    // Check for linking errors
    compileErrors(ID, "PROGRAM");

    // Delete the old shader objects
    glDeleteShader(newVertexShader);
    glDeleteShader(newFragmentShader);
    return true;
}

std::string Shader::getErrorMessage() {
    return currentErrorMessage;
}

int Shader::getErrorLine() {
    return Shader::currentErrorLine;
}
