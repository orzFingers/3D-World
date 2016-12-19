#ifndef CONSTANTS_H
#define CONSTANTS_H

const double DEGREES_TO_RADIANS = 0.0174532925;

const int Screen_W = 400;
const int Screen_H = 400;
const double midX = Screen_W/2;
const double midY = Screen_H/2;

/*
// FOV is in radians
double FOV_X = 0.78539816;//45.0;
double FOV_Y = 0.78539816;//45.0;
*/
double FOV = 70;//70;
double FOV_X = FOV/2.0 * DEGREES_TO_RADIANS;
double FOV_Y = double(Screen_H)/double(Screen_W) * FOV_X;


double RAD_360 = 6.28318531;
double RAD_180 = 3.14159265;
double RAD_90 =  1.57079633;

ALLEGRO_FONT *fontDefault = NULL;
ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(26,120,248);


int getDigit(int num, int digit){
    //if(num < pow(10,digit) ) // if num does not have that location
       //return 0;
    int step1 = num/pow(10,(digit-1)); // step1 holds the value in the ones location.
    int step2 = (step1/10)*10;
    int step3 = step1-step2;
    return step3;
}


#endif

