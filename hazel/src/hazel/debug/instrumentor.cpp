#include "hazel/debug/instrumentor.h"

#include "hazel/core/log.h"

namespace hazel {

void Instrumentor::beginSession(const std::string& name,
                                const std::string  filepath) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (currentSession_) {
    // If there is already a current session, then close it before beginning
    // new one. Subsequent profiling output meant for the original session
    // will end up in the newly opened session instead.  That's better than
    // having badly formatted profiling output.
    if (Log::GetCoreLogger()) {  // Edge case: BeginSession() might be before
                                 // Log::Init()
      HZ_CORE_ERROR(
          "Instrumentor::beginSession('{0}') when session '{1}' already "
          "open.",
          name, currentSession_->name);
    }
    internalEndSession();
  }
  outputStream_.open(filepath);
  if (outputStream_.is_open()) {
    currentSession_ = new InstrumentationSession({name});
    writeHeader();
  } else {
    if (Log::GetCoreLogger()) {
      HZ_CORE_ERROR("Instrumentor could not open results file '{0}'.",
                    filepath);
    }
  }
}

void Instrumentor::endSession() {
  std::lock_guard<std::mutex> lock(mutex_);
  internalEndSession();
}

void Instrumentor::writeProfile(const ProfileResult& result) {
  std::stringstream json;

  std::string name = result.name;
  std::replace(name.begin(), name.end(), '"', '\'');

  json << std::setprecision(3) << std::fixed;
  json << ",{";
  json << "\"cat\":\"function\",";
  json << "\"dur\":" << (result.elapsedTime.count()) << ',';
  json << "\"name\":\"" << name << "\",";
  json << "\"ph\":\"X\",";
  json << "\"pid\":0,";
  json << "\"tid\":" << result.threadID << ",";
  json << "\"ts\":" << result.start.count();
  json << "}";

  std::lock_guard<std::mutex> lock(mutex_);
  if (currentSession_) {
    outputStream_ << json.str();
    outputStream_.flush();
  }
}

Instrumentor& Instrumentor::Get() {
  static Instrumentor s_instance;
  return s_instance;
}

void Instrumentor::writeHeader() {
  outputStream_ << "{\"otherData\": {},\"traceEvents\":[{}";
  outputStream_.flush();
}

void Instrumentor::writeFooter() {
  outputStream_ << "]}";
  outputStream_.flush();
}

void Instrumentor::internalEndSession() {
  if (currentSession_) {
    writeFooter();
    outputStream_.close();
    delete currentSession_;
    currentSession_ = nullptr;
  }
}

}  // namespace hazel
