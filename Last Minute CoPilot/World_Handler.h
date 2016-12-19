#ifndef WORLD_HANDLER_H
#define WORLD_HANDLER_H
// This class holds all Items and Residents. As well as createName() functions to create them.
// constants

class World_Handler{
public:
    World_Handler(ALLEGRO_DISPLAY *myDisplay) {
        my3DWorld = new D3_World();
    }
    void draw(){
    }
    void update(){
    }

private:

};
World_Handler* World;


#endif
