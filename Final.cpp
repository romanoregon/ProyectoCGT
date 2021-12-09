/*---------------------------------------------------------*/
/* ----------------  Proyecto Final ---------------------------*/
/*-----------------    2022-1   ---------------------------*/
/*------------- Oregon Arias Roman ------------------------*/
/*------------- 417021340 ---------------------------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>


//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);//funcion donde re reslizaran las animaciones


// settings
GLuint VBO, VAO, EBO;
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(1500.0f, 1000.0f, 6000.0f));//posicion inicial de la camara 0.0 1000.0 500.0
float MovementSpeed = 0.05f;//velocidad de movimiento del mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);//pisicion de la luz
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// variable para textura
unsigned int	t_cubo;

// -------------------------------------------------------------------------------------------------------------------------
// Variables animacion directa
// -------------------------------------------------------------------------------------------------------------------------

//variables del carro
float	movAuto_x = 3800.0f,//como si fuera y
		movAuto_z = -2000.0f,//como si fuera x
		movAuto_y = 100.0f,
		orienta = 0.0f,
		giroLlantas = 0.0f,
		giroAuto = 0.0f;

//Variables del cascanuces
float	movBrazoCasca = 0.0f,
		movBocaCasca = -2.0f,
		movNuezY = -5.0f,
		movNuezX = -5.0f,
		movNuezZ = 0.0f,
		movNuezY2 = 0.0f,
		movNuezZ2 = 0.0f, 
		movNuezY3 = 0.0f,
		movNuezZ3 = 0.0f;

		
//Variables del Avion
float	giroHelice= 0.0f,
		movAvionY = 180.0f,
		movAvionX = -50.0f,
		movAvionZ = 350.0f,
		giroAvion1 =-90.0f,
		giroAvion2 = 0.0f,
		movAvion1 = 0.0f,
		movAvion2 = 0.0f,
		movAvion3 = 0.0f,
		movAvion4 = 0.0f,
		movAvion5 = 0.0f;

//variables boolianas para las animaciones
bool	animacionCarro = false,
		animacionCasca = false,
		animacionAvion = false,

		//animacion cascanueces
		conteoMov1 = false,
		conteoMov2 = true,
		conteoMov3 = true,
		conteoMov4 = true, 
		conteoMov5 = true,
		conteoMov6 = true,
		conteoMov7 = true,
		conteoMov8 = true,
		conteoMov9 = true,
		conteoMov10 = true,

		//animacion Avion
		AMov1 = false,
		AMov2 = true,
		AMov3 = true,
		AMov4 = true,
		AMov5 = true,
		AMov6 = true,
		AMov7 = true,
		AMov8 = true,
		AMov9 = true,
		AMov10 = true;
		


// -------------------------------------------------------------------------------------------------------------------------
// codigo para la manipulacion por KeyFrames
// -------------------------------------------------------------------------------------------------------------------------

//Keyframes (Manipulación y dibujo)

int x = 0;

//Robot
float	RPosX = 0.0f,
		RPosY = 0.0f,
		RPosZ = 0.0f,
		RCabeza = 0.0f,
		RBIzq = 0.0f,
		RBDer = 0.0f,
		RABIzq = 0.0f,
		RABDer = 0.0f,
		RPIzq = 0.0f,
		RPDer = 0.0f,
		RPieIzq = 0.0f,
		RPieDer = 0.0f,
		rotaP = 0.0f;
//Persona 1
float	RPosX2 = 0.0f,
		RPosY2 = 0.0f,
		RPosZ2 = 0.0f,
		RCabeza2 = 0.0f,
		RBIzq2 = 0.0f,
		RBDer2 = 0.0f,
		RABIzq2 = 0.0f,
		RABDer2 = 0.0f,
		RPIzq2 = 0.0f,
		RPDer2 = 0.0f,
		RPieIzq2 = 0.0f,
		RPieDer2 = 0.0f,
		rotaP2 = 0.0f;

//incremento robot
float	IncRobotPosX = 0.0f,
		IncRobotPosY = 0.0f,
		IncRobotPosZ = 0.0f,
		IncRobotCabeza = 0.0f,
		IncRobotBIzq = 0.0f,
		IncRobotBDer = 0.0f,
		IncRobotABIzq = 0.0f,
		IncRobotABDer = 0.0f,
		IncRobotPIzq = 0.0f,
		IncRobotPDer = 0.0f,
		IncRobotPieIzq = 0.0f,
		IncRobotPieDer = 0.0f;

//Incremento Persona
float	IncPerPosX = 0.0f,
		IncPerPosY = 0.0f,
		IncPerPosZ = 0.0f,
		IncPerBIzq = 0.0f,
		IncPerBDer = 0.0f,
		IncPerABIzq = 0.0f,
		IncPerABDer = 0.0f,
		IncPerPIzq = 0.0f,
		IncPerPDer = 0.0f,
		IncRegPosX = 0.0f,
		IncRegPosY = 0.0f,
		IncRegPosZ = 0.0f,
		IncrotaP = 0.0f;

#define MAX_FRAMES 13
int i_max_steps = 60;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float	PosX;
	float	PosY;
	float	PosZ;
	float	BIzq;
	float	BDer;
	float	ABIzq;
	float	ABDer;
	float	PIzq;
	float	PDer;
	float	Cabeza;//cambia a posicion de regalo para persona
	float	PieIzq;
	float	PieDer;
	float	Rota;

}FRAME;

FRAME KeyFrame [MAX_FRAMES];

int FrameIndex = 0;			//introducir datos
bool play1 = false;
bool play2 = false;
int playIndex = 0;

void cargaframePersona(void) {

	ifstream archivo;
	string nombreArchivo, texto;
	int Robot[170];

	nombreArchivo = "framePersona.txt";
	archivo.open(nombreArchivo.c_str(), ios::in); //Abrimos el archivo en modo lectura

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	x = 0;
	while (!archivo.eof()) { //mientras no sea final del archivo
		getline(archivo, texto);

		Robot[x] = stoi(texto, nullptr, 10);

		x = x + 1;
	}

	x = 0;
	for (int i = 0; i < 8; i++)
	{
		KeyFrame[i].PosX = Robot[x];
		KeyFrame[i].PosY = Robot[x + 1];
		KeyFrame[i].PosZ = Robot[x + 2];
		KeyFrame[i].Cabeza = Robot[x + 3];
		KeyFrame[i].BIzq = Robot[x + 4];
		KeyFrame[i].BDer = Robot[x + 5];
		KeyFrame[i].ABIzq = Robot[x + 6];
		KeyFrame[i].ABDer = Robot[x + 7];
		KeyFrame[i].PIzq = Robot[x + 8];
		KeyFrame[i].PDer = Robot[x + 9];
		KeyFrame[i].PieIzq = Robot[x + 10];
		KeyFrame[i].PieDer = Robot[x + 11];
		KeyFrame[i].Rota = Robot[x + 12];

		x = x + 13;
	}

	archivo.close(); //Cerramos el archivo

}

void cargaframeRobot(void) {

	ifstream archivo;
	string nombreArchivo, texto;
	int Robot[170];

	nombreArchivo = "FrameRobot.txt";
	archivo.open(nombreArchivo.c_str(), ios::in); //Abrimos el archivo en modo lectura

	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}

	x = 0;
	while (!archivo.eof()) { //mientras no sea final del archivo
		getline(archivo, texto);

		Robot[x] = stoi(texto, nullptr, 10);

		x = x + 1;
	}

	x = 0;
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].PosX = Robot[x];
		KeyFrame[i].PosY = Robot[x + 1];
		KeyFrame[i].PosZ = Robot[x + 2];
		KeyFrame[i].Cabeza = Robot[x + 3];
		KeyFrame[i].BIzq = Robot[x + 4];
		KeyFrame[i].BDer = Robot[x + 5];
		KeyFrame[i].ABIzq = Robot[x + 6];
		KeyFrame[i].ABDer = Robot[x + 7];
		KeyFrame[i].PIzq = Robot[x + 8];
		KeyFrame[i].PDer = Robot[x + 9];
		KeyFrame[i].PieIzq = Robot[x + 10];
		KeyFrame[i].PieDer = Robot[x + 11];
		KeyFrame[i].Rota = Robot[x + 12];
		
		x = x + 13;
	}

	archivo.close(); //Cerramos el archivo

}

void resetFrames(void) {
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].PosX = 0;
		KeyFrame[i].PosY = 0;
		KeyFrame[i].PosZ = 0;
		KeyFrame[i].Cabeza = 0;
		KeyFrame[i].BIzq = 0;
		KeyFrame[i].BDer = 0;
		KeyFrame[i].ABIzq = 0;
		KeyFrame[i].ABDer = 0;
		KeyFrame[i].PIzq = 0;
		KeyFrame[i].PDer = 0;
		KeyFrame[i].PieIzq = 0;
		KeyFrame[i].PieDer = 0;
		KeyFrame[i].Rota = 0;
	}
}

void resetElements(void)
{
	RPosX = KeyFrame[0].PosX;
	RPosY = KeyFrame[0].PosY;
	RPosZ = KeyFrame[0].PosZ;
	
	RCabeza = KeyFrame[0].Cabeza;
	RBIzq	= KeyFrame[0].BIzq;
	RBDer	= KeyFrame[0].BDer;
	RABIzq	= KeyFrame[0].ABIzq;
	RABDer	= KeyFrame[0].ABDer;
	RPIzq	= KeyFrame[0].PIzq;
	RPDer	= KeyFrame[0].PDer;
	RPieIzq = KeyFrame[0].PieIzq;
	RPieDer = KeyFrame[0].PieDer;
	rotaP = KeyFrame[0].Rota;
}

void interpolation(void)
{

	IncRobotPosX = (KeyFrame[playIndex + 1].PosX - KeyFrame[playIndex].PosX) / i_max_steps;
	IncRobotPosY = (KeyFrame[playIndex + 1].PosY - KeyFrame[playIndex].PosY) / i_max_steps;
	IncRobotPosZ = (KeyFrame[playIndex + 1].PosZ - KeyFrame[playIndex].PosZ) / i_max_steps;
	IncRobotCabeza = (KeyFrame[playIndex + 1].Cabeza - KeyFrame[playIndex].Cabeza) / i_max_steps;
	IncRobotBIzq = (KeyFrame[playIndex + 1].BIzq - KeyFrame[playIndex].BIzq) / i_max_steps;
	IncRobotBDer = (KeyFrame[playIndex + 1].BDer - KeyFrame[playIndex].BDer) / i_max_steps;
	IncRobotABIzq = (KeyFrame[playIndex + 1].ABIzq - KeyFrame[playIndex].ABIzq) / i_max_steps;
	IncRobotABDer = (KeyFrame[playIndex + 1].ABDer - KeyFrame[playIndex].ABDer) / i_max_steps;
	IncRobotPIzq = (KeyFrame[playIndex + 1].PIzq - KeyFrame[playIndex].PIzq) / i_max_steps;
	IncRobotPDer = (KeyFrame[playIndex + 1].PDer - KeyFrame[playIndex].PDer) / i_max_steps;
	IncRobotPieIzq = (KeyFrame[playIndex + 1].PieIzq - KeyFrame[playIndex].PieIzq) / i_max_steps;
	IncRobotPieDer = (KeyFrame[playIndex + 1].PieDer - KeyFrame[playIndex].PieDer) / i_max_steps;
	IncrotaP = (KeyFrame[playIndex + 1].Rota - KeyFrame[playIndex].Rota) / i_max_steps;
}

void animate(void)
{
	//animacion key frame
	if (play1)
	{
		
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play1 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			RPosX += IncRobotPosX;
			RPosY += IncRobotPosY;
			RPosZ += IncRobotPosZ;

			RCabeza += IncRobotCabeza;
			RBIzq += IncRobotBIzq;
			RBDer += IncRobotBDer;
			RABIzq += IncRobotABIzq;
			RABDer += IncRobotABDer;
			RPIzq += IncRobotPIzq;
			RPDer += IncRobotPDer;
			RPieIzq += IncRobotPieIzq;
			RPieDer += IncRobotPieDer;
			rotaP += IncrotaP;

			i_curr_steps++;
		}
	}

	if (play2)/// animacion Persona
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play1 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			RPosX2 += IncRobotPosX;
			RPosY2 += IncRobotPosY;
			RPosZ2 += IncRobotPosZ;

			RCabeza2 += IncRobotCabeza;
			RBIzq2 += IncRobotBIzq;
			RBDer2 += IncRobotBDer;
			RABIzq2 += IncRobotABIzq;
			RABDer2 += IncRobotABDer;
			RPIzq2 += IncRobotPIzq;
			RPDer2 += IncRobotPDer;
			RPieIzq2 += IncRobotPieIzq;
			RPieDer2 += IncRobotPieDer;
			rotaP2 += IncrotaP;

			i_curr_steps++;
		}
	}

	//Vehículo
	if (animacionCarro){

		if (movAuto_z <= 2300) {
			movAuto_z += 50.0f;
			giroLlantas += 15.0f;///giro de la llanta en sentido al reloj
			if (movAuto_z >= 1300) {
				giroAuto += 1.5f;
			}
		}
		if( movAuto_z >=2000 &&  movAuto_z <= 3200 && giroAuto <= 180.0f) {
			movAuto_z += 25.0f;
			movAuto_x += 20.0f;
			if (giroAuto <= 180.0f) {
				giroAuto += 1.5f;
			}
		}
		if (movAuto_z >=3200 && movAuto_x >= 500.0f) {
			movAuto_x -= 50.0f;
			giroLlantas -= 15.0f;
			if (movAuto_y <= 140.0f) {
				movAuto_y += 3.0f;
			}
		}
		else {
			animacionCarro = false;
		}
		
	}
	//Cascanueces
	if (animacionCasca) {
			if (!conteoMov1) {
				movBrazoCasca -= 2;
				if (movBrazoCasca <= -90.0f) {
					conteoMov1 = true;
					conteoMov2 = false;
				}
			}
			else if (!conteoMov2) {
				movBrazoCasca += 2;
				if (movBrazoCasca >= 0.0f) {
					conteoMov2 = true;
					conteoMov3 = false;
				}
			}
			else if (!conteoMov3) {
				movBrazoCasca -= 4;
				if (movBrazoCasca <= -90.0f) {
					conteoMov3 = true;
					conteoMov4 = false;
				}
			}
			else if( !conteoMov4 ) {
				movBrazoCasca += 4;
				if (movBrazoCasca >= -45.0f) {
					conteoMov4 = true;
					conteoMov5 = false;
				}
			}
			else if (!conteoMov5) {
				movBrazoCasca -= 6;
				if (movBrazoCasca <= -190.0f) {
					conteoMov5 = true;
					conteoMov6 = false;
				}
			}
			else if (!conteoMov6) {
				movBrazoCasca += 6;
				if (movBrazoCasca >= -80.0f) {
					conteoMov6 = true;
					conteoMov7 = false;
				}
			}
			 else if (!conteoMov7) {//movimiento de la nuez
				movNuezZ = 50.0 * sin( -movNuezY/50.0);// Y
				movNuezY -= 3;// Z
				if (movNuezY <= -145.0) {
					conteoMov7 = true;
					conteoMov8 = false;
					movNuezX += 1;
				}
			}
			 else if (!conteoMov8) {
				movNuezZ = (50.0 * sin(movNuezY2 / 50.0)) + 17.6882f;// Y
				movNuezY2 += 2;// Z
				movNuezY -= 2;
				if (movNuezY2 >= 40.0) {
					conteoMov8 = true;
					conteoMov9 = false;
					movNuezX += 2;
				}
			}
			 else if (!conteoMov9) {
				if (movNuezY3 >= 138.0f) {
					movNuezZ -= 1.89f;
					movNuezY3 += 2;// Z
					if (movBocaCasca >= -6.0f) {
						movBocaCasca -= 1.0f;
					}
				}
				else {
					movNuezZ = (50.0 * sin(movNuezY3 / 40.0)) + 56.2251f;// Y
					movNuezY3 += 2;// Z	
				}
				movNuezY += 2;
				if (movNuezY3 >= 186.0) {
					conteoMov9 = true;
					animacionCasca = false;
				}
			}


	}//end if animacion casca
	
	 //Avion
	if (animacionAvion) {
		if (!AMov1) {
			movAvionX -= 6;
			giroHelice += 30.0;
			if (movAvionX <= -300.0f) {
				AMov1 = true;
				AMov2 = false;
			}
		}
		else if (!AMov2) {
			movAvionX -= 6;
			movAvionY += 3;
			giroHelice += 30.0;
			if (movAvionX <= -750.0) {
				giroAvion1 += 2.0;
				giroAvion2 -= 2.0;
			
			}
			if (movAvionX <= -800.0f) {
				AMov2 = true;
				AMov3 = false;
			}
		}else if (!AMov3){
			movAvionX -= 6;
			giroHelice += 30.0;
			if (movAvionZ <= 826.045) {
				movAvionZ = 500 * sin(movAvion1 / 100.0) + 350.0f;//374.99 comienza a mov y 826.045 termina
				movAvion1 += 1;
			}
			else {
				if (giroAvion2 >= 0.0) {
					giroAvion2 -= 1.0;
					giroAvion1 -= 0.6;
				}
			}
			if (movAvionX <= -850.0f && movAvionX >= -1100.0f) {
				if (giroAvion2 <= 45.0) {
					giroAvion2 += 1.0;
				}
			}
			if (movAvionX <= -2200.0f ) {
				AMov3 = true;
				AMov4 = false;
			}
		}
		else if (!AMov4) {
			giroHelice += 30.0;
			if (movAvionX >= -2282.0) {
				movAvionX -= 6;
			}
			if (movAvionZ >= 0.0) {
				if (movAvionZ <= 500.0) {
					movAvionZ -= 4.0;
				}
				else {
					movAvionZ = 500 * sin(movAvion2 / 100.0) + 826.045f;
					movAvion2 -= 1;
					giroAvion1 -= 1;
					giroAvion2 += 1;

				}
			
			}
			else {
				AMov4 = true;
				AMov5 = false;
				
			}
		}
		else if (!AMov5) {
			giroHelice += 30.0;
			if (movAvionX <= -1100.0) {
				if (movAvionX <= -2210.0) {
					movAvionZ = 500 * sin(movAvion3 / 100.0) + (-1.64734f);
					movAvion3 -= 1;
					giroAvion1 -= 1.5;
					movAvionX += 2;
				}
				else {
					movAvionX += 6;
					if (giroAvion1 >= -258 ) {
						giroAvion1 -= 1;
					}
					else if (giroAvion2 >= 0.0) {
						giroAvion2 -= 1;
					}
				}

			}
			else {
				AMov5 = true;
				AMov6 = false;
			}
		
		}
		else if (!AMov6) {
		giroHelice += 30.0;
			if (movAvionX <= -100.0) {
				if (movAvionX <= -700.0) {
					movAvionZ = 500 * sin(movAvion4 / 100.0) + (-187.108f);
					movAvion4 += 1;
					if (giroAvion1 <= -213.0) {
						giroAvion1 -= 1.0;
					}
					if (giroAvion2 <= 45.0) {
						giroAvion2 += 1.0;
					}
					movAvionX += 6;
				}
				else if (movAvionX <= -500.0 && movAvionX >= -800.0) {
					movAvionZ = 500 * sin(movAvion5 / 100.0) + (119.45f);
					movAvion5 += 1;
					if(giroAvion1 <= -250.0){
						giroAvion1 += 1.5;
					}
					if(giroAvion2 >= -45.0){
						giroAvion2 -= 2.0;
					}
					movAvionX += 6;
				}
				else if (movAvionX <= -56.0) {
					if (giroAvion2 <= 0.0) {
						giroAvion2 += 2.0f;
					}
					movAvionX += 6;
					movAvionY -= 3.7;
				}
		}
		else {
			AMov6 = true;
			AMov7 = false;
		}
		
		
		}
		else if (!AMov7) {
		animacionAvion = false;

		}



	}//end if animacion Avion
	
}

void reset()
{
	if (!animacionCarro)
	{
		//animacion = true;
		//variables del avion
		movAuto_z = -4000.0f;
		movAuto_x = 4000.0f;
		movAuto_y = 100.0f;
		giroAuto = 0.0f;

		//variables de cascanueces
		movBrazoCasca = 0.0f;
		movBocaCasca = -2.0f;
		movNuezY = -5.0f;
		movNuezX = -5.0f;
		movNuezZ = 0.0f;
		movNuezY2 = 0.0f;
		movNuezZ2 = 0.0f;
		movNuezY3 = 0.0f;
		movNuezZ3 = 0.0f;

	
		//variables booleanas de animacion
		conteoMov1 = false;
		conteoMov2 = true;
		conteoMov3 = true;
		conteoMov4 = true;
		conteoMov5 = true;
		conteoMov6 = true;
		conteoMov7 = true;
		conteoMov8 = true;
		conteoMov9 = true;
		conteoMov10 = true;

		//variable Avion
		AMov1 = false;
		AMov2 = true;
		AMov3 = true;
		AMov4 = true;
		AMov5 = true;
		AMov6 = true;
		AMov7 = true;
		AMov8 = true;
		AMov9 = true;
		AMov10 = true;

	}
}

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	//---------------------------------------------

	//--------------------------------------------------
	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------

	//Casa Completa junto con calle 
	Model Casa("resources/objects/CasaFinal/CasaCompleta.obj");
	//Carro
	Model Carro("resources/objects/Carro/CuerpoCarro.obj");
	Model Llanta("resources/objects/Carro/Llanta.obj");

	//Robot de juguete
	Model RobotCuerpo("resources/objects/Robot/TorzoRobot.obj");
	Model RobotCabeza("resources/objects/Robot/CabezaRobot.obj");
	Model RobotBrazoIzq("resources/objects/Robot/BrazoIzqRobot.obj");
	Model RobotAnteBrazoIzq("resources/objects/Robot/AnteBrazoIzqRobot.obj");
	Model RobotBrazoDer("resources/objects/Robot/BrazoDerRobot.obj");
	Model RobotAnteBrazoDer("resources/objects/Robot/AnteBrazoDerRobot.obj");
	Model RobotPiernaIzq("resources/objects/Robot/PiernaIzq.obj");
	Model RobotPieIzq("resources/objects/Robot/PieIzq.obj");
	Model RobotPiernaDer("resources/objects/Robot/PiernaDer.obj");
	Model RobotPieDer("resources/objects/Robot/PieDer.obj");

	//Persona
	Model PersonaCuerpo("resources/objects/Persona/TorzoM.obj");
	Model PersonaBrazoIzq("resources/objects/Persona/BrazoIzqM.obj");
	Model PersonaAnteBrazoIzq("resources/objects/Persona/AnteBrazoIzqM.obj");
	Model PersonaBrazoDer("resources/objects/Persona/BrazoDerM.obj");
	Model PersonaAnteBrazoDer("resources/objects/Persona/AnteBrazoDerM.obj");
	Model PersonaPiernaIzq("resources/objects/Persona/PiernaIzqM.obj");
	Model PersonaPiernaDer("resources/objects/Persona/PiernaDerM.obj");

	Model PersonaRegalo("resources/objects/Persona/Regalo.obj");

	//Avion de Juguete

	Model Avion("resources/objects/Avion/Avion.obj");
	Model Helice("resources/objects/Avion/Helice.obj");

	//Cascanueces
	Model CascaCuerpo("resources/objects/Cascanueces/CuerpoC.obj");
	Model CascaBoca("resources/objects/Cascanueces/BocaC.obj");
	Model CascaBrazoIzq("resources/objects/Cascanueces/BrazoIzqC.obj");
	Model CascaBrazoDer("resources/objects/Cascanueces/BrazoDerC.obj");
	Model CascaNuez("resources/objects/Cascanueces/Nuez.obj");

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].PosX = 0.0;
		KeyFrame[i].PosY = 0.0;
		KeyFrame[i].PosZ = 0.0;
		KeyFrame[i].Cabeza = 0.0;
		KeyFrame[i].BIzq = 0.0;
		KeyFrame[i].BDer = 0.0;
		KeyFrame[i].ABIzq = 0.0;
		KeyFrame[i].ABDer = 0.0;
		KeyFrame[i].PIzq = 0.0;
		KeyFrame[i].PDer = 0.0;
		KeyFrame[i].PieIzq = 0.0;
		KeyFrame[i].PieDer = 0.0;
		KeyFrame[i].Rota = 0.0;
	}

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);
		
		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		glm::mat4 tmp2 = glm::mat4(1.0f);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);


		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//casa del ecenario
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		Casa.Draw(staticShader);


		// -------------------------------------------------------------------------------------------------------------------------
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//orientacion del carro
		model = glm::translate(model, glm::vec3(movAuto_x, movAuto_y, movAuto_z));//tralacion para el carro
		tmp = model = glm::rotate(model, glm::radians(giroAuto), glm::vec3(0.0f, 1.0f, 0.0f));//
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		Carro.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(180.0f,-50.0f,-342.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Orientacion de las llantas
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));//girar las llantas
		model = glm::scale(model, glm::vec3(4.9f));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//Izq Tracera

		model = glm::translate(tmp, glm::vec3(180.0f, -50.0f, 405.0f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));//girar las llantas
		model = glm::scale(model, glm::vec3(4.9));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//Izq Delantera

		model = glm::translate(tmp, glm::vec3(-180.0f, -50.0f, -342.0f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));//girar las llantas
		model = glm::scale(model, glm::vec3(4.9));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//Der Trasera

		model = glm::translate(tmp, glm::vec3(-180.0f, -50.0f, 405.0f));
		model = glm::rotate(model, glm::radians(giroLlantas), glm::vec3(1.0f, 0.0f, 0.0f));//girar las llantas
		model = glm::scale(model, glm::vec3(4.9));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//Der Delantera


		// -------------------------------------------------------------------------------------------------------------------------
		// Avion
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//orientacion del avion
		model = glm::translate(model, glm::vec3(movAvionX,movAvionY,movAvionZ));//tralacion para el avion
		tmp = model = glm::rotate(model, glm::radians(giroAvion1), glm::vec3(0.0f, 1.0f, 0.0f));//
		tmp = model = glm::rotate(model, glm::radians(giroAvion2), glm::vec3(0.0f, 0.0f, 1.0f));//
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		Avion.Draw(staticShader);//Avion

		model = glm::translate(tmp, glm::vec3(-0.1f, 2.9f, 36.3f));
		model = glm::rotate(model, glm::radians(giroHelice), glm::vec3(0.0f, 0.0f, 1.0f));//giro de la helice
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		Helice.Draw(staticShader);	//Helice

		// -------------------------------------------------------------------------------------------------------------------------
		// Robot
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//orientacion del avion
		model = glm::translate(model, glm::vec3(10.0f + RPosX , 50.0f + RPosY, 1000.0f + RPosZ));//tralacion para el avion
		tmp = model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		RobotCuerpo.Draw(staticShader);//Robot

		model = glm::translate(tmp, glm::vec3(0.0f, 8.9f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(RCabeza), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		RobotCabeza.Draw(staticShader);	//Cabeza

		model = glm::translate(tmp, glm::vec3(12.0f, 6.4f, 2.2f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(RBIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		tmp2 = model;
		staticShader.setMat4("model", model);
		RobotBrazoDer.Draw(staticShader);	//Brazo Izq

		model = glm::translate(tmp2, glm::vec3(0.0f, -4.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f));
		model = glm::rotate(model, glm::radians(RABIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		RobotAnteBrazoDer.Draw(staticShader);	//AnteBrazo Izq

		model = glm::translate(tmp, glm::vec3(-12.0f, 6.4f, 2.2f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(RBDer), glm::vec3(1.0f, 0.0f, 0.0f));
		tmp2 = model;
		staticShader.setMat4("model", model);
		RobotBrazoIzq.Draw(staticShader);	//Brazo Der

		model = glm::translate(tmp2, glm::vec3(0.0f, -4.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f));
		model = glm::rotate(model, glm::radians(RABDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		RobotAnteBrazoIzq.Draw(staticShader);	//AnteBrazo Der

		model = glm::translate(tmp, glm::vec3(-7.0f, -13.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(RPIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		tmp2 = model;
		staticShader.setMat4("model", model);
		RobotPiernaDer.Draw(staticShader);	//Pierna Izq

		model = glm::translate(tmp2, glm::vec3(0.0f, -3.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f));
		model = glm::rotate(model, glm::radians(RPieIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		RobotPieIzq.Draw(staticShader);	//Pie Izq

		model = glm::translate(tmp, glm::vec3(7.0f, -13.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(RPDer), glm::vec3(1.0f, 0.0f, 0.0f));
		tmp2 = model;
		staticShader.setMat4("model", model);
		RobotPiernaDer.Draw(staticShader);	//Pierna Der

		model = glm::translate(tmp2, glm::vec3(0.0f, -3.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f));
		model = glm::rotate(model, glm::radians(RPieDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		RobotPieDer.Draw(staticShader);	//Pie Der

		// -------------------------------------------------------------------------------------------------------------------------
		// Persona 1
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//orientacion del avion
		model = glm::translate(model, glm::vec3(-500.0f + RPosX2, 275.0f + RPosY2, -100.0f+ RPosZ2));//tralacion para el avion
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//
		model = glm::rotate(model, glm::radians(rotaP2), glm::vec3(1.0f, 0.0f, 0.0f));//
		tmp = model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		PersonaCuerpo.Draw(staticShader);//Persona

		model = glm::translate(tmp, glm::vec3(-33.0f, -6.5f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		model = glm::rotate(model, glm::radians(RBIzq2), glm::vec3(1.0f, 0.0f, 0.0f));//
		tmp2 = model;
		staticShader.setMat4("model", model);
		PersonaBrazoDer.Draw(staticShader);	//Brazo Izq

		model = glm::translate(tmp2, glm::vec3(-2.15f, -8.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		model = glm::rotate(model, glm::radians(RABIzq2 - 15.0f), glm::vec3(1.0f, 0.0f, 0.0f));//
		staticShader.setMat4("model", model);
		PersonaAnteBrazoDer.Draw(staticShader);	//Ante Brazo Izq

		model = glm::translate(tmp2, glm::vec3(0.0f + RCabeza2, -25.0f + RPieIzq2, 0.0f + RPieDer2));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		PersonaRegalo.Draw(staticShader);	//Regalo 1

		model = glm::translate(tmp, glm::vec3(31.5f, -9.6f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		model = glm::rotate(model, glm::radians(RBDer2), glm::vec3(1.0f, 0.0f, 0.0f));//
		tmp2 = model;
		staticShader.setMat4("model", model);
		PersonaBrazoIzq.Draw(staticShader);	//Brazo Der

		model = glm::translate(tmp2, glm::vec3(2.0f, -7.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		model = glm::rotate(model, glm::radians(RABDer2 -15.0f), glm::vec3(1.0f, 0.0f, 0.0f));//
		staticShader.setMat4("model", model);
		PersonaAnteBrazoIzq.Draw(staticShader);	//Ante Brazo Der

		model = glm::translate(tmp, glm::vec3(-14.6f, -95.8f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		model = glm::rotate(model, glm::radians(RPIzq2), glm::vec3(1.0f, 0.0f, 0.0f));//
		staticShader.setMat4("model", model);
		PersonaPiernaDer.Draw(staticShader);	//Pierna Izq

		model = glm::translate(tmp, glm::vec3(12.0f, -95.8f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		model = glm::rotate(model, glm::radians(RPDer2), glm::vec3(1.0f, 0.0f, 0.0f));//
		staticShader.setMat4("model", model);
		PersonaPiernaIzq.Draw(staticShader);	//Pierna Der

		// -------------------------------------------------------------------------------------------------------------------------
		// Persona 2
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f , 1.0f , 0.0f));//orientacion del avion
		model = glm::translate(model, glm::vec3(-2000.0f, 275.0f, 600.0f));//tralacion para el avion
		tmp = model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));//
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		PersonaCuerpo.Draw(staticShader);//Persona

		model = glm::translate(tmp, glm::vec3(-33.0f, -6.5f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));//
		tmp2 = model;
		staticShader.setMat4("model", model);
		PersonaBrazoDer.Draw(staticShader);	//Brazo Izq

		model = glm::translate(tmp2, glm::vec3(-2.15f, -8.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f));//
		staticShader.setMat4("model", model);
		PersonaAnteBrazoDer.Draw(staticShader);	//Ante Brazo Izq

		model = glm::translate(tmp, glm::vec3(31.5f, -9.6f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));//
		tmp2 = model;
		staticShader.setMat4("model", model);
		PersonaBrazoIzq.Draw(staticShader);	//Brazo Der

		model = glm::translate(tmp2, glm::vec3(2.0f, -7.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f));//
		staticShader.setMat4("model", model);
		PersonaAnteBrazoIzq.Draw(staticShader);	//Ante Brazo Der

		model = glm::translate(tmp2, glm::vec3(0.0f, -25.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		staticShader.setMat4("model", model);
		PersonaRegalo.Draw(staticShader);	//Regalo 2

		model = glm::translate(tmp, glm::vec3(-14.6f, -95.8f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		PersonaPiernaDer.Draw(staticShader);	//Pierna Izq

		model = glm::translate(tmp, glm::vec3(12.0f, -95.8f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		PersonaPiernaIzq.Draw(staticShader);	//Pierna Der


		// -------------------------------------------------------------------------------------------------------------------------
		// Cascanueces
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//orientacion del avion
		model = glm::translate(model, glm::vec3(-2100.0f, 50.0f, 800.0f));//tralacion para el avion
		tmp = model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		CascaCuerpo.Draw(staticShader);//Cascanueces

		model = glm::translate(tmp, glm::vec3(-9.8f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(movBrazoCasca), glm::vec3(1.0f, 0.0f, 0.0f));//
		tmp2 = model;
		staticShader.setMat4("model", model);
		CascaBrazoIzq.Draw(staticShader);	//Brazo izq

		model = glm::translate(tmp2, glm::vec3(movNuezX, movNuezY, movNuezZ));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		CascaNuez.Draw(staticShader);	//Nuez

		model = glm::translate(tmp, glm::vec3(9.8f, 0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));//
		staticShader.setMat4("model", model);
		CascaBrazoDer.Draw(staticShader);	//Brazo Der

		model = glm::translate(tmp, glm::vec3(0.0f, movBocaCasca, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		staticShader.setMat4("model", model);
		CascaBoca.Draw(staticShader);	//Boca

		// -------------------------------------------------------------------------------------------------------------------------
		// Meza echa con cubos
		// -------------------------------------------------------------------------------------------------------------------------
		


		//--------------------------------------------------------------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	//----------------- movimiento de la camara ------------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//-------------------------------------------------------------------------------------------------------
	//

	//amimacion del carro
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		animacionCarro ^= true;
	}
	//animacion del cascanueces
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		animacionCasca ^= true;
	}
	// animacion del Avion
	if (key == GLFW_KEY_C && action == GLFW_PRESS){
		animacionAvion ^= true;
	}

	//reset animacion directa
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		reset();
	}

	//To play KeyFrame robot animation 
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		resetFrames();
		cargaframeRobot();
		FrameIndex = 13;
		if (play1 == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play1 = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play1 = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To play KeyFrame persona animation 
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		resetFrames();
		cargaframePersona();
		FrameIndex = 8;
		if (play2 == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play2 = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play2 = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
