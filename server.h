#include <node.h>
#include <nan.h>
#include <uv.h>

namespace udt4 {
  class Server : public node::ObjectWrap {
    public:
	  static void Init(v8::Handle<v8::Object> exports);
	  static NAN_METHOD(FireEvent) ;
    Server ();
    ~Server ();
	   
	private:
    static NAN_METHOD(New);
	  static NAN_METHOD(Close);
	  static NAN_METHOD(Listen);
	  static NAN_METHOD(CallEmit); 
	  /*static NAN_METHOD(GetSockName);
      static NAN_METHOD(GetPeerName);
      static NAN_METHOD(SetNoDelay);
      static NAN_METHOD(SetKeepAlive);
      static NAN_METHOD(Bind);
      static NAN_METHOD(Bind6);
      static NAN_METHOD(Connect);
      static NAN_METHOD(Connect6);
      static NAN_METHOD(Open);*/
  }; 
}
