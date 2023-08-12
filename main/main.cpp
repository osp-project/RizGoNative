#include <stdio.h>
#include <wifitool.cpp>
#include <httpserver.cpp>
#include <sysmemtool.h>
#include <sysidtool.h>
#include <iostream>
#include <sstream>

extern "C" {
	void app_main(void);
}

void app_main(void)
{
	printf("RizGoNative is running now\n");
	print_mem_info();
	std::string deviceidstr = std::to_string(get_device_id());
	std::cout << "获取到的device id: " << deviceidstr << std::endl;
	std::string normal_wifi_ssid_header = "RizGoNativeAP_";
	std::stringstream stitchingss;
	stitchingss << normal_wifi_ssid_header << deviceidstr;
	std::string final_ssid = stitchingss.str();
	bool apret = createap(final_ssid.c_str(),"",1,4);//默认无密码，1信道，4最大连接，SSID由deivceid拼成
	if(apret){
		print_mem_info();
		httpd_handle_t server = start_webserver();
		print_mem_info();
	}
	else{
		printf("WiFi AP创建失败，请检查参数合法性\n");
	}
}