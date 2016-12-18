# Tracey - A 3d Ray Tracer written in C++

# Final images
![5](http://i.imgur.com/6NwrWGT.png)
![6](http://i.imgur.com/fbGFmnr.png)
![7](http://puu.sh/nscjb/504d913f3e.png)

This implementation currently supports diffuse shading, shadows, phong lighting/specular lighting and reflections. The currently supported objects are spheres and planes.

# Ray tracing introduction (with screenshots)
Ray tracing is a 3d rendering technique that attemps to generate photorealistic images by tracing rays that are shot from every pixel of the image and applying mathematical and physical concepts to accomplish techniques described below.

## Diffuse lighting
Diffuse shading applies a shadow on an object by getting the cosine angle of the closest object's normal and light direction, giving the object a matte effect.
The lower the angle of the light direction to the object's normal, the brighter that point of the object.

![1](http://puu.sh/nsg0S/b137d04ce9.png)

## Shadows
To check if a particular point of the image is a part of a shadow, a ray is traced from an intersection point to the light source.
If the object intersection to light position ray hits some object along the way, the starting point of the ray is a part of a shadow.

![2](http://puu.sh/nsg9E/535832d82b.png)

## Specular lighting / [Phong illumination](https://en.wikipedia.org/wiki/Phong_reflection_model)
Specular reflection can be observed when a light is being shone on an object with shinyness value.
The result of that is a specular highlight on the surface of the object.
The light source's position and the viewing angle contributes to the specular highlight's position.

The phong reflection model has been devloped by Bui Tuong Phong [Phong's model](https://en.wikipedia.org/wiki/Phong_reflection_model), which is used in this project.
In this implementation the intensity of the reflection is proportional to the cosine (raised to some power) of the angle between the reflection direction and viewer direction.

![3](http://puu.sh/nsgnF/ec2002f125.png)

## Reflections
Reflections are implemented by casting rays from the light source to an object and then by casting a reflection ray from intersection point of the object, directed along the reflection vector.
This method is used recursively to add realism by allowing for multiple reflections in the scene.

![4](https://puu.sh/nsgz9/6c11a9cc54.png)

![5](https://puu.sh/nsgHN/24d87e5150.png)