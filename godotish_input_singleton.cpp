// Gototish Input Singleton Demo
// compile: g++ foo.cpp -lSDL3
//
// This program saves relevant input state in an Input singleton class.
// press a to show a message box on screen

// Ways to store and access input state:
// Singleton              <--- you are here
// - guaranteed unique
// - global only if desired
// - can be subclassed
// Dependency injection
// - best for decoupling
// - good for testing
// Service locator
// - easily swap services
// - good for testing
// Namespace with free functions
// - simplicity

// Singleton is accessed when needed like so:
// auto& input_state = Input::get_singleton();
// auto& is critical, obviously
//
// Pros:
// - guaranteed unique
//
// Cons:
// - are often made globabally accessible
// - encourages coupling
// - singleton can't be easily mocked for testing
// - may have concurrency issues

// Caveats:
// - careful with lazy initialization

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_scancode.h>

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define SDL_WINDOW_WIDTH 720
#define SDL_WINDOW_HEIGHT 480

struct KeyboardAction {
  SDL_EventType event_type;
  SDL_Scancode scancode;
  std::string name;
  bool pressed;
};

class Input {
public:
  static Input &get_singleton() {
    static Input instance;
    return instance;
  }

  // call this at start of event function
  void reset() {

    for (auto &[k, v] : m_keyboard_actions) {
      v.pressed = false;
    }
  }

  // call this in event loop switch statement
  void update(SDL_Event *event) {
    // invariant - SDL_Event is a KeyboardEvent

    try {
      auto &action_name = m_event_to_action_map.at(event->key.scancode);
      auto &action = m_keyboard_actions[action_name];
      action.pressed = true;
      // SDL_Log("event found: %i, %s, %i", event->type, action.name.c_str(),
      // action.scancode);
    } catch (std::out_of_range) {
      // SDL_Log("no event found: %i", event->type);
      return;
    }
  }

  bool is_action_pressed(const std::string &name) {
    return m_keyboard_actions[name].pressed;
  }

  void add_action(SDL_EventType event_type, SDL_Scancode scancode,
                  const std::string &name) {
    KeyboardAction action{event_type, scancode, name};
    m_keyboard_actions[name] = action;
    m_event_to_action_map[scancode] = name;
    // SDL_Log("adding action: ");
    for (const auto &pair : m_keyboard_actions) {
      std::cerr << pair.first << ": " << pair.second.event_type << " "
                << pair.second.scancode << std::endl;
    }
  }

private:
  Input() {}
  Input(const Input &) = delete;            // Block copy construction
  Input &operator=(const Input &) = delete; // Block copy assignment
  std::unordered_map<std::string, KeyboardAction> m_keyboard_actions;
  std::unordered_map<SDL_Scancode, std::string> m_event_to_action_map;
  // need map of event_type to string - event type is int
};

struct MessageBox;
struct Context {
  MessageBox *message_box;
};

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Context ctx;
  Uint64 last_step;
} AppState;

struct MessageBox {
  std::string title = "TITLE";
  std::string message = "MESSAGE";
  Input &input_state;
  bool show = false;
  MessageBox() : input_state{Input::get_singleton()} {}

  void update() {
    if (input_state.is_action_pressed("show message"))
      show = true;
  }
  void draw(AppState *as) {
    if (show)
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(),
                               message.c_str(), as->window);
    show = false;
  }
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  auto &input_state = Input::get_singleton();
  input_state.add_action(SDL_EVENT_KEY_DOWN, SDL_SCANCODE_A, "show message");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
  if (!as) {
    return SDL_APP_FAILURE;
  }

  *appstate = as;
  as->ctx.message_box = new MessageBox;

  if (!SDL_CreateWindowAndRenderer("Input Singleton Demo", SDL_WINDOW_WIDTH,
                                   SDL_WINDOW_HEIGHT, 0, &as->window,
                                   &as->renderer)) {
    return SDL_APP_FAILURE;
  }

  as->last_step = SDL_GetTicks();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  SDL_Delay(100);

  AppState *as = (AppState *)appstate;
  Context *ctx = &as->ctx;
  ctx->message_box->update();
  ctx->message_box->draw(as);

  SDL_SetRenderDrawColor(as->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderPresent(as->renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  auto &input_state = Input::get_singleton();
  Context *ctx = &((AppState *)appstate)->ctx;
  input_state.reset();

  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    SDL_Log("AppEvent scancode %i", event->key.scancode);
    input_state.update(event);
  default:
    break;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (appstate != NULL) {
    AppState *as = (AppState *)appstate;
    SDL_DestroyRenderer(as->renderer);
    SDL_DestroyWindow(as->window);
    SDL_free(as);
  }
}
