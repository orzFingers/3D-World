#ifndef INPUT_H
#define INPUT_H

//enum MOUSE_ACTIONS{ DRAW_NONE=0, DRAW_LINE=1, DRAW_RECTANGLE=2, DRAW_FILL=3 };
class ButtonState{
public:
    ButtonState(): isNew(false), current(false), previous(false){
    }
    void update(){
        if(current){
            if(!previous){
                isNew = true;
                previous = true;
            }
            else
                isNew = false;
        }
        else
            previous = false;
    }
    void press(){
        current=true;
    }
    void release(){
        current=false;
    }

    bool isNew;
    bool current;
    bool previous;
};

class MouseValues{
public:
    MouseValues(){
    }

    void update(){
        m1.update();
        m2.update();
    }

    ButtonState m1, m2;
    int x, y;
};
MouseValues m;

class Input_States{
public:
    Input_States(): Axis_X(0), Axis_Y(0){
    }
    void updateBeforeUse(){ // update buttons
        Use.update();
    }
    void updateAfterUse(){ // reset axis
        Axis_X = Axis_Y = 0;
    }

    float Axis_X;
    float Axis_Y;

    ButtonState Use;
};
Input_States gameInput;


struct Joystick{
    // axis values
    float Stick_L_x;
    float Stick_L_y;

    float Stick_R_x;
    float Stick_R_y;

    float DPad_X;
    float DPad_Y;

    bool Button_A;
    bool Button_X;
};
typedef struct Joystick Joystick;
Joystick Gamepad;


class Input{
public:
    Input(): mouseDZ(0), CameraSpeed(80){
    }
    void draw(){
    }

    void updateInput(){
        updateController();

    }

    void setCursor(int _mouseX, int _mouseY){
        m.x = _mouseX;
        m.y = _mouseY;
    }
    void setAxisChange(float x, float y){
        my3DWorld->camera.yRot += x/1000.0;
    }
    void setScroll(int _mouseDZ){
        mouseDZ += _mouseDZ;
    }
    void setMouse1(bool m1){
        m.m1.current = m1;
    }
    void setMouse2(bool m2){
        m.m2.current = m2;
    }
    void cameraUP(){
    }
    void cameraDOWN(){
    }
    void cameraLEFT(){
    }
    void cameraRIGHT(){
    }



    void updateController(){

        // Take input from controller and keyboard;
        if(Gamepad.Stick_L_x)
            gameInput.Axis_X = Gamepad.Stick_L_x;
        if(Gamepad.Stick_L_y)
            gameInput.Axis_Y = Gamepad.Stick_L_y;

        // Update gameInput beforeUse
        gameInput.updateBeforeUse();

        // ---> Use Controller Input Here
        my3DWorld->moveCamera(Gamepad.Stick_L_y, Gamepad.Stick_L_x);
        my3DWorld->rotateCamera(Gamepad.Stick_R_x);
        my3DWorld->raiseCamera(Gamepad.Stick_R_y);

        // Update gameInput afterUse
        gameInput.updateAfterUse();
    }


private:
    int mouseDZ; // Change in scroll each frame.
    const double CameraSpeed;
    double CameraOffsetX, CameraOffsetY;
};

#endif

