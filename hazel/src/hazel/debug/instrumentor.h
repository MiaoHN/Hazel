#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>

namespace hazel {

struct ProfileResult {
  std::string name;
  long long   start, end;
  uint32_t    threadID;
};

struct InstrumentationSession {
  std::string name;
};

class Instrumentor {
 public:
  Instrumentor() : currentSession_(nullptr), profileCount_(0) {}

  void beginSession(const std::string& name,
                    const std::string  filepath = "result.json") {
    outputStream_.open(filepath);
    writeHeader();
    currentSession_ = new InstrumentationSession{name};
  }

  void endSession() {
    writeFooter();
    outputStream_.close();
    delete currentSession_;
    currentSession_ = nullptr;
    profileCount_   = 0;
  }

  void writeProfile(const ProfileResult& result) {
    if (profileCount_++ > 0) {
      outputStream_ << ",";
    }

    std::string name = result.name;
    std::replace(name.begin(), name.end(), '"', '\'');

    outputStream_ << "{";
    outputStream_ << "\"cat\":\"function\",";
    outputStream_ << "\"dur\":" << (result.end - result.start) << ',';
    outputStream_ << "\"name\":\"" << name << "\",";
    outputStream_ << "\"ph\":\"X\",";
    outputStream_ << "\"pid\":0,";
    outputStream_ << "\"tid\":" << result.threadID << ",";
    outputStream_ << "\"ts\":" << result.start;
    outputStream_ << "}";

    outputStream_.flush();
  }

  void writeHeader() {
    outputStream_ << "{\"otherData\": {},\"traceEvents\":[";
    outputStream_.flush();
  }

  void writeFooter() {
    outputStream_ << "]}";
    outputStream_.flush();
  }

  static Instrumentor& Get() {
    static Instrumentor s_instance;
    return s_instance;
  }

 private:
  InstrumentationSession* currentSession_;
  std::ofstream           outputStream_;
  int                     profileCount_;
};

class InstrumentationTimer {
 public:
  InstrumentationTimer(const char* name) : name_(name), stopped_(false) {
    startTimePoint_ = std::chrono::high_resolution_clock::now();
  }

  ~InstrumentationTimer() {
    if (!stopped_) {
      stop();
    }
  }

  void stop() {
    auto endTimePoint = std::chrono::high_resolution_clock::now();

    long long start =
        std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint_)
            .time_since_epoch()
            .count();
    long long end =
        std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint)
            .time_since_epoch()
            .count();

    uint32_t threadID =
        std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::Get().writeProfile({name_, start, end, threadID});

    stopped_ = true;
  }

 private:
  const char* name_;
  bool        stopped_;

  std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint_;
};

}  // namespace hazel

#define HZ_PROFILE 1
#if HZ_PROFILE
#define HZ_PROFILE_BEGIN_SESSION(name, filepath) \
  ::hazel::Instrumentor::Get().beginSession(name, filepath)
#define HZ_PROFILE_END_SESSION() ::hazel::Instrumentor::Get().endSession()
#define HZ_PROFILE_SCOPE(name) \
  ::hazel::InstrumentationTimer timer##__LINE__(name)
#define HZ_PROFILE_FUNCTION() HZ_PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name)
#define HZ_PROFILE_FUNCTION()
#endif  // HZ_PROFILE