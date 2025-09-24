/* Copyright (c) 2024 orbea
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

#ifdef HAVE_SDL3
#include <SDL3/SDL.h>
#else
#include <SDL.h>
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

int main(void) {
	int running = 1;
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;

#ifdef HAVE_SDL3
	if(!SDL_Init(SDL_INIT_VIDEO)) {
#else
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
#endif
		fprintf(stderr, "Failed to initialize SDL: %s\n",
			SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("xssd",
#ifndef HAVE_SDL3
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
#endif
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_HIDDEN
	);

#ifdef HAVE_SDL3
	renderer = SDL_CreateRenderer(window, NULL);
#else
	renderer = SDL_CreateRenderer(window, -1, 0);
#endif

	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_DisableScreenSaver();

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
#ifdef HAVE_SDL3
				case SDL_EVENT_QUIT: {
#else
				case SDL_QUIT: {
#endif
					running = 0;
					break;
				}
				default: {
					break;
				}
			}
		}
		SDL_Delay(1000);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
