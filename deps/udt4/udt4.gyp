{
   "targets": [
       {
         "target_name": "udt4core",
	 "cflags!": [ "-fno-exceptions" ],
	 "cflags_cc!": [ "-fno-exceptions" ],
	 "type": "static_library",
	 "standalone_static_library": 1,
	 "conditions": [
      ["OS == 'win'", {
         "defines": [
         "_HAS_EXCEPTIONS=0",
		 "UDT_EXPORTS"
         ]
         , "msvs_settings": {
            "VCCLCompilerTool": {
               "RuntimeTypeInfo": "false"
               , "EnableFunctionLevelLinking": "true"
               , "ExceptionHandling": "2"
               , "DisableSpecificWarnings": [ "4355", "4530" ,"4267", "4244", "4506", "4297" ]
            }
         }
      }]
      ],
         "sources": [   "api.cpp",     
			"cache.cpp", 
			"channel.cpp",  
			"core.cpp",   
			"list.cpp",  
			"md5.h",       
			"queue.h",     
			"window.h",
			"api.h",       
			"cache.h",    
			"channel.h",    
			"core.h",     
			"list.h",    
			"packet.cpp",  
			"buffer.cpp",  
			"ccc.cpp",    
			"common.cpp",   
			"epoll.cpp",  
			"packet.h",    
			"udt.h",
			"buffer.h",    
			"ccc.h",      
			"common.h",     
			"epoll.h",    
			"md5.cpp",   
			"queue.cpp",   
			"window.cpp" 
       ],
         "include_dirs": []
       }
    ]
}
