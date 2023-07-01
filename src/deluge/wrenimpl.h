#pragma once
#include "wren/Wren++.h"

#define SCRIPT_BUFFER_SIZE 1024

class Wren {
public:
	bool first_run;
	wrenpp::VM vm;

	struct {
		wrenpp::Method Deluge_init;
	} methods;

	Wren();
	void tick();
	void setup();
	void runInit();

	static void configure();

private:
	static char* getSourceForModule(const char*);
};
