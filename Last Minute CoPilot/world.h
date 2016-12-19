#ifndef WORLD_H
#define WORLD_H




Input World_Input;

void Init_World(ALLEGRO_DISPLAY *myDisplay){
    World = new World_Handler(myDisplay);
    srand(time(NULL));
}

void Update_World(){

    World->update();
    World_Input.updateInput();
}

void Draw_World(){
    World->draw();
    World_Input.draw();
    my3DWorld->draw();
}

void Destroy_World(){
    // Delete pointers, images, etc.
}

#endif
