#ifndef SERVER_H
#define SERVER_H

#include <nan.h>

class Server : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Server();
  ~Server();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Listen(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Close(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
};

#endif