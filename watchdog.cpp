#include <windows.h>
#include <winsvc.h>
#include <string>

#define SVC_NAME TEXT("SimpleWatchdog")

SERVICE_STATUS gSvcStatus;
SERVICE_STATUS_HANDLE gSvcStatusHandle;
HANDLE ghSvcStopEvent = NULL;

//
// Purpose:
//      Entry point
//
// Parameters:
//      None
//
// Return value:
//      None, defaults to 0 (zero)

int wmain(int argc, TCHAR *argv[]) {

    // If command line argument is "install" than install the service
    // otherwise, SCM may start the service
    if(lstrcmpi(argv[1], TEXT("install")) == 0) {
        SvcInstall();
        return 0;
    }

    SERVICE_TABLE_ENTRY DispatchTable[] = {
        {SVC_NAME, (LPSERVICE_MAIN_FUNCTION) SvcMain},
        {NULL, NULL}
    };

    // This call returns when the service has stopped
    // The process should simply terminate when call returns
    if(!StartServiceCtrlDispatcher(DispatchTable)) {
        SvcReportEvent(TEXT("StartServiceControlDispatcher!"));
    }

    return 0;
}
