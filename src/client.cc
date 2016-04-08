#include <v8.h>
#include <node.h>
#include <nan.h>
#include <iostream>
#include <sstream>
#include <udt.h>
#include <stdio.h>
#include <cstdlib>
#include "client.h"

using namespace v8;
using namespace node;
using namespace std;

Nan::Persistent<v8::Function> Client::constructor;

UDTSOCKET client;

Client::Client() {
}

Client::~Client() {
}

void Client::Init(v8::Local<v8::Object> exports) {


  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Client").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "firemetrics", FireMetrics);
  Nan::SetPrototypeMethod(tpl, "connect", Connect);
  Nan::SetPrototypeMethod(tpl, "write", Write);
  Nan::SetPrototypeMethod(tpl, "end", End);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("Client").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(Client::New) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new Client(...)`
    Client* obj = new Client();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `Client(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

NAN_METHOD(Client::Connect) {
  Nan::HandleScope scope;

  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("Port must be supplied");
    return;
  }

  int port = info[0]->Uint32Value();

  const char *host_arr = NULL;

  if(!info[1]->IsUndefined()) {
    if (!info[1]->IsString()) {
      Nan::ThrowTypeError("Host must be supplied");
      return;
    }
    v8::String::Utf8Value utfStr(info[1]);
    host_arr = (char*) *utfStr;
  } else {
    host_arr = "127.0.0.1";
  }

  UDT::startup();
  struct addrinfo hints, *local, *peer;

  memset(&hints, 0, sizeof(struct addrinfo));

   hints.ai_flags = AI_PASSIVE;
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   //hints.ai_socktype = SOCK_DGRAM;

   if (0 != getaddrinfo(NULL, "9000", &hints, &local))
   {
      //TODO: Raise Error
      cout << "incorrect network address.\n" << endl;
   }

   client = UDT::socket(local->ai_family, local->ai_socktype, local->ai_protocol);

   #ifdef WIN32
      UDT::setsockopt(client, 0, UDT_MSS, new int(1052), sizeof(int));
   #endif

   freeaddrinfo(local);

   std::stringstream out;
   out << port;
   string service(out.str());

   if (0 != getaddrinfo(host_arr, service.c_str(), &hints, &peer))
   {
      //TODO: Raise Error
      cout << "incorrect server/peer address. " << "argv[1]" << ":" << port << endl;

   }

   // connect to the server, implict bind
   if (UDT::ERROR == UDT::connect(client, peer->ai_addr, peer->ai_addrlen))
   {
      //TODO: Raise Error
      cout << "connect: " << UDT::getlasterror().getErrorMessage() << endl;

   }

   freeaddrinfo(peer);
}

NAN_METHOD(Client::Write) {

}

NAN_METHOD(Client::End) {

}

NAN_METHOD(Client::FireMetrics) {

}