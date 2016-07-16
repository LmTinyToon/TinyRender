# TinyRender
It is my attemp to create own small render (for educational purposes) on C++ lanugage. 
I am planning to implement basic algorithms of computer graphics in this project.

In current version of renderer I am using TGA format of file to produce result image.
Current version of renderer supports simple operations on TGA images (such as create image, change pixels of image, save image).
Brief specification of TGA format is located here: 

1) https://en.wikipedia.org/wiki/Truevision_TGA
2) http://www.paulbourke.net/dataformats/tga/

Initial format of loaded mesh models is simply collection of triangles.
Each model has such structure:
N - count of triangles of model
x0 y0 z0 x1 y1 z1 x2 y2 z2  - coordinates of each triangle in model

Note: Any other characters (except tabulation) are not allowed

NOTE: I am developing this project on platform Windows. 
My implementation of TinyRender is partially based on https://github.com/ssloy/tinyrenderer (I accidentally created project with the same name).
Author of that project has really good course on Russian language at https://habrahabr.ru/post/248153/.
	  
