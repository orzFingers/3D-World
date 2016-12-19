#ifndef D3_WORLD_H
#define D3_WORLD_H

class D3body{
public:
    D3body(){
        x=y=z=yRot=xRot=0;
        //xRot = RAD_90/1.0;
    }
    D3body(double _x, double _y, double _z): x(_x), y(_y), z(_z), yRot(0){
    }

    double x, y, z;
    double yRot;
    double xRot;
};


const int MAX_D3_BODIES = 10000;

class D3_World{
public:
    D3_World(): numBodies(0), CameraSpeed(0.01) {
        addBody(0,0,1.0);
        DebugAddBodiesCircle(0,0,1,90);
        DebugAddBodiesCircle(0,0,0.4,140);
        DebugAddBodiesCircle(2,2,0.4,140);
        DebugAddBodiesCircle(3,2.5,0.6,180);
        DebugAddBodiesCircle(1,1,0.3,100);

        //DebugAddBodiesCube(-3,-4,20);
    }
    void draw(){
        for(int i=0; i<numBodies; i++){
            D3body* myBody = bodies[i];
            int x = midX + getAngleXZ(myBody)/FOV_X * midX;
            int y = midY + getAngleYZ(myBody)/FOV_Y * midY;

            double size = getSize(myBody);

            al_draw_scaled_bitmap(IMG_Data_Obj[NO_IMG].image, 0, 0,
                           IMG_Data_Obj[NO_IMG].width, IMG_Data_Obj[NO_IMG].height,
                           x,y,
                           IMG_Data_Obj[NO_IMG].width*size, IMG_Data_Obj[NO_IMG].height*size,
                           0);
        }
    }
    void update(){
    }
    D3body* addBody(double x, double y, double z){
        bodies[numBodies++] = new D3body(x,y,z);
    }

    void moveCameraLeft(){
        camera.x += sin(camera.yRot-RAD_90)*CameraSpeed;
        camera.z += cos(camera.yRot-RAD_90)*CameraSpeed;
    }
    void moveCameraRight(){
        camera.x += sin(camera.yRot+RAD_90)*CameraSpeed;
        camera.z += cos(camera.yRot+RAD_90)*CameraSpeed;
    }
    void moveCameraForward(){
        camera.x += sin(camera.yRot)*CameraSpeed;
        camera.z += cos(camera.yRot)*CameraSpeed;
    }
    void moveCameraBackward(){
        camera.x -= sin(camera.yRot)*CameraSpeed;
        camera.z -= cos(camera.yRot)*CameraSpeed;
    }
    void moveCameraUp(){
        camera.y -= CameraSpeed;
    }
    void moveCameraDown(){
        camera.y += CameraSpeed;
    }
    void rotateCameraLeft(){
        camera.yRot -= CameraSpeed*4.0;
    }
    void rotateCameraRight(){
        camera.yRot += CameraSpeed*4.0;
    }

    void moveCamera(double throttle, double strafe){
        camera.x -= sin(camera.yRot)*CameraSpeed*throttle*2.0;
        camera.z -= cos(camera.yRot)*CameraSpeed*throttle*2.0;

        camera.x -= sin(camera.yRot-RAD_90)*CameraSpeed*strafe*2.0;
        camera.z -= cos(camera.yRot-RAD_90)*CameraSpeed*strafe*2.0;
    }
    void rotateCamera(float amount){
        camera.yRot += amount*CameraSpeed*4.0;
    }
    void raiseCamera(float amount){
        camera.y += amount*CameraSpeed*2.0;
    }

    D3body camera;

private:
    double CameraSpeed;
    D3body* bodies[MAX_D3_BODIES];
    int numBodies;

    void DebugAddBodiesCircle(double x, double z, double radius, double amount){
        for(int i=0; i<amount; i++){
           addBody(x+ radius * cos( RAD_360*(i/amount) ),(rand()%5)/10.0f, z+ radius * sin( RAD_360*(i/amount) )  );
        }
    }
    void DebugAddBodiesCube(double x, double z, double size){
        double spacing = 1.0;
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                for(int k=0; k<size; k++){
                    addBody(x+i/spacing, k/spacing, z+j/spacing);
                }
            }
        }
    }

    double getAngleXZ(D3body* myBody){
        double angle = fmod( atan2(myBody->x - camera.x, myBody->z - camera.z) - camera.yRot, RAD_360);
        if(angle < 0)
            angle += RAD_360;
        if(angle > RAD_180)
            angle -= RAD_360;
        return angle;
    }
    double getAngleYZ(D3body* myBody){
        //double angle = fmod( atan2(myBody->y - camera.y, myBody->z - camera.z), RAD_360 );
        double angle = fmod( atan2(myBody->y - camera.y, getDistanceXZ(myBody)) - camera.xRot, RAD_360 );
        if(angle < 0)
            angle += RAD_360;
        if(angle > RAD_180)
            angle -= RAD_360;

        if(angle > RAD_90)
            angle = RAD_90 - (angle-RAD_90);
        else if(angle < - RAD_90)
            angle = -RAD_90 - (angle+RAD_90);

        return angle;
    }
    double getSize(D3body* myBody){// needs to be 3D coordinate to be accurate.
        double deltaX = myBody->x - camera.x;
        double deltaZ = myBody->z - camera.z;
        double distance = sqrt(deltaX*deltaX + deltaZ*deltaZ);
        return 1.0 / pow(2,distance);
    }
    double getDistanceXZ(D3body* myBody){
        double deltaX = myBody->x - camera.x;
        double deltaZ = myBody->z - camera.z;
        return sqrt(deltaX*deltaX + deltaZ*deltaZ);
    }

};
D3_World *my3DWorld;


#endif
