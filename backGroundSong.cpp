#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <unistd.h>
#include "soundLib.h"

SERVICE_STATUS servStat = {0};
SERVICE_STATUS_HANDLE statusHandle = 0;
HANDLE stopEvent = nullptr; // Creates a handle that represents the stop service event
                            // A service is a API object used to interact with Windows system resources

/*void subProc(){
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CreateProcessA(
        NULL,
        "pServTest.exe",
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}*/
void WINAPI servControlHandle(DWORD code){
    // We make sure the service is even running before pentitioning to stop it
    if(servStat.dwCurrentState == SERVICE_RUNNING){
        switch(code){
            case SERVICE_CONTROL_STOP:
            servStat.dwCurrentState = SERVICE_STOP_PENDING;

            // Updates the service status to the Windows service manager
            SetServiceStatus(statusHandle, &servStat); // handle is provided so the manager can interact and the status is provided for the manager to see full info on service

            SetEvent(stopEvent);
        }
    }
}

void WINAPI mainService(DWORD argc, LPSTR *argv){
    // Register the service with the contorl manager and get handle
    statusHandle = RegisterServiceCtrlHandler(_T("StreetsOfTrogue"), servControlHandle);

    ZeroMemory(&servStat, sizeof(servStat));
    servStat.dwServiceType = SERVICE_WIN32_OWN_PROCESS; // Not sharing with other services
    servStat.dwControlsAccepted = 0; // Usually 0 at transitionary periods: start, stop, or pause. Indicates that the process is yielding to the manager
                                     // When it reaches a stable state it may indicate to the manager that it can accept a stop command and handle it with SERVICE_ACCEPT_STOP
    servStat.dwCheckPoint = 0; // Status metric to indicate the process is still running and making progress
    servStat.dwCurrentState = SERVICE_START_PENDING; // Indicates the service is in the midst of starting
    servStat.dwWin32ExitCode = 0; // Current exit code
    servStat.dwServiceSpecificExitCode = 0; // More specific exit for additional error info

    SetServiceStatus(statusHandle, &servStat);

    stopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    /* Args:
    1. Identitfies security level (0 for default basic perms meaning handle can't be given to child restricted)
    2. Sets to manual reset. It means that the event signal will be toggled with ResetEvent allowing everything relying on the event to be synched instead of each auto resetting according to their own conditions
        the difference between this an auto is that auto resets to 0 after each thread closes, while manual remains signaled until ResetEvent() (opposite of SetEvent) is called
    3. Sets the initial state to not signaled
    4. Sets the name to anonymous (just like named vs unnamed pipes) 
    */
   // Error Case:
   if(!stopEvent){
    servStat.dwControlsAccepted = 0;
    servStat.dwCurrentState = SERVICE_STOPPED;
    servStat.dwWin32ExitCode = GetLastError(); // Gets most recent windows error code
    SetServiceStatus(statusHandle, &servStat);
   }

   servStat.dwControlsAccepted = SERVICE_ACCEPT_STOP; // Service can handle stop control codes now (it can be stopped an expected to clean itself)
   servStat.dwCurrentState = SERVICE_RUNNING;
   SetServiceStatus(statusHandle, &servStat);

   
   //subProc();
   sleep(30);
   while (true){
    laugh();
    sleep(300);
   }
   //WaitForSingleObject(stopEvent, INFINITE); // Wait an indefinite amount of time for the stop event to be signaled


   CloseHandle(stopEvent); // Deallocates resources to manage event
   servStat.dwControlsAccepted = 0;
   servStat.dwCurrentState = SERVICE_STOPPED;
   SetServiceStatus(statusHandle, &servStat);

    
}

int _tmain(int argc, TCHAR *argv[]){
    SERVICE_TABLE_ENTRY serviceTable[] = {
        {_T("TestService"),
        (LPSERVICE_MAIN_FUNCTION)mainService},
        {nullptr, nullptr}

    };
    // Adds the service to the service table:
    // {service name in correct format UNICODE or ANSI whatever is specified, cast and specify service function},
    // indicates the end of the entry

    if(!StartServiceCtrlDispatcher(serviceTable)){
        std::cerr << "Failed to start " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}