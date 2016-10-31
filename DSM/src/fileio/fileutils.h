#pragma once
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include <string>
class FileUtils
{
public:
	static std::string read_file(const char* filepath)
	{
#ifdef __APPLE__
		CFURLRef appUrlRef;
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFStringCreateWithCString(NULL,filepath,kCFStringEncodingMacRoman),NULL,NULL);
	    CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
	    const char* pathString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else
	    const char* pathString = filepath;
#endif
        FILE* file = fopen(pathString, "r");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);
#ifdef __APPLE__
	    CFRelease(appUrlRef);
	    CFRelease(filePathRef);
#endif
		std::string result(data);
		delete[] data;
		return result;
	}
};
