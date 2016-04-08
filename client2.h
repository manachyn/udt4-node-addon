#include <node.h>
#include <nan.h>

namespace udt4 {
  class Client : public node::ObjectWrap {
    public:
      static void Init(v8::Handle<v8::Object> exports);
      Client ();
      ~Client ();
    private:
      static NAN_METHOD(New);
      static NAN_METHOD(FireMetrics);
      static NAN_METHOD(Connect);
      static NAN_METHOD(Write);
      static NAN_METHOD(End);
      static v8::Persistent<v8::Function> constructor;
  }; 
}
