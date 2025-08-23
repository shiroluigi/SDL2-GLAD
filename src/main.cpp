#include <iostream> 
#include <globals.h>


void GetOpenGLVerisionInfo(){
	std::cout<< "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout<< "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout<< "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void init(){
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout<<"SDL2 Initialization failed"<<std::endl;
		exit(-1);
	}else{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		
		Globals::gApplicationWindow = SDL_CreateWindow("MyWindow",0,0,Globals::gScreenWidth,Globals::gScreenHeight,SDL_WINDOW_OPENGL);
		if(Globals::gApplicationWindow == nullptr){
			std::cout << "Window Initialization Unsuccessfull" << std::endl;
			exit(-1);
		}
		Globals::gOpenGLContext = SDL_GL_CreateContext(Globals::gApplicationWindow);
		if(Globals::gOpenGLContext == nullptr){
			std::cout <<"OpenGL Context not available"<<std::endl;
			exit(-1);
		}
		//Initialize GLAD library
		if (!gladLoaderLoadGL()) {
			printf("Failed to initialize OpenGL\n");
			exit(-1);
		}
		GetOpenGLVerisionInfo();
		std::cout<<"Initialized all"<<std::endl;
	}
}


void Input(){
	SDL_Event e;
	while(SDL_PollEvent(&e) !=0){
		if(e.type == SDL_QUIT){
			std::cout << "Program Exit" << std::endl;
			Globals::quit = true;
		}
	}
}
void PreDraw(){}
void Draw(){}

void loop(){

	while(!Globals::quit){
		Input();
		PreDraw();
		Draw();

		//swap the buffers to display
		SDL_GL_SwapWindow(Globals::gApplicationWindow);
	}
	
}
void CleanUp(){
	SDL_DestroyWindow(Globals::gApplicationWindow);
	SDL_Quit();
}

int main(){
	init();
	loop();
	CleanUp();
	return 0;
}
