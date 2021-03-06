#pragma once
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include "../global.h"


#include <fstream>
namespace elements {
	struct Element
	{
		int Atomic_Number;
		int x;
		int y;
		std::string Symbol;
		std::string Name;
		double Atomic_Weight;
		float Melting_Point;
		float Boiling_Point;
		double Density;
		int Discovery_Year;
		double Ionization_Energy;
		int Element_Type;
		int Element_State;
		glm::vec3 Colour;
		float Covalent_Radius;
	};
	static std::vector<Element> init_elements()
	{
		std::vector<Element> ELEMENTS;
		std::ifstream element_stream;
#ifdef __APPLE__
        CFURLRef appUrlRef;
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFSTR("/src/entities/elements.txt"),NULL,NULL);
        CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
        const char* elementString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else
        const char* elementString = "src/entities/elements.txt";
#endif
        element_stream.open(elementString);

		Element Atomic;
		ELEMENTS.clear();

		while (element_stream)
		{
			element_stream >> Atomic.Atomic_Number;
			element_stream >> Atomic.x;
			element_stream >> Atomic.y;
			element_stream >> Atomic.Symbol;
			element_stream >> Atomic.Colour.r;
			element_stream >> Atomic.Colour.g;
			element_stream >> Atomic.Colour.b;
			element_stream >> Atomic.Covalent_Radius;
			element_stream >> Atomic.Name;
			element_stream >> Atomic.Atomic_Weight;
			element_stream >> Atomic.Melting_Point;
			element_stream >> Atomic.Boiling_Point;
			element_stream >> Atomic.Density;
			element_stream >> Atomic.Discovery_Year;
			element_stream >> Atomic.Ionization_Energy;
			element_stream >> Atomic.Element_Type;
			element_stream >> Atomic.Element_State;
			ELEMENTS.push_back(Atomic);
		}
#ifdef __APPLE__
        CFRelease(appUrlRef);
        CFRelease(filePathRef);
#endif
		element_stream.close();
		return ELEMENTS;
	}
	const std::vector<Element> ELEMENTS = init_elements();
}


