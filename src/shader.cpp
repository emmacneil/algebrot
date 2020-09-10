#include "shader.hpp"

#include <fstream>

#include <QDebug>

Shader::Shader(const char *filename, GLenum shaderType)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    std::string strSource = readSource(filename);
    const char * source = strSource.c_str();

    reference = f->glCreateShader(shaderType);
    f->glShaderSource(reference, 1, &source, nullptr);
    f->glCompileShader(reference);

    if (!checkStatus())
        throw std::runtime_error("Failed to compile shader");
}

Shader::~Shader()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    if (reference)
        f->glDeleteShader(reference);
}

bool Shader::checkStatus()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    // Check if shader was compiled successfully
    int success;
    f->glGetShaderiv(reference, GL_COMPILE_STATUS, &success);
    if (success)
        return true;

    // Get length of info log
    int infoLogLength;
    f->glGetShaderiv(reference, GL_INFO_LOG_LENGTH, &infoLogLength);

    // Get info log
    char infoLog[infoLogLength];
    f->glGetShaderInfoLog(reference, infoLogLength, nullptr, infoLog);
    qDebug() << infoLog;
    return false;
}

unsigned int Shader::getReference()
{
    return reference;
}

std::string Shader::readSource(const char * filename)
{
    std::ifstream fin(filename);
    std::string str;
    if (!fin.is_open())
    {
        qDebug() << "Could not open file" << filename;
        return nullptr;
    }

    fin.seekg(0, std::ios::end);
    str.reserve(fin.tellg());
    fin.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(fin)),
                std::istreambuf_iterator<char>());

    return str;
}
