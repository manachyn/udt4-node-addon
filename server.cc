#include <v8.h>
#include <node.h>
#include <nan.h>

#include "server.h"
#include "serverasync.h"

using namespace v8;
using namespace node;

namespace udt4 {

static Persistent<Function> server_constructor;
static Persistent<Object> persistent_instance;
static NanCallback* onDataCallback; 
static ServerAsync* server; 

  Server::Server () {};
  Server::~Server () {};

  void Server::Init(Handle<Object> exports) {
    NanScope();

    Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
    tpl->SetClassName(NanNew("Server"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    NODE_SET_PROTOTYPE_METHOD(tpl, "listen", Listen);
    NODE_SET_PROTOTYPE_METHOD(tpl, "close", Close);
    NanAssignPersistent(server_constructor, tpl->GetFunction());
    exports->Set(NanNew<String>("Server"), tpl->GetFunction());
   }

  NAN_METHOD(Server::FireEvent) {
      NanScope();
      int len=Buffer::Length(args[0]->ToObject());
      char *buf=Buffer::Data(args[0]->ToObject());

          Handle<Value> argv[2] = {
                      NanNew("data"), // event name
                      NanNewBufferHandle(buf, len)
       };
      
      NanMakeCallback(args.This(), "emit", 2, argv);
      NanReturnUndefined();
  }

  NAN_METHOD(Server::Listen) {
     NanEscapableScope();
     
     int port = args[0].As<Number>()->IntegerValue();
         server = new ServerAsync(args.This(), onDataCallback, port);
    
     NanAsyncQueueWorker(server);

     return NanEscapeScope(persistent_instance);
   }

  NAN_METHOD(Server::CallEmit) {
     
     NanScope();
     Handle<Value> argv[1] = {
        NanNew("close"), // event name
     };

     NanMakeCallback(args.This(), "emit", 1, argv);
     NanReturnUndefined();
  }
  
  NAN_METHOD(Server::Close) {
        NanScope();
        server -> Close();
        // cout << "closed" << endl;
        
        NanReturnUndefined();
   }

  NAN_METHOD(Server::New) {
    NanScope();
    if(args.IsConstructCall()) {
      Server* obj = new Server();
      obj->Wrap(args.This());
      NanReturnValue(args.This());
    }
    else {
      Local<Function> cons = NanNew<Function>(server_constructor);
      NanReturnValue(cons->NewInstance());
    }
    
}

}//EONS