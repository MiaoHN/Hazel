#include "hazel/renderer/shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "hazel/log.h"
#include "hzpch.h"

namespace hazel {

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
  unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);

  const char* source = vertexSrc.c_str();
  glShaderSource(vertexShader, 1, &source, 0);

  glCompileShader(vertexShader);
  int isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    int maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(vertexShader);

    HZ_CORE_ERROR("{0}", infoLog.data());
    HZ_CORE_ASSERT(false, "Vertex shader complication failure!");
    return;
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  source = fragmentSrc.c_str();

  glShaderSource(fragmentShader, 1, &source, 0);

  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    int maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    HZ_CORE_ERROR("{0}", infoLog.data());
    HZ_CORE_ASSERT(false, "Fragment shader compilation failure!");
    return;
  }

  _id = glCreateProgram();
  unsigned int program = _id;

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  int isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
  if (isLinked == GL_FALSE) {
    int maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    HZ_CORE_ERROR("{0}", infoLog.data());
    HZ_CORE_ASSERT(false, "Shader link failure!");
    return;
  }

  // Always detach shaders after a successful link.
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
}

Shader::~Shader() { glDeleteProgram(_id); }

void Shader::Bind() const { glUseProgram(_id); }

void Shader::UnBind() const { glUseProgram(0); }

void Shader::UploadUniformMat4(const std::string& name,
                               const glm::mat4& matrix) {
  int location = glGetUniformLocation(_id, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

}  // namespace hazel
