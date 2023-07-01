#include "hid/display/numeric_driver.h"
#include "storage/storage_manager.h"
#include "memory/general_memory_allocator.h"
#include "memory/wren_heap.h"
#include "wrenimpl.h"
#include <string>
#include "string.h"

static char scriptBuffer[SCRIPT_BUFFER_SIZE];

void Wren::configure() {
	wren_heap_init();

	wrenpp::VM::writeFn = [](const char* text) -> void {
		bool empty = true;
		for (size_t i = 0; text[i] != '\0'; i++) {
			if (!std::isspace(static_cast<unsigned char>(text[i]))) {
				empty = false;
			}
		}
		if (empty) return;

#if HAVE_OLED
		numericDriver.displayPopup(text);
#else
		if (strlen(text) <= NUMERIC_DISPLAY_LENGTH) {
			numericDriver.setText(text, true);
		}
		else {
			numericDriver.setScrollingText(text);
		}
#endif
	};

	wrenpp::VM::errorFn = [](WrenErrorType type, const char* module_name, int line, const char* message) -> void {
		//const char* typeStr = errorTypeToString(type);
		if (module_name) {
			//std::cout << typeStr << " in " << module_name << ":" << line << "> " << message << std::endl;
		} else {
			//std::cout << typeStr << "> " << message << std::endl;
		}
	};

	wrenpp::VM::loadModuleFn = [](const char* name) -> char* {
		return Wren::getSourceForModule(name);
	};

	wrenpp::VM::reallocateFn = wren_heap_realloc;
	wrenpp::VM::initialHeapSize = kWrenHeapSize;
	wrenpp::VM::minHeapSize = 4096;
}

char* Wren::getSourceForModule(const char* name) {
	FIL fil;
	UINT bytesRead = 0;
	TCHAR filename[256];
	sprintf(filename, "SCRIPTS/%s.wren", name);
	if (f_open(&fil, filename, FA_READ) == FR_OK) {
		(void)f_read(&fil, &scriptBuffer, SCRIPT_BUFFER_SIZE, &bytesRead);
		f_close(&fil);
	}
	scriptBuffer[bytesRead] = '\0';

	return scriptBuffer;
}

Wren::Wren() : vm() {
	setup();
	first_run = true;
}

void Wren::tick() {
	if (first_run) {
		runInit();
		first_run = false;
	}
}

#define NL "\n"
void Wren::setup() {
	static const char* setupScript =
		NL "class TDeluge {"
		NL "  construct new() { _init = Fn.new {} }"
		NL "  init() { _init.call() }"
		NL "  onInit(fn) { _init = fn }"
		NL "}"
		NL "var Deluge = TDeluge.new()"
		NL;
	vm.executeString(setupScript);
	methods.Deluge_init = vm.method("main", "Deluge", "init");

	char* source = getSourceForModule("init");
	vm.executeString(source);
}

void Wren::runInit() {
	methods.Deluge_init();
}
