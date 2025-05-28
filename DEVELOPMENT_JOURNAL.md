May 26th 2025 @ 14:16 EST 

After struggling for days over build systems and IDE I finally have what I feel is a strong build system. It stook a lot of work and headache but I finally have a CMake system to carry we through the rest of the course.

Transferring over from Visual Studio to VSCode has been difficult but ultimately so worth it. I learned a ton about CMake and how actually it is quite easy to use. The problems in Visual Studio, in particular its lack of ability to have multiple programs in a single project folder, the hidden main.cpp, all the different settings that have to be tuned and set set became such a pain in the ass that it was ultimately worth it to navigate over to the code editor I am more happy with. 

The good news was that a lot of the ground work had been laid to actually catch me up. I didn't have to manufacture a lot of new code - just porting the build system and porting the stages of the Learn OpenGL tutorials over.

I reused the bones of the Triforce LearnOpenGL to make an interpolated rainbow triangle. I did a similar assignment in my Computer Graphics course but obviously with a lot less complexity (for now). This is only a single triangle, the cube had 6 * 2 = 12 triangles and rotated. 

I ported the triangle assignment to make a new rainbow triangle and then used the trifoce vertices to add more colors. A normal triangle has 3 points, the triforce has 6 - meaning double the colors. 

I still need to get a handle on debugging basically every stage of the graphics pipeline. If I am not learning anything in this process it is debugging. I still don't have a super solid grasp on the connection between VAO, VBO, and EBO. Maybe a YouTube video will clear it up? What is next I don't know. I guess I will go back to Learn OpenGL and do the next stage. I could also download a book and give it a read. More to follow tomorrow and the next day. 

Ultimately I would be extremely happy with some kind of solar system simulator and a click and turn feature and a sliding bar to speed or slow down time. 

The dream of a 3D Water Polo video game side project is still very much alive. We will see. 


May 27th 2025

Just managed to import the STB and GLM libraries. The plan of attack for today and tomorrow is to basically catch up to where I was before in the graphics programming class. Lets get a rainbow 3D outputted and rotating and then a 3D cube with a texture mapped to the surface of the cube. That is two separate projects and hopefully it goes smoothly.