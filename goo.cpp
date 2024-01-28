#include <SDL.h>

int main(int argc, char *argv[]) {
  int width = 2;
  int height = 2;

  // Pixel data for a simple 2x2 texture (RGBA8888 format)
  Uint32 pixels[] = {
      0xFF0000FF, 0x00FF00FF, // Red, Green
      0x0000FFFF, 0xFFFFFFFF  // Blue, White
  };
  int pitch = width * sizeof(Uint32); // Bytes in a row of pixel data
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window =
      SDL_CreateWindow("SDL Texture Example", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Assuming you have pixel data in 'pixels' and width/height information
  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STATIC, width, height);
  SDL_UpdateTexture(texture, NULL, pixels, pitch);

  SDL_Rect destinationRect = {0, 0, width, height};

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set background color
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, texture, NULL, &destinationRect);

  // Fill a rectangle
  SDL_Rect fillRect = {100, 100, 50, 50};
  SDL_SetRenderDrawColor(renderer, 255, 0, 0,
                         255); // Set the drawing color to red
  SDL_RenderFillRect(renderer, &fillRect);

  SDL_RenderPresent(renderer);

  SDL_Delay(2000); // Pause for 2000 milliseconds (2 seconds)

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
