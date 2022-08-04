#include "stdafx.h"
// dear imgui: Platform Binding for GLUT/FreeGLUT
// This needs to be used along with a Renderer (e.g. OpenGL2)

// !!! GLUT/FreeGLUT IS OBSOLETE SOFTWARE. Using GLUT is not recommended unless you really miss the 90's. !!!
// !!! If someone or something is teaching you GLUT in 2019, you are being abused. Please show some resistance. !!!
// !!! Nowadays, prefer using GLFW or SDL instead!

// Issues:
//  [ ] Platform: GLUT is unable to distinguish e.g. Backspace from CTRL+H or TAB from CTRL+I
//  [ ] Platform: Missing mouse cursor shape/visibility support.
//  [ ] Platform: Missing clipboard support (not supported by Glut).
//  [ ] Platform: Missing gamepad support.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

// CHANGELOG
// (minor and older changes stripped away, please see git history for details)
//  2019-04-03: Misc: Renamed imgui_impl_freeglut.cpp/.h to imgui_impl_glut.cpp/.h.
//  2019-03-25: Misc: Made io.DeltaTime always above zero.
//  2018-11-30: Misc: Setting up io.BackendPlatformName so it can be displayed in the About Window.
//  2018-03-22: Added GLUT Platform binding.

#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glut.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed (stb stuff)
#endif

static int g_Time = 0;          // Current time, in milliseconds

#include "EgForm.h"

bool ImGui_ImplGLUT_Init()
{
	ImGuiIO& io = ImGui::GetIO();
	io.BackendPlatformName = "imgui_impl_glut";

	g_Time = 0;

	// Glut has 1 function for characters and one for "special keys". We map the characters in the 0..255 range and the keys above.
	io.KeyMap[ImGuiKey_Tab] = '\t'; // == 9 == CTRL+I
	io.KeyMap[ImGuiKey_LeftArrow] = 256 + GLUT_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = 256 + GLUT_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = 256 + GLUT_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = 256 + GLUT_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = 256 + GLUT_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = 256 + GLUT_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = 256 + GLUT_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = 256 + GLUT_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = 256 + GLUT_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = 127;
	io.KeyMap[ImGuiKey_Backspace] = 8;  // == CTRL+H
	io.KeyMap[ImGuiKey_Space] = ' ';
	io.KeyMap[ImGuiKey_Enter] = 13; // == CTRL+M
	io.KeyMap[ImGuiKey_Escape] = 27;
	io.KeyMap[ImGuiKey_KeyPadEnter] = 13; // == CTRL+M
	io.KeyMap[ImGuiKey_A] = 'A';
	io.KeyMap[ImGuiKey_C] = 'C';
	io.KeyMap[ImGuiKey_V] = 'V';
	io.KeyMap[ImGuiKey_X] = 'X';
	io.KeyMap[ImGuiKey_Y] = 'Y';
	io.KeyMap[ImGuiKey_Z] = 'Z';

	return true;
}

void ImGui_ImplGLUT_Shutdown()
{
}

void ImGui_ImplGLUT_NewFrame()
{
	// Setup time step
	ImGuiIO& io = ImGui::GetIO();
	int current_time = glutGet(GLUT_ELAPSED_TIME);
	int delta_time_ms = (current_time - g_Time);
	if (delta_time_ms <= 0)
		delta_time_ms = 1;
	io.DeltaTime = delta_time_ms / 1000.0f;
	g_Time = current_time;

	// Start the frame
	ImGui::NewFrame();
}

