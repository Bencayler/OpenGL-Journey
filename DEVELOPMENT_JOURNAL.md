May 26th 2025 @ 14:16 EST 

After struggling for days over build systems and IDE I finally have what I feel is a strong build system. It stook a lot of work and headache but I finally have a CMake system to carry we through the rest of the course.

Transferring over from Visual Studio to VSCode has been difficult but ultimately so worth it. I learned a ton about CMake and how actually it is quite easy to use. The problems in Visual Studio, in particular its lack of ability to have multiple programs in a single project folder, the hidden main.cpp, all the different settings that have to be tuned and set set became such a pain in the ass that it was ultimately worth it to navigate over to the code editor I am more happy with. 

The good news was that a lot of the ground work had been laid to actually catch me up. I didn't have to manufacture a lot of new code - just porting the build system and porting the stages of the Learn OpenGL tutorials over.

I reused the bones of the Triforce LearnOpenGL to make an interpolated rainbow triangle. I did a similar assignment in my Computer Graphics course but obviously with a lot less complexity (for now). This is only a single triangle, the cube had 6 * 2 = 12 triangles and rotated. 

I ported the triangle assignment to make a new rainbow triangle and then used the trifoce vertices to add more colors. A normal triangle has 3 points, the triforce has 6 - meaning double the colors. 

I still need to get a handle on debugging basically every stage of the graphics pipeline. If I am not learning anything in this process it is debugging. I still don't have a super solid grasp on the connection between VAO, VBO, and EBO. Maybe a YouTube video will clear it up? What is next I don't know. I guess I will go back to Learn OpenGL and do the next stage. I could also download a book and give it a read. More to follow tomorrow and the next day. 

Ultimately I would be extremely happy with some kind of solar system simulator and a click and turn feature and a sliding bar to speed or slow down time. 

The dream of a 3D Water Polo video game side project is still very much alive. We will see. 

---------------------------

May 27th 2025

Just managed to import the STB and GLM libraries. The plan of attack for today and tomorrow is to basically catch up to where I was before in the graphics programming class. Lets get a rainbow 3D outputted and rotating and then a 3D cube with a texture mapped to the surface of the cube. That is two separate projects and hopefully it goes smoothly.

After some headaches and a few hours of debugging I have the cube textured with a rainbow interpolation and rotating. A major source of problems was crashing caused by calling the Rendering State Configuration Functions BEFORE the window was properly setup. That is a big note for debugging later. I couldn't even get output on it just immediate crash. IE (glEnable(CL_DEPTH_TEST) / glFrontFace(GL_CCW) / glEnable(GL_CULL_FACE)). Long story short, the window object needs to be properly built before any of those functions can be called.

Drawing the cube on paper was yet again the way to go. Knowing the vertices coordinates and the indices made connecting them so much easier. 

The using of the GLM lib to create the mat4 objects and linking them to the shaders may take some more practice. I understand fundamentally what is happening and why, but the practical application and debugging is still a challenge. I don't know if that is because I am dense or too dim to see it though. Again, I understand the fundamental connection between the shader program and the C++ execution, but just practically learning them has been a challenge. 

I am excited to do more with shaders and with some interactability in the future. My immediate thought is that I can spin the cube with a mouse interaction and use a derivative to slow it down to create an incredibly basic physics simulations. 

I haven't used the STB library yet to import a texture, but that is next on the agenda: finding a square texture somewhere and applying it to the face of the cube. 

------------------------

May 28th 2025 @ 11:33

The cube is now textured with a wood crate / flooring image from OpenGameArt.org! Like every other step of this process it has been more painful than I had anticipated. I'm still mastering the shading language but I think I got the layout down, just getting the process oriented in my head is a bit challenging:

Your LAYOUTS reserve a space on the GPU to allow for skips. IE I have 12 * 6 = 72 vertices and 4 * 6 = 24 texture coordinates. Those need to reserve the breadth across the GPU memory. As in the GPU memory need to be 72 + 24 GLuint floats across. The layouts allow us to split that segment into two different sections for the GPU to work with. This keeps the vertex data separate from the fragment / color data IN THE SHADING LANGUAGE. 

The vertex shader takes INPUTS from the program (our vertices and texture coordinates) and OUTPUTS them (textureCoords). Any outputs need to go to the FRAGMENT shader (BIG NOTE HERE: FOR THE SECOND TIME I HAVE SPENT 30 MINUTES DEBUGGING WHAT WAS A BASIC NAME MISMATCH. THE TWO INPUT AND OUTPUT VARIABLE NAMES MUST MATCH). 

We declare an OUTPUT vec4 FragColor (vec 4 for RBGA and output to output to the screen.) We declare textureCoords as INPUT from the vertex shader. We also declare a uniform sampler2D. Our main rendering loop then has a glUniform1i function to point to the fragment shader program texture unit. 

I'd like to consolidate some of this texture code into its own class or function so that is on the agenda and then modifying the CMake file to properly point to the assets folder. After about 10 minutes I coulnd't get it to work and had to move on to properly debugging the code before I could confirm that any kind of build system change would work. Leaning on one debug output for that kind of thing seems incredibly risky.

Up next is consolidating a lot of the texture work to and properly modify the CMake to get the asset directory structure agnostically.

@ 17:20 

It is all wrapped up. I have a much better understanding of the shading language and the code is a lot cleaner. Maybe an entire class wrapper isn't the way to go there, but it seems like the standard. Hopefully I develop opinions of how it should look later. That would mean I am confident enough to have some expertise. 

Big details to hit for the afternoon session - making sure to Bind the texture unit. That was a small source of begugging at the end there. AND only using the:
#define STB_IMAGE_IMPLEMENTATION
once in a project and then including stb as normal from then on. 

Overall, much more painful than anticipated, but that is typically the only way to learn. Notably, the size of the project is getting more and more unwieldy so when I reach out to the LLM it gives less concise feedback and I have to rely on my programming knowledge more.

I'd still like to rotate it with a mouse and then have it slowly slow down as if it were some kind of character customization screen where the model can be manipulated. I think that might be a good exercise in basic physics simulation.

------------------------

May 30th 2025 @ 15:39

I have the camera class mostly working as intended. I still need to program the mouse buttons for looking around the sceen and that looks a little bit more complicated, but its only a few more lines in the INPUT functions so it shouldn't be too difficult. Building the class wrapper for the camera was fairly simple. We have done this with the Shaders and with the VAO and with textures already. Move all the functions that are normally associated with the camera in main into a class to clean up the main function and reuse the camera later. 

Some noteworthy things I learned so far:
Since we are changing the model matrices to a camera it is only appropriate we stop the model from rotating. This makes practical sense. The model floats in space and we want to move the camera around it, it doesn't necessarily need to be rotating, in fact its more of a distraction than anything. So in the making of the camera I realize I wanted to RE-ADD the rotation to the model matrix for the sake of exercise. I thought it would be difficult but it turned out to be easier than I thought. Our new camera class took the Orientation and Position matrices and passed those to the shader in a uniform mat4 camMatrix. We multiplied them in the class so we only need one matrix in the vertex shader. In general I'd rather have the C++ code be more complicated and let the shaders be simpler so this works out. But it didn't leave an entry point to re-add the model matrix. We can simply define our own, pass it to the shader language with a uniform just like before, and multiply it with the camMatrix variable. Boom done. 
uniform mat4 mModel;
uniform mat4 camMatrix;

IN THE VERTEX SHADER
uniform mat4 mModel;
uniform mat4 camMatrix;


void main() {
	
	gl_Position = camMatrix * mModel * vec4(aPos, 1.0);
	// gl_Position = vec4(aPos, 1.0);
	
	textureCoords = aTexCoord;
}

IN THE MAIN RENDERING LOOP
glm::mat4 model = glm::rotate(glm::mat4(1.0f),
                    rotation,
                    glm::vec3(0.5f, 1.0f, 0.25f)

);

// Get the mModel location
GLuint modelLocation = glGetUniformLocation(shader.getProgramID(), "mModel");
// Pass that location back to the vertex shader
glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

Boom. Done and dusted. I learned something new about shaders - which has been what I wanted.

Another thing I learned is the transformation matrices. Always keeping the up matrix as a way of orientating the camera. If it knows a single cardinal direction all the movement can be derived. It might be worth making that a const type so it can't be accidentally changed in the future. The normalizatio nfunction makes every vector's length 1, meaning it always moves at a consant rate. 

Also there is a distinction between GL_BUTTON_PRESS and GL_BUTTON_RELEASE - that proved slightly difficult debugging. 

@ 17:17 - Implementing the camera movement


Going back now and deleting the commented out camera stuff from main before we had the camera wrapper.

Mouse buttons implemented and I am honestly quite confused about how it works. But I'll try to walk myself through it. First, standard stuff, if the mouse button is pressed the cursor should be hidden. Almost every program in the world does this.

We declare doubles for the X and Y coordinates of the mouse - we give those memory addresses to the GetCursorPos function. We pass them as memory addresses since they are going to be updated every loop of the rendering loop.

Next we normalize the cursor to the center of the screen. If we it would immediately move to in the inputted click and jump around, as opposed to us being able to smoothly pan around the window.

We calcualte the new orientation and location and write it to a vec3. 

We have a guarding IF STATEMENT to prevent the camera from pitching forward and preventing the camera from flipping upside down. 

We move our Orientation left and right with the calculated inputs.

Lastly, we unhide the cursor and return it to the center of the screen when we release the mouse button so the cursor doesn't fly away. And reset our first click bool

------------------------

June 1st 2025 @ 12:39

I am trying to understand why we are chaning the cameraMatrix in the camera class. I still don't entirely understand entirely. It seems like all we are doing is incorporating the mat4 cameraMatrix variable into the Camera class definition so the matrix now is a member instead of having to modify it in the main function. Unknown. If I get more insight I will talk about it more here. For now I'm just doing my best to understand what is changing even if it is minor change. 

Leaving for a responsibility - need to write the shader program, write the new vertices and indices to VAO, VBO, and EBO objects, and place it into the rendering loop. Probably a scale function as well so we can shrink the light cube - then we can go back to following the tutorial after that for how lighting works. 

------------------------

June 2nd 2025

Back to the problem. From previous entry I need to insantiate and render the object on screen. Here we go. Writing to the vertex and fragment shader is slightly different. Since we are including a model this time and will be shifting it around we will include a model matrix now. The exercise of having removed the model and then re-adding it without it being pre calculated in the C++ program came in handy. My understanding is that we want this light source to be moveable so we can move the light around. If now the model's location is basically stuck in the middle of the scene. 

The cube is now rendering and is white as intended, but I want to be able to scale it and be move it to a different location so it is smaller and above the textured cube.

Okay, so this is lesson seems to be divived into two parts. Getting the cube setup outside the textured cube and then using the shader language to modify the lighting. 

Just spent the last hour refactoring the main rendering loop. My understanding now is more complete. Basically every object in the world has its own shader program and they need to be executed in order. IE Rendering loop for the Cube and then rendering loop for the Lighting Cube. Which is why they now have two different sets of fragment and vertex shaders. They need to draw their own objects. There is definetely a possibility of abstraction here where we have a different shading language for differnt objects.

A big revelation from the tutorial - lighting for now - is just multiplying the colors of the light together. IE if the light is 
(1.0f, 0.0, 0.0) and the object is (1.0f, 0.5f, 0.0f) or orange. If you multiply them together you get red. The object will now receive a red color. This is reminding me of using red light to read map in the Marine Corps during night land nav. Red markings on the map for roads were invisible and you had to be careful how you red the map since red * red == invisible (in comparison to the other map stuff)

Okay I need to stop for the evening but I think I am ready to move on to normals. I should watch another youtube video on how they exactly work. The tutorial I'm following gives it a 30 second explanation and moves on and I am really confused. My VAO object should be setup to input them tomorrow. My indices on the textured cube have to change for some reason too. I anticipate tomorrow being quite difficult. We will see.

------------------------

June 3rd 2025

Picking up where I left off, today will be watching YouTube videos and making sure I understand normals before I move on and start to input them into the cube vertices and debug it. I want to make sure I completely understand this concept and can implement it, at least in overall concept, before I ask an LLM to debug my code. 

What I do understand. The normal vectors for diffuse lightings are just vectors of size one that shoot out perpendicularly from the face of the primitive. This is called a face normal. If each face has a single normal, that normal represents the orientation of the entire flat face, and thusm its effect is unform across the face. IE - there is no interpolation - the smooth spread of the light across the surface won't happen. See the picture at the top of the learnopengl page for the example of the diffuse lighting. The new frag color is calculated and then spread across the entire face of the cube. 

https://learnopengl.com/Lighting/Basic-Lighting

However, in your current code we are setup to provide the veritces with 3 sets of data - 3 floats for the vertex coordinates, 2 floats for the texture coordinates spread across the face of the cube, and 3 more floats for the normal data - the normals allow us to interpolate a new color across the face of the cube. 

How we find the location of these normals is pretty complicated and a class in trig and linear algebra specifically for graphics programming would be incredibly helpful. We calculate the face normal by taking the CROSS PRODUCT (not the dot product) of two NON-PARALLEL edge vectors that form the face. For example, if you hve a triangle wth vertices A, B, and C you can find the normal by: normalize(cross(B - A), C - A)
	 B
    / \
   /    \
  /       \  
 /          \
A-------------C

Vertex normals, what we are using so we can interpolate the fragment shader, are typically pre calculated by the 3D grapics modeling software and are incorporated in the mesh data. It works by averaguing the face ormals of all the polygons connected to that vertex. This average then points outwards in a way that allows for smooth lighting interpolation. 

The dot product is used AFTER you have the normal. It's used in the lighting equation to determine the ANGLE between two vectors. The prime example being the angle between the surface normal and the light direction.

Light source      Normal Vector
	        \   |
	         \  |
     Angle    \	|
______________________________________
               Surface of the mesh

Normally, this kind of normals data will be calculated in 3D modeling software. A piece of software like Blender's most basic application is allowing an artist to design meshes and animate things. Those meshes and transformation are simply vertices / lighting values - like our cube - but far too complex to input by hand. So the work is extrapolated to the 3D art software. For this reason I will have to manually input the normal data. This will likely be difficult and I'll have to find a decent method of calculating it by hand. Lastly the steps I will have to do to finish this lesson are: 
1.| Modify vertices data to take in normal data
2.| Modify the VAO linking function to account for 3 more floats
3.| Change the default vertex shader layout
4.| In the default.vert add a vec3 output for the normal, add a vec3 output fragPos so the 'light' can be interpolated and then take care of the calculations in the fragment shader.

I shouldn't have to modify indices - but we will see. I am slightly different than the tutorial I am following. It seems like I've already taken care of that because I am using a textured cube as opposed to a pyramid.

@ 18:27

Done and working as intended.

The modification of the vertices and the VAO object was quite a bit easier than I thought it would be. I thought the Normal vectors would be different for some reason, but either kind of the normals works for all kinds of lighting is now my understanding. So inputting a perpendicular line was easy. The top face was labeled in the comments (0.0, 1.0, 0.0) is a straight up vector. Easy.

Changing the VAO object was easy as well. Just account for the layout, data, and offsets, and we are good.

The hardest part I need to go back and read the learnopengl article on is the fragment and vertex shader changes I had to make. I somewhat understand the steps, but the math is a complete mystery. Again, I really would love to take a trig, calc, linear algebra class FOR computer graphics. LOTS AND LOTS OF linear algebra above the hood and I'm sure loads of calc and trig below. Just the feeding of the camera position, lighting position is the biggest key here. I don't know what more there is to say besides I'm somewhat glad this is over, but of course, I know its not and I will be returning for the rest of my graphics programming career so I might as well get cozy with the concepts over the week.

------------------------

June 4th 2025

Next up the Specular Maps. Specular maps are a type of texture map to control the amount and color of specular reflections on a surface. My understanding is that it is a basically a black and white (or more specifically - grayscale) version of the texture and that shows how reflective the light should be. So in our wood texture there is a lot of blacks and darker colors at are inbetween the wood 'planks'. That light needs to be relfected LESS than the lighter part of the wood which would reflect more. As it is now - the specular reflections are just uniform across the surface and looks good, but not quite realistic. The specular map will provide an even more realistic gradient. 

For the sake of the tutorial we will begin by modifying the texture class so it is easier for us to assign multiple textures to the same shader. For the sake of seeing the example it may be worth it to use a different image that has more contrast. The wood crate texture I am using now doesn't have very much dark color across it. We can also move the light a bit closer.

We get the specular map into our main.cpp by importing the texture but only using ONE color channel, in this case, red. Because we are only using one color channel this will effectively grayscale the image. We will create a new texture object and work to port it over after commenting out some of the other texture statements. We will then export it to the shader, and bind it in the main rendering loop. That should be the work to be done in main.cpp

Now in the shader, we import the texture in the default.frag and use that to modify the final frag color. More to follow on those details.

A new revelation - the image that is loaded for the specular mapping actually has to be grayscaled. We can't rely on anything to grayscale for us. I would love an stbi function to grayscale it, but oh well. We use the .r for the single channel on the grayscaled image to get the proper specular map. 

It is fairly easy actually. The biggest changes are only in our specular lighting section of the fragment shader. We declare an extra uniform sampler2D for the grayscaled texture. We use ONLY THE RED CHANNEL from that texture to calculate our finalSpecularStrength INSTEAD of only using standard texture. From there we cacluate the lighting as normal. The same calculations are stored in result. Result is then pushed to FragColor as a vec4. FragColor still takes the NON grayscaled texture (we still want to load the colored texture).

The last issue I am facing is the vertical lines of light the are across the surface of the cube. It signals to me that the specular lighting is working better now, but it is a strange artifact to have and there are no answers readily found with google. 

![alt text](image-1.png)

I couldn't find an issue or a solution in an easy amount of time. I will keep it in there for a while until I find something that causes this. I am ready to put this one to bed. 

Laslty, specular lighting is going to be incredibly important in a water polo video game. The way the light reflects off the surface of the water is going to change from pool to pool (indoors, outdoors, kinds of overhead lights, if there are windows etc etc).

Like a LOT of these tutorials, there is obviously huge amounts of potential for abstraction. I am trying to follow a bit of Jonathan Blows advice and wait sometime before refactoring anything. Often times we want to refactor something for the sake of cleanliness and readability or whatever great programming virtue, but we often refactor TOO soon. Meaning, there is still more to learn about a particular technology or product and a more intelligent refactoring is just around the corner and we end up wasting time refactoring code more times than necessary. Build up the expertise and lessons learned AND then refactor. Maybe that will have the lessons stick less - that is a factor I am worried about, but I think he is correct about waiting to apply our lessons learned before we go forward. 

This does also conflict with his advice of, write a program, rewrite it so its better, rewrite it so it is even better again and again until it is perfect. And maybe, if you're lucky you have a good program that does something interesting with the computer. More to follow. 

------------------------

June 6th 2025

Moving onto the different kinds of light we can use. In general we have three kinds of light: point, directional, and spot. 

Point lights illuminate the environment in all directions, which is what we were doing with our light the last two lessons. It is basically the sun. It sends light out in all directions just as the sun illuminates the solar system. There is a catch - just like in real life the intensity of the light becomes less intense as it moves away and it strength decreases exponentially (inverse square relationship or 1/x^2). In our point light example we did not incorporate this. 

In computer graphics we have a slightly more complicated equation to simulate this. Instead of just 1 / distance squared we have to use 1 over a quadratic equation with respect to distance. Typically this equation is written 1 / a * d^2 + b * d + 1 where a and b are constants. A is the quadratic term and B is the linear term. A changes how fast the intensity dies out and B changes how far the light reaches. Look at this image from desmos for an illustration. The Y output of the function is our light intenisty and we can change the inputs for A and B. My understanding is that we want these consants normalized. Going beyond certain values in the equation has a lot bizzare undefined behavior in the graph.

![alt text](image-2.png)

This lesson has implement this really quickly. We start by writing a pointLight function in the fragment shader where we copy everything over. This is somewhat notable since its our first function outside of main for our shading language.

First we simply need the distance from the light to the object. This is simply the vector that comes from the subtracting the current position from the light position. We already do this for the diffuse lighting, but it is not stored as a variable. We create a vec3 lightVec and can replace that in the function. We then get the distance by using a length function on the vector. Lastly, we right out the equation with our variables. Float A = 3.0; etc and store that in an intensity float variable and then apply it to the specular and diffuse lighting. 

Directional lighting is next and is actually the easiest to implement. This too works like the sun but on the scales we see on Earth as opposed to the solar system. The suns rays are so far away and the sun so massive that the rays are essentially parallel. Also similar to the sun, the source of light is so distanct from the scene the lights are basically parallel. Because it is so far we remove the dimming. 

We basically just copy the function over from the point light and instead of calculating the light direction based on two points we pass in a constanct vec3 and normalize it. For the sake of this example we have to point the light in the OPPOSITE direction we want it to face. I wonder if we can't just subtract the result of the normalized vector instead? Wouldn't that point it in the opposite direction?

The last type of light is the spot light and illuminates an area in a conic area, light a spotlight or a lamp. We again beging by taking the pointlight function. We then define the two foats that represent the cosines values of two angles. The first angle is the angle between the inner cone and the direction of the light, the second angle is the angle between outer cone and the direction of the light. See the example below.

![alt text](image-3.png)

We use the two cones to create a gradient between the intensily illuminated area and the transition to darkness. 

![alt text](image-4.png)

This tutorial wrote the cosine values directly into the floats as opposed to using angles to calculate it and a cosine function and their respective returned values. Apparently there are performance concerns? That seems strange to me, trig functions are some of the most fundamental operations in computers - how intense can the performance hit be?

Nevertheless, we calculate the angle between the current part being lit and the central direction of the light using a dot product. This will give us yet another cosine value which matches perfectly with our other cosine values. Lastly we need to get the intensity of the gradient and return the clampled value between 0.0 and 1.0. That formula is the following:

intensity = clamp((angle - outerCone) / (innerCone - outerCome), 0.0f, 1.0f)

Lastly we multiply this intensity by the diffuse and specular lighting and should have our final values to return.

This lesson is nice, and quick, but also fundamental in the lighiting sense. It is quite nice it takes place entirely in the fragment shader, which simplifies our debugging and focuses our learning.

Next up is a mesh class which may take considerably longer, but is likely to be an extremely helpful abstraction over our vertices and indices we have for our two cubes.

------------------------

June 7th 2025

Okay! The time has come to abstract all this together. Finally. I've been dealing with shaders, vertices, and indices, one at a time and calling them sequentially as we step through the main function. Not to mention standard arrays, which are great, but are difficult to make abstractions around. Using vectors just gives a lot more confidence that this can abstracted well.

I imagine this is the heart of grahpics programming. Wrapping up all this semi complicated instructions with the GPU and putting it into a single mesh class. I also imagine this is where a lot of decision making comes in. How exactly do we abstract away a mesh defines a lot of what the engine will do. I can imagine that this is a big decision that comes early in development and an intelligent decision guided by experience needs to be made early before things get too big and unwieldy to refactor. 

After reading the tutorial I also understand the criticism that things like Unreal and Unity get. Yes, you can use those off the shelf, but if they implement something in a way that doesn't work for your particular game then it can be a bit rough. Additionally, if you have a source modifiable license of those engines, going in and changing the way it handles something like meshes is basically splitting the atom. 

Of course I know what a mesh is - I've seen the monkey head and donut in Blender, but it might be nice to have a concrete definition. A mesh simply is the set of vertices, indices, and textures for a model. That is basically it. And as I've said before all a video game model is, is a series of vertices and indices stored in GPU memory. So when we take the model from Blender it is stored as vertex coordinate, how they are connected with indices, and the texture that acompanies it, and normals. All the things we have manually encoded our cube with, Blender does for us to be loaded into the game engine. 

To begin with the actual programming I'm going to be refactoring the class names to be more uniform. textureClass needs to be renamed to texture etc. Actually quite a bit easier to do than I thought. Simply reading the compilation errors and clearing them was enough. 

Okay, I'm going to have some questions or maybe concerns with this tutorial so far. In our Mesh class we are defining one of the vectors of our Mesh data as a Vertex data class. We are then putting a struct for Vertex in the VBO.h file. We will see how this goes, but it seems like a bizzare place to place it and weird that it is a struct. We will see. Again, my read right now is that this is an important decision but we will see how it plays out. Also dealing with structs in C++ is so much nicer than in C. Just declare that sucker and shes ready to go. 

The vertex struct basically just stores all the data that is in our vertices: Position, Normals, Color, and texture coordinates.

I'm finding my beef now and I had to go to an LLM to get a decent answer. This tutortial wants us to include color data into the Vertex struct. This seems sily to me. After the rainbow cube I haven't done anything with color data, why include it as a part of the mesh? Isn't everything in the game going to be textured? According to the LLM this is an area of tradeoff, if we are going to just texture everything, why would we need to store information for color? I'm going to refactor to include this, but it seems silly so far and a pain in the neck to include. - Not to mention our vertex data need to store in a particular order (the order the vertex struct defines its parts in). We will see.

I am at a stopping point and want to make a note for my future self at where I am at. I am done modifying the vertices to have the correct data and in the correct order. I have modified the VAO LinkAttrib methods in the Mesh class. I have NOT compiled in a while. To do so I need to modify the main function to account for the new parameters of the new VBO and EBO objects. (They now take in a reference to a vector as opposed to an array and the size). That apparently comes later in the tutorial and I'm apprehensive I'll waste my time making the refactorizations now. 

I still have some questions I'll need to get answered in the future: Is this the standard order vertex data is stored? How can we change it in the future? More to follow.

------------------------

June 9th 2025

Okay, so I didn't journal for the 8th despite working on this for over 6 hours. The lack of compilation and checking the output caught up with me. I eventually got the cube to draw using the new Mesh class abstraction but could never find the problem with the texture loading. I tried what I thought was everything. My frustration mounted and mounted and mounted and there was I could find. And eventually it just because such a hot mess of debugging that I had to start over. This is me doing that and changing my approach. I'm going to start over, now checking my incremental updates to ensure the cube still draws as God intended. 

My general order of operations are again
1: Rename the Texture and Shader classes == Done
2: Refactor the Vertices and the vertex shader to account for color data (that we aren't even using) 
     - Done and the cube is still drawing as intened == Done 
     - Now we want to reorder everything so it will match the Vertex struct == Done
3: Change the link Attrib VAO and make sure that works with the new data. == Done
     - This is done for the Textured Cube - lets do this for the light cube next == Done
3A: Refactor the EBO class to take in a vector of indices
3A: Refactor the texture class to work in a vector == Done
4: Refactor it to use Vertex structs - make sure it is working == Done
5: Introduce the Mesh class  
6: Introduce the Mesh class in steps to ensure the cube is drawing as intended
7: Hopefully we are finished


THIS SEEMS TO BE IT. When using the textures in a vector the textures are not loading properly. But when manually and hard coded called they work. 

After some tooling I see the problem now and I need to write this down to remember it. It works as intended when calling the functions from a normal array of Textures. But when initialized to a Vector it suddenly breaks. We need a copy constructor - not because of the const char* or any OpenGL data type - but bcecuse when a texture is copied, the default copy constructor just copies the GLuint texture ID, meaning two objects now think the "own" the same OpenGL texture. The rub comes with how .emplace_back() and resiable arrays work. When we "increase the size of the array" we are actually defining an entirely new array and MOVING / COPYING everything over to that new array that fits our data. That is the problem here and what is doubly frustrating is that of course I know this. Why didn't I bother to think it was an issue with the vector? I know how arrays and resizable arrays work and I am just so fucking bad at debugging I never bothered to look at the problem from every possible angle. I just trusted C++ to take care of it for me and that is not how this works. I digress. If we don't define a custom copy / move constuctor when we 'emplace_back()' we are only copying the textureID member and not the actual texture and two texture objects have the same ID and both will call glDeleteTextures() in their destructor. So we need the rule of the Big 5 to fix this problem, just like I learned about at school and I was so annoyed I had to learn it, because isn't it so obvious you have to do this. But look at me. Victim of my own hubris. 

Quick overview of the Big 5 - since I'm mostly only familiar with the Big 3. If we implement one, we have to implement all. What those are:
1. Destructor
2. Copy Constructor
3. Copy assignment overload
4. Move constructor - to transfer ownership WITHOUT copying
5. Move assignment operator - to transfer ownership on assignment

Quick update - and that was it, and even more problems with the vector. It doesn't like initializing it with the shaders. The initialization apparently creates an unnamed temporary Texture object, which then get copied or moved into the vector and that is sensitive. This is different than creating the objects permanently and emplacing them in the back. This is okay with me, the emplacing_back method is honestly easier for me to read.

What does the syntax mean for the Move constructor and the move assignment operators?: Texture(Texture&& other) noexcept; What does noexcept mean, and what is the reference to a reference?

The double reference in the move contructor && identifies this as a move contructor and is an rvalue reference. Rvalue references are a kind of reference introduced in C++ 11 that can bind to temporary objects (things that are about to be destryoed). The move contructor "steals" resources (like an OpenGL texture ID, or strings) from this termporary object OTHER instead of copying them.

NOEXCEPT is a keyword that specifies this function is guranteed not to throw exceptions. It's a promise to the compiler andanyone using this function. The standard library loves it apparently. When resizing a vector it will only use the move constructor if it is a NOEXCEPT function, otherwise it will fall back for safety. Similar to ordered maps not liking objects that don't have comparison overloads.

------------------------

June 10th 2025

Carrying on from yesterday with the revelation of how Vectors are handled. Three or four days debugging later it feels amazing to finally have an understanding of what was going wrong and enhanced skills are debugging. More troubles today, but it was nice to finally have a shot at reading what exactly the code was doing. Move semantics still weren't working for some reason and part of the reason I don't care for vectors, but I understand why they are necessary in this case. If something needs more than one texture file to layer over a model we need to support more than just the normal diffuse and the specular textures. (IE supporting more than one texture pass). The solution was to use a shared pointer so the texture vector can properly transfer ownership from function to function. That may be my standard going forward. I'd probably be smart to more fully understand what smart pointers do under the hood and rewrite much of this code base in it, but that may be a task better saved for the end when I can spend multiple days refactoring and improving the tutorial in its entirety. Either way things are looking good. The draw method appears to work as intended and I am moving the light vertices now and deleting all the unnecesary commented out code. Big day today and the culmination of a lot of work since Saturday. I am on my way to be a better programmer and graphics programmer. Like a lot of things in life - the most painful path has the most growth. I of course love math, and feel better learning more math, but damn if it isn't a painful process. I've always said it is easier to go to the gym 5 times a week than it is 1 time a month and that example is obvious here. More to follow when the tutorial is complete.

After finally debuggin another 4 hours I found the last issue of the initialization. One final statement must have gotten deleted and it was causing the error. I really need to install a debugger into VSCode to debug these statements instead of just trying to read the program. It is also getting to the point in which the LLM can't help me except in really specific and tight scenarios like with the vector issue - I need to start thinking much more on my own because the only thing that will be able to help me before long are other people using OpenGL. I'm incredibly done. I am committing this and pushing it. Onto the next lesson.