#include "test.h"

std::string api::hello () {
	return "HEllO";
}

Napi::String api::HelloWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String returnValue = Napi::String::New(env, api::hello());

  return returnValue;
}

Napi::Object api::Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
"hello", Napi::Function::New(env, api::HelloWrapped)
  );

  return exports;
}
