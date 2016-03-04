# Tracey - A 3d Ray Tracer written in C++

# Final image
![6](http://puu.sh/nscjb/504d913f3e.png)

This implementation currently supports diffuse shading, shadows, phong lighting/specular lighting and reflections. The currently supported objects are spheres and planes.

# Ray tracing introduction (with screenshots)
Ray tracing is a 3d rendering technique that attemps to generate photorealistic images by tracing rays that are shot from every pixel of the image and applying mathematical and physical concepts to accomplish techniques described below.

## Diffuse lighting
Diffuse shading applies a shadow on an object by getting the cosine angle of the closest object's normal and light direction giving the object a matte effect.
The lower the angle of the light direction to the object's normal, the lighter that point of the object.


![1](http://puu.sh/nsg0S/b137d04ce9.png)

## Shadows
To check if a particular point in the image is part of a shadow, a ray is traced from that point to the light source.
If the ray hits some object along the way, that point is a part of a shadow.

![2](http://puu.sh/nsg9E/535832d82b.png)

## Specular lighting / [Phong illumination](https://en.wikipedia.org/wiki/Phong_reflection_model)
Specular reflection can be observed when a light is being shone on a shiny object and we can see a specular highlight of the light source and it's position is connected to the position of the viewing angle.
In this implementation, I am using [Phong's model](https://en.wikipedia.org/wiki/Phong_reflection_model) to apply this effect.
In this model the intensity of the reflection is proportional to the cosine
(raised to some power) of the angle between the reflection direction and viewer direction.

![3](http://puu.sh/nsgnF/ec2002f125.png)

## Reflections
Reflections are implemented by casting rays from the intersection point of an object directed along the reflection vector.
This method is used recursively to add realism by allowing for multiple reflections in the scene.

![4](https://puu.sh/nsgz9/6c11a9cc54.png)

![5](https://puu.sh/nsgHN/24d87e5150.png)