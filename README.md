# 3DMesh
A simple OpenGL code to load obj models, with features to rotate the camera and rotate the light source.

![image](https://user-images.githubusercontent.com/39425103/206224886-c2bd9482-bac0-4c73-93c4-a7cc79a85c72.png)


## Testing Environment
* Microsoft Visual Studio 2019 Community Edition

## How to Run

The dependencies are packed in the `Dependencies/` directory, which we include the following libraries:
* [freeglut 3.0.0](https://www.transmissionzero.co.uk/software/freeglut-devel/)
* [glew 2.1.0](https://glew.sourceforge.net/index.html)


Simply open the `3DMesh.sln` file in Visual Studio to open the project.
As long as OpenGL is configured on your PC (which is usually installed along with Microsoft Visual Studio), it should run without problems.
Press `<Ctrl> + <F5>` to build without debugging.

## Description

### Camera
To rotate the camera, first change the rotation mode to camera mode by pressing `<F1>`.
Then, drag on the screen to rotate the camera.
You may zoom in and zoom out by scrolling.

![image](https://user-images.githubusercontent.com/39425103/206225707-8c5859ad-4228-4372-8a10-2e8461ac2da6.png)


### Light Source
To rotate the light source, change the rotation mode to light source mode by pressing `<F2>`.
Then, drag on the screen to rotate the light source.
You may change the distance of the light source by scrolling.

![image](https://user-images.githubusercontent.com/39425103/206225817-d44b6dae-0a77-4f3b-8e7e-d8a0586cc1c7.png)


