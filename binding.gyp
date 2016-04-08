{
   "targets": [
   {
      "target_name": "udt4",
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
               , "DisableSpecificWarnings": [ "4355", "4530" ,"4267", "4244", "4506" ]
            }
         }
      }]
      ],
      "sources": [
         "src/udt4.cc",
         "src/client.cc",
         "src/server.cc"
         ],
      "dependencies": ["<(module_root_dir)/deps/udt4/udt4.gyp:udt4core"],
      "include_dirs": [
         "<!(node -e \"require('nan')\")",
         "deps/udt4"
         
      ]
   }
   ]
}


