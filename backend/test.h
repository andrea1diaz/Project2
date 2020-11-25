#include <napi.h>

#include <iostream>
#include <string>

namespace api {
	std::string hello();
	Napi::String HelloWrapped (const Napi::CallbackInfo& info);
	Napi::Object Init(Napi::Env env, Napi::Object exports);
}
