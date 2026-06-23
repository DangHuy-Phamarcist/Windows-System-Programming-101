#include <windows.h>
#include <stdio.h>
#include <VersionHelpers.h>
#include <tchar.h>

int systemInfo();
int computerName();
int windowsDirectory();
int queryPerformanceCounter();
int productInfo();
int computerObject();

int main() {
	systemInfo();
	computerName();
	windowsDirectory();
	queryPerformanceCounter();
	productInfo();
	computerObject();
	return 0;
}
int systemInfo() {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	printf("Processor Architecture: %d\n", si.wProcessorArchitecture);
	printf("Number of Processors: %d\n", si.dwNumberOfProcessors);
	return 0;
}

int computerName() {
	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
	if (GetComputerName(computerName, &size)) {
		printf("Computer Name: %ws\n", computerName);
	}
	else {
		printf("Failed to get computer name. Error code: %d\n", GetLastError());
	}
	return 0;
}

int windowsDirectory() {
	TCHAR windowsDir[MAX_PATH];
	UINT result = GetWindowsDirectory(windowsDir, MAX_PATH);
	if (result > 0 && result < MAX_PATH) {
		printf("Windows Directory: %ws\n", windowsDir);
	}
	else {
		printf("Failed to get Windows directory. Error code: %d\n", GetLastError());
	}
	return 0;
}

int queryPerformanceCounter() {
	LARGE_INTEGER counter;
	if (QueryPerformanceCounter(&counter)) {
		printf("Performance Counter: %lld\n", counter.QuadPart);
	}
	else {
		printf("Failed to query performance counter. Error code: %d\n", GetLastError());
	}
	return 0;
}

int productInfo() {
	OSVERSIONINFOEX osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
		printf("Operating System: Windows %d.%d (Build %d)\n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
	}
	else {
		printf("Failed to get OS version. Error code: %d\n", GetLastError());
	}
	return 0;
}

int computerObject() {
	COMPUTER_NAME_FORMAT format = ComputerNamePhysicalDnsHostname;
	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
	if (GetComputerNameEx(format, computerName, &size)) {
		printf("Computer Name (DNS Hostname): %ws\n", computerName);
	}
	else {
		printf("Failed to get computer name. Error code: %d\n", GetLastError());
	}
	return 0;
}
