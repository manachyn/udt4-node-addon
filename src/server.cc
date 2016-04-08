#include "server.h"

Nan::Persistent<v8::Function> Server::constructor;

Server::Server() {
}

Server::~Server() {
}

void Server::Init(v8::Local<v8::Object> exports) {

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Server").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "listen", Listen);
  Nan::SetPrototypeMethod(tpl, "close", Close);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("Server").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(Server::New) {
  if (info.IsConstructCall()) {
    Server* obj = new Server();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

NAN_METHOD(Server::Listen) {
  
}

NAN_METHOD(Server::Close) {

}