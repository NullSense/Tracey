# [C++] A 3d Ray Tracer

# Final image
![6](http://puu.sh/nscjb/504d913f3e.png)

# Ray tracing introduction (with screenshots)

Ray tracing is a powerful 3D image-rendering technique that simulates the interaction of light with 3D objects at each intersection point within the environment, when a ray intersects with an object. the intensity and color of the intersection point are assigned to the pixel.

It currently supports diffuse shading, shadows, phong lighting/specular lighting and reflections. The currently supported objects are spheres and planes.

## Diffuse lighting
Diffuse lighting is determined by computing the intensity of the light at a point on the sphere.
If the angle is close to the normal at that point then the intensity will be increased.
The intensity determines how much of the object's color to contribute.

![1](http://puu.sh/nsg0S/b137d04ce9.png)

## Shadows
Shadows are incorporated into lighting.
To determine if a light source should contribute to the lighting at an intersection point a shadow ray is cast from the intersection point to the light source.
If there is an intersection before the light source then this point is in the shadow of that light source.

![2](http://puu.sh/nsg9E/535832d82b.png)

## Specular lighting / [Phong illumination](https://en.wikipedia.org/wiki/Phong_reflection_model)
Specular reflection is due to the shininess of a surface. Unlike diffuse
reflection, it is highly dependent upon the position of the viewer and the iight source
at each point on the specular surface. In [Phong's model](https://en.wikipedia.org/wiki/Phong_reflection_model), specular reflection is
scattered about the mirror direction when a surface is not mirror We but still shiny.

In this model the intensity of the reflection is proportional to the cosine
(raised to some power) of the angle between the mirror direction and viewer direction.

![3](http://puu.sh/nsgnF/ec2002f125.png)

## Reflections
Reflections are performed by casting rays originating from the intersection point directed along the reflection vector.
A portion of the reflected ray's color will be contributed to the original intersection point based on how reflective the surface is.
Fortunately this is fairly easy given the a recursive approach for casting rays.

![4](https://puu.sh/nsgz9/6c11a9cc54.png)

![5](https://puu.sh/nsgHN/24d87e5150.png)