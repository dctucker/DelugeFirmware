#include "hid/button.h"

using namespace hid::button;

#define STRINGIFY(s) #s
#define ITOA(i) STRINGIFY(i)
#define WREN_BUTTON(name, index)                                                                                       \
	"\nstatic " #name " { "                                                                                            \
	"__buttons[" #index "]"                                                                                            \
	" }"

/*
// clang-format off
const char* buttonsSource =
	"foreign "
	"class Button {"
	"\n  construct new(index) {}"
	"\n  foreign index"
	"\n}"
	"\nclass Buttons {"
	"\n  static setup(known) {"
	"\n    __buttons = {}"
	"\n    for (b in known.bytes) {"
	"\n      __buttons[b] = Button.new(b)"
	"\n    }"
	"\n  }"
	WREN_BUTTON(affectEntire, AFFECT_ENTIRE)
	WREN_BUTTON(song, SESSION_VIEW)
	WREN_BUTTON(clip, CLIP_VIEW)
	WREN_BUTTON(synth, SYNTH)
	WREN_BUTTON(kit, KIT)
	WREN_BUTTON(midi, MIDI)
	WREN_BUTTON(cv, CV)
	WREN_BUTTON(keyboard, KEYBOARD)
	WREN_BUTTON(scale, SCALE)
	WREN_BUTTON(crossScreen, CROSS_SCREEN_EDIT)
	WREN_BUTTON(back, BACK)
	WREN_BUTTON(load, LOAD)
	WREN_BUTTON(save, SAVE)
	WREN_BUTTON(learn, LEARN)
	WREN_BUTTON(tapTempo, TAP_TEMPO)
	WREN_BUTTON(syncScaling, SYNC_SCALING)
	WREN_BUTTON(triplets, TRIPLETS)
	WREN_BUTTON(play, PLAY)
	WREN_BUTTON(record, RECORD)
	WREN_BUTTON(shift, SHIFT)
	"\n}"
	"\n";
// clang-format on
*/
