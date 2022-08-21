#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <string>
#include <thread>

namespace hazel {

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult {
  std::string               name;
  FloatingPointMicroseconds start;
  std::chrono::microseconds elapsedTime;
  std::thread::id           threadID;
};

struct InstrumentationSession {
  std::string name;
};

class Instrumentor {
 public:
  Instrumentor() : currentSession_(nullptr) {}

  void beginSession(const std::string& name,
                    const std::string  filepath = "result.json");

  void endSession();

  void writeProfile(const ProfileResult& result);

  static Instrumentor& Get();

 private:
  void writeHeader();

  void writeFooter();

  void internalEndSession();

 private:
  std::mutex mutex_;

  InstrumentationSession* currentSession_;
  std::ofstream           outputStream_;
  int                     profileCount_;
};

class InstrumentationTimer {
 public:
  InstrumentationTimer(const char* name) : name_(name), stopped_(false) {
    startTimePoint_ = std::chrono::steady_clock::now();
  }

  ~InstrumentationTimer() {
    if (!stopped_) {
      stop();
    }
  }

  void stop() {
    auto endTimePoint = std::chrono::steady_clock::now();

    auto highResStart =
        FloatingPointMicroseconds{startTimePoint_.time_since_epoch()};

    auto elapsedTime =
        std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint)
            .time_since_epoch() -
        std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint_)
            .time_since_epoch();

    Instrumentor::Get().writeProfile(
        {name_, highResStart, elapsedTime, std::this_thread::get_id()});

    stopped_ = true;
  }

 private:
  const char* name_;
  bool        stopped_;

  std::chrono::time_point<std::chrono::steady_clock> startTimePoint_;
};

}  // namespace hazel

#ifdef HZ_PROFILE

// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || \
    (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define HZ_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define HZ_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define HZ_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || \
    (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define HZ_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define HZ_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define HZ_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define HZ_FUNC_SIG __func__
#else
#define HZ_FUNC_SIG "HZ_FUNC_SIG unknown!"
#endif

#define HZ_PROFILE_BEGIN_SESSION(name, filepath) \
  ::hazel::Instrumentor::Get().beginSession(name, filepath)
#define HZ_PROFILE_END_SESSION() ::hazel::Instrumentor::Get().endSession()
#define HZ_PROFILE_SCOPE(name) \
  ::hazel::InstrumentationTimer timer##__LINE__(name)
#define HZ_PROFILE_FUNCTION() HZ_PROFILE_SCOPE(HZ_FUNC_SIG)

#else

#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name)
#define HZ_PROFILE_FUNCTION()

#endif  // HZ_PROFILE