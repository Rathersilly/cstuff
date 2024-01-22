// Put bits of code you dont use but dont want to delete here

// unused - not sure exactly how/whether to use this since context is not part
// of imgui api (its implementation instead)
// feel free to delete
ImGuiContext *context = ImGui::GetCurrentContext();
//
//
// Before event loop, from Imgui example
// Poll and handle events (inputs, window resize, etc.)
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
// tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to
// your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
// data to your main application, or clear/overwrite your copy of the
// keyboard data. Generally you may always pass all inputs to dear imgui,
// and hide them from your application based on those two flags.
