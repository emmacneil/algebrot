#ifndef SHADER_HPP
#define SHADER_HPP

#include <QOpenGLFunctions>

class Shader
{
public:
    Shader(const char * filename, GLenum shaderType);
    ~Shader();

    unsigned int getReference();

private:
    unsigned int reference;

    bool checkStatus();
    std::string readSource(const char * filename);
};

#endif // SHADER_HPP
