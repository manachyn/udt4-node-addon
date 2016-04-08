#ifndef CLIENT_H
#define CLIENT_H

#include <nan.h>

class Client : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Client();
  ~Client();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Connect(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Write(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void End(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void FireMetrics(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
};

#endif