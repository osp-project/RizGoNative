#include <stdio.h>
#include <wifitool.cpp>
#include <httpserver.cpp>
#include <sysmemtool.h>

extern "C" {
	void app_main(void);
}

void app_main(void)
{
	printf("RizGoNative is running now\n");
	print_mem_info();
	bool apret = createap("RizGoNativeAPaaaaaaaa","1234567890",1,4);
	if(apret){
		print_mem_info();
		httpd_handle_t server = start_webserver();
		print_mem_info();
	}
	else{
		printf("WiFi AP创建失败，请检查参数合法性\n");
	}
}