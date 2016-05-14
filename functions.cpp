#include "main.h"
#include "functions.h"

unsigned int loadModel(std::string path)
{
	SDL_Surface *image = IMG_Load(path.c_str());

    SDL_SetAlpha(image, 0, 0);

    unsigned object(0);
    glGenTextures(1, &object);
    glBindTexture(GL_TEXTURE_2D, object);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    SDL_FreeSurface(image);

    return object;
}

unsigned int loadModel(std::string path, SDL_Rect imageRect)
{
    SDL_Surface *image = IMG_Load(path.c_str());
    SDL_DisplayFormatAlpha(image);
    SDL_Surface *tempImage;   // Tempoary surface
    tempImage = SDL_CreateRGBSurface(0, imageRect.w, imageRect.h,image->format->BitsPerPixel, image->format->Rmask, image->format->Gmask, image->format->Bmask, image->format->Amask);  // Make empty surface
    SDL_SetAlpha(image, 0, 0);

    SDL_Rect tempRect;  // Tempoary rectangle for dest information
    tempRect.x = 0;
    tempRect.y = 0;
    tempRect.w = imageRect.w;
    tempRect.h = imageRect.h;

    SDL_BlitSurface(image, &imageRect, tempImage, &tempRect);   // Copy image

    unsigned object(0);
    glGenTextures(1, &object);
    glBindTexture(GL_TEXTURE_2D, object);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage->w, tempImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage->pixels);

    //SDL_FreeSurface(image); // Free surface
    SDL_FreeSurface(tempImage); // Free tempImage surface

    // Return texture
    return object;
}

int randnum(int max)
{
    //srand(time(NULL));
    return rand() % max + 1;
}
