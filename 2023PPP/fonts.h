#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include <SDL.h>
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
//
// This would need to be rewritten using ap.io in order to work
//
//
// Load Fonts
// - If no fonts are loaded, dear imgui will use the default font. You can
// also load multiple fonts and use ImGui::PushFont()/PopFont() to select
// them.
// - AddFontFromFileTTF() will return the ImFont* so you can store it if you
// need to select the font among multiple.
// - If the file cannot be loaded, the function will return a nullptr. Please
// handle those errors in your application (e.g. use an assertion, or display
// an error and quit).
// - The fonts will be rasterized at a given size (w/ oversampling) and stored
// into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which
// ImGui_ImplXXXX_NewFrame below will call.
// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype
// for higher quality font rendering.
// - Read 'docs/FONTS.md' for more instructions and details.
// - Remember that in C/C++ if you want to include a backslash \ in a string
// literal you need to write a double backslash \\ !
// - Our Emscripten build process allows embedding fonts to be accessible at
// runtime from the "fonts/" folder. See Makefile.emscripten for details.
// io.Fonts->AddFontDefault();
// io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
// io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
// io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
// io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
// ImFont* font =
// io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
// nullptr, io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != nullptr);
