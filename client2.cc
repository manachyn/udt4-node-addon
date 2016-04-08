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

namespace udt4 {

  static Persistent<Function> client_constructor;
  UDTSOCKET client;
  Client::Client () {};
  Client::~Client () {};
  
  void Client::Init(Handle<Object> exports) {
     Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
     tpl->SetClassName(NanNew("Client"));
     tpl->InstanceTemplate()->SetInternalFieldCount(1);
     
     NODE_SET_PROTOTYPE_METHOD(tpl, "firemetrics", FireMetrics);
     NODE_SET_PROTOTYPE_METHOD(tpl, "connect", Connect);
     NODE_SET_PROTOTYPE_METHOD(tpl, "write", Write);
     NODE_SET_PROTOTYPE_METHOD(tpl, "end", End);
     NanAssignPersistent(client_constructor, tpl->GetFunction());
     exports->Set(NanNew<String>("Client"), tpl->GetFunction());
  }

   NAN_METHOD(Client::New) {
    NanScope();
    if(args.IsConstructCall()) {
      Client* obj = new Client();
      obj->Wrap(args.This());
      NanReturnValue(args.This());
    }
    else {
      Local<Function> cons = NanNew<Function>(client_constructor);
      NanReturnValue(cons->NewInstance());
    }
   }

   NAN_METHOD(Client::Connect) {
    NanScope();

        if (!args[0]->IsNumber()) {
          ThrowException(Exception::TypeError(String::New("Port must be supplied")));
          return scope.Close(Undefined());
        }

        int port = args[0]->Uint32Value();

        const char *host_arr = NULL;
      
        if(!args[1]->IsUndefined()) {
          if (!args[1]->IsString()) {
            ThrowException(Exception::TypeError(String::New("Port must be supplied")));
            return scope.Close(Undefined());
          }
          String::Utf8Value utfStr(args[1]);
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

         
         NanReturnUndefined();
   }

   NAN_METHOD(Client::Write) {
      NanScope();
      NanUtf8String val(args[0]);
      char *data = *val;
      int size = strlen(data);

      int ssize = 0;
      int ss;
      while (ssize < size)
      {
         if (UDT::ERROR == (ss = UDT::send(client, data + ssize, size - ssize, 0)))
         {
            cout << "send:" << UDT::getlasterror().getErrorMessage() << endl;
            break;
         }

         ssize += ss;
      }
      NanReturnUndefined();
   }

   NAN_METHOD(Client::End) {
      NanScope();
      UDT::close(client);
      NanReturnUndefined();
   }

   NAN_METHOD(Client::FireMetrics) {
       NanScope();
       Local<Object> obj = NanNew<Object>(); //Object::New();
         obj->Set(NanNew("sendrate"), NanNew(1));
         obj->Set(NanNew("rtt"), NanNew(1));
         obj->Set(NanNew("cwnd"), NanNew(1));
         obj->Set(NanNew("pktsendperiod"), NanNew(1));
         obj->Set(NanNew("recvack"), NanNew(1));
         obj->Set(NanNew("recvnack"), NanNew(1));


       Handle<Value> argv[2] = {
                      NanNew("metrics"), // event name
                      obj
       };

      NanMakeCallback(args.This(), "emit", 2, argv);
      NanReturnUndefined();
   }

}
