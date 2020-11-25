{
   "targets": [
       {
           "target_name": "addon",
           "sources": [ "addon.cpp", "test.cpp"],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api\').include\")"
				'../node_modules/node-addon-api',
        'node_modules/node-addon-api',
        '/usr/include/node',
        '/usr/local/include/node'
			],
			'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
       }
   ]
}
