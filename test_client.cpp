
#define LOG_TAG "helloserver"

/*参考：frameworks\av\mediaserver\Main_mediaserver.cpp*/

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>


#include "IHelloService.h"



using namespace android;

/**
  * ./test_client hello
  *  ./test_client hello some
  */

int main(int argc, char **argv)
{
	int cnt = 0;
	if(argc < 2) {
		 ALOGI("Usage:\n");
		 ALOGI("%s <hello|goodbye>\n",argv[0]);
		 ALOGI("%s <hello|goodbye> <name>\n",argv[0]);
		 return -1;
	}

	/*getservice*/

	sp<ProcessState> proc(ProcessState::self());
	/*获得BpServiceManager*/
    sp<IServiceManager> sm = defaultServiceManager();

	sp<IBinder> binder
		= sm->getService(String16("hello"));
	if(binder == 0)
	{
		 ALOGI("can not get hello service:\n");
		 return -1;
	}

	sp<IHelloService> service
		= interface_cast<IHelloService>(binder);

	if(argc < 3) {
		service->sayhello();
		ALOGI("call  say_hello\n");
	}
	else {
		cnt = service->sayhello_to(argv[2]);
		ALOGI("call  say_hello_to cnt:%d\n",cnt);
	}
	return 0;
}


