#include <napi.h>
#include <string>
#include <vector>
#include "decoder.h"

Napi::String decoder(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string file = info[0].ToString();
    std::string result = decode(file);
    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "decode"),
        Napi::Function::New(env, decoder)
    );

    return exports;
}

NODE_API_MODULE(zbardecoder, Init);