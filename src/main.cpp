#include <iostream> 
#include <globals.h>
#include <vector>

void GetOpenGLVerisionInfo(){
	std::cout<< "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout<< "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout<< "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void VertexSpecification(){
	const std::vector<GLfloat> vertexData{
		//0th vertex
		-0.5f,-0.5f,0.0f, //V
		 1.0f,0.0f,0.0f,  //C
		//1st vertex
		 0.5f,-0.5f,0.0f, //V
		 0.0f,1.0f,0.0f,  //C
		//2nd vertex
		 -0.5f,0.5f,0.0f,  //V
		 0.0f,0.0f,1.0f,  //C
		//3rd vertex
		 0.5f,0.5f,0.0f, //V
		 1.0f,0.0f,0.0f,  //C
	};
	//vao
	glGenVertexArrays(1,&Globals::gVertexArrayObj);
	glBindVertexArray(Globals::gVertexArrayObj);
	//vbo
	//1
	glGenBuffers(1,&Globals::gVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER,Globals::gVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		vertexData.size()*sizeof(GL_FLOAT),
		vertexData.data(),
		GL_STATIC_DRAW	
	);

	const std::vector<GLuint> indexBufferData {2,0,1,3,2,1};

	glGenBuffers(1,&Globals::gIndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Globals::gIndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				indexBufferData.size()*sizeof(GLuint),
				indexBufferData.data(),
				GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GL_FLOAT),
		(GLvoid*)0	
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GL_FLOAT),
		(GLvoid*)(3 * sizeof(GL_FLOAT))	
	);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

GLuint CompileShader(GLuint type, const std::string& source){
	GLuint shaderObject;
	if(type==GL_VERTEX_SHADER){
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	}else if (type == GL_FRAGMENT_SHADER){
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}
	const char* src = source.c_str();
	glShaderSource(shaderObject,1,&src,nullptr);
	glCompileShader(shaderObject);
	return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource){
	GLuint programObject = glCreateProgram();

	GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER,vertexShaderSource);
	GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER,fragmentShaderSource);
	glAttachShader(programObject,myVertexShader);
	glAttachShader(programObject,myFragmentShader);
	glLinkProgram(programObject);
	glValidateProgram(programObject);

	return programObject;
}

void CreateGraphicsPipeline(){
	reader *r = new reader();
	std::string vs = r->readAsString("../shaders/vertex.txt");
	std::string fs = r->readAsString("../shaders/fragment.txt");
	Globals::gGraphicsPipelineShaderProgram = CreateShaderProgram(vs,fs);
	delete(r);
}

void init(){
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout<<"SDL2 Initialization failed"<<std::endl;
		exit(-1);
	} else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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
void PreDraw(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glViewport(0,0,Globals::gScreenWidth,Globals::gScreenHeight);
	glClearColor(1.f,1.f,0.f,1.f);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(Globals::gGraphicsPipelineShaderProgram);

}
void Draw(){
	glBindVertexArray(Globals::gVertexArrayObj);
	glBindBuffer(GL_ARRAY_BUFFER,Globals::gVertexBufferObject);
	// glDrawArrays(GL_TRIANGLES,0,6);
	glDrawElements(GL_TRIANGLES,
					6,
					GL_UNSIGNED_INT,
					0);
}

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

	//vao
	VertexSpecification();
	CreateGraphicsPipeline();

	loop();
	CleanUp();
	return 0;
}
