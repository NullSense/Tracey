# Tracey - A 3d Ray Tracer written in C++ (multithreaded)

# Final images
![5](http://i.imgur.com/471lxiB.png)
![6](http://i.imgur.com/7WN9yQH.png)
![7](http://i.imgur.com/J98nxZ5.png)
![8](http://i.imgur.com/5ryC4nw.png)

This implementation currently supports diffuse shading, specular reflections, shadows, reflections, blinn-phong lighting and supersampling.
The currently supported geometric primitives are spheres, planes, disks, boxes.

# Ray tracing introduction (with screenshots)
Ray tracing is a 3d rendering technique that attemps to generate photorealistic images by tracing rays that are shot from every pixel of the image and applying mathematical and physical concepts to accomplish techniques described below.

## Ambient Light
The light that gets scattered all around the scene, takes object ambient reflection parameter into consideration.
![8](http://i.imgur.com/sx3nj7D.png)

## Diffuse lighting
Diffuse shading applies a shadow on an object by getting the cosine angle of the closest object's normal and light direction, giving the object a matte effect.
The lower the angle of the light direction to the object's normal, the brighter that point of the object.

![1](http://i.imgur.com/7vzEw0m.png)

## Shadows
To check if a particular point of the image is a part of a shadow, a ray is traced from an intersection point to the light source.
If the intersection point to light position ray hits some object along the way, the intersection point is a shadow.

![2](http://i.imgur.com/xEKn7x3.png)

## Specular lighting / [Blinn-Phong illumination](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model)
Specular reflection can be observed when a light is being shone on an object with shinyness value.
The result of that is a specular highlight on the surface of the object.
The light source's position and the viewing angle contributes to the specular highlight's position.
The light source's intensity and color define it's size and color

![3](http://i.imgur.com/F1djdgd.png)

## Reflections
Reflections are implemented by casting rays from the light source to an object and then by casting a reflection ray from intersection point of the object, directed along the reflection vector.
This method is used recursively to add realism by allowing for multiple reflections in the scene.

![4](http://i.imgur.com/UnFEBU6.png)
You can see reflections in reflections in reflections and so on...
![5](http://i.imgur.com/rIMd94R.png)