#include <windows.h>
#include <gl/glut.h>

int pontos = 0;
char placar[50] = "";

GLfloat movimentoNuvem = 10.0f;

GLfloat xPosArvore = 1.0f;

int randQuantidadeArvore1 = 1;
int randQuantidadeArvore2 = 2;
int randQuantidadeArvore3 = 3;

int velocidade = 15;


GLfloat yPosPersonagem = 0.0f;
GLfloat xPosPersonagem = -0.5f;
GLfloat movimento = 0.0f;
int direcao = 1;

GLfloat pulo = 0.0f;
int ativarPulo = 0;
int chao = 1;

int pause = -1;



void circulo(float r, float g, float b, int inicio, int fim)
{
	float pi = 3.14159265358979323846;
	glBegin(GL_POLYGON);
		glColor3f(r, g, b);
		for(int i = inicio; i <fim; i++)
		{
			float x = (float) cos(i*2*pi/100);
			float y = (float) sin(i*2*pi/100);
			glVertex2f(x, y);
		}
	glEnd();
}


void perna(GLfloat movi)												//INICIO DESENHO PERSONAGEM
{
	GLfloat aux;

	glPushMatrix();
	glBegin(GL_QUADS);											//perna
		glColor3f(0.87f, 0.82f, 0.78f);
		glVertex2f(xPosPersonagem-0.01, yPosPersonagem+0.04f);
		glVertex2f(xPosPersonagem, yPosPersonagem+0.04f);
																					//Movimenta só a parte de baixo do braço
		aux = xPosPersonagem;														//Grava a posição do personagem em um aux para poder voltar depois
		xPosPersonagem = xPosPersonagem + movi;										//Translata até a posição nova

		glVertex2f(xPosPersonagem, yPosPersonagem+0.01f);
		glVertex2f(xPosPersonagem-0.01, yPosPersonagem+0.01f);
	glEnd();

	glBegin(GL_QUADS);											//tenis
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(xPosPersonagem-0.01, yPosPersonagem);
		glVertex2f(xPosPersonagem-0.01, yPosPersonagem+0.01f);
		glVertex2f(xPosPersonagem+0.01, yPosPersonagem+0.01f);
		glVertex2f(xPosPersonagem+0.01, yPosPersonagem);

		xPosPersonagem = aux;														//Restaura a posição original
	glEnd();
	glPopMatrix();
}

void braco(GLfloat movi)
{
	GLfloat aux;

	glPushMatrix();
	glBegin(GL_QUADS);
		glColor3f(0.87f, 0.82f, 0.78f);
		glVertex2f(xPosPersonagem-0.01, yPosPersonagem+0.08f);
		glVertex2f(xPosPersonagem, yPosPersonagem+0.08f);
																					//Movimenta só a parte de baixo do braço
		aux = xPosPersonagem;														//Grava a posição do personagem em um aux para poder voltar depois
		xPosPersonagem = xPosPersonagem + movi;										//Translata até a posição nova

		glVertex2f(xPosPersonagem, yPosPersonagem+0.04f);
		glVertex2f(xPosPersonagem-0.01, yPosPersonagem+0.04f);

		xPosPersonagem = aux;														//Restaura a posição original
	glEnd();
	glPopMatrix();
}

void cabeca()
{
	glPushMatrix();																	//Cabeça
		glTranslatef(xPosPersonagem, yPosPersonagem+0.12, 0.0f);
		glScalef(0.02f, 0.02f, 0.0f);
		circulo(0.87f, 0.82f, 0.78f, 0, 100);
	glPopMatrix();

	glPushMatrix();																	//Olho
		glTranslatef(xPosPersonagem+0.01, yPosPersonagem+0.125, 0.0f);
		glScalef(0.003f, 0.003f, 0.0f);
		circulo(0.0f, 1.0f, 0.0f, 0, 100);
	glPopMatrix();
}

void personagem()
{
	glPushMatrix();
	glTranslatef(0.0f, pulo, 0.0f);

	braco(movimento*-1);													//Braço e perna esquerda || movimento inverso
	perna(movimento);

	glBegin(GL_QUADS);														//Corpo
		glColor3f(0.0f, 0.63f, 0.9f);
		glVertex2f(xPosPersonagem-0.02, yPosPersonagem+0.04);
		glVertex2f(xPosPersonagem-0.02, yPosPersonagem+0.1);
		glVertex2f(xPosPersonagem+0.02, yPosPersonagem+0.1);
		glVertex2f(xPosPersonagem+0.02, yPosPersonagem+0.04);
	glEnd();

	cabeca();

	perna(movimento*-1);													//Braço e perna direita	|| movimento inverso
	braco(movimento);

	glPopMatrix();
}																				//FIM DESENHO PERSONAGEM


void arvore(int quantidade_arvore, GLfloat posInicial)
{
	GLfloat posX = xPosArvore + posInicial;

	for(int qntd = 1; qntd <= quantidade_arvore; qntd++)						//Desenha uma sequencia de árvores passada por parâmetro
	{
		glBegin(GL_QUADS);						//Tronco
			glColor3f(0.72f, 0.47f, 0.33f);
			glVertex2f(posX-0.01f, 0.0f);
			glVertex2f(posX-0.01f, 0.08f);
			glVertex2f(posX+0.01f, 0.08f);
			glVertex2f(posX+0.01f, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);					//Folhas1
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(posX-0.05f, 0.06f);
			glVertex2f(posX, 0.12f);
			glVertex2f(posX+0.05f, 0.06f);
		glEnd();

		glBegin(GL_TRIANGLES);					//Folhas2
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(posX-0.04f, 0.08f);
			glVertex2f(posX, 0.14f);
			glVertex2f(posX+0.04f, 0.08f);
		glEnd();

		glBegin(GL_TRIANGLES);					//Folhas3
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(posX-0.02f, 0.12f);
			glVertex2f(posX, 0.16f);
			glVertex2f(posX+0.02f, 0.12f);
		glEnd();

		posX += 0.1;							//Posição das arvores
	}
}


void nuvem(GLfloat tx, GLfloat ty)
{
	GLfloat movi = movimentoNuvem + tx;			//Movimento da nuvem
	glPushMatrix();
		glScalef(0.15f,0.15f,0.0f);
		glColor3f(1.0f,1.0f,1.0f);
		glTranslatef(movi, ty, 0.0f);
		circulo(1.0f, 1.0f, 1.0f, 0, 100);
	glPopMatrix();
}


void cenario()
{
	glBegin(GL_QUADS);						//grama
		glColor3f(0.1f, 0.5f, 0.1f);
		glVertex2f(-2.0f, -1.0f);

		glColor3f(0.3f, 0.8f, 0.3f);
		glVertex2f(-2.0f, 0.0f);
		glVertex2f(2.0f, 0.0f);

		glColor3f(0.3f, 0.5f, 0.3f);
		glVertex2f(2.0f, -1.0f);
	glEnd();

	glPushMatrix();							//sol
		glScalef(0.2f, 0.2f, 0.2f);
		glTranslatef(4.0f, 4.0f, 0.0f);
		circulo(1.0f, 1.0f, 0.3f, 0, 100);
	glPopMatrix();

	glPushMatrix();
		nuvem(0.0,4.5);
		nuvem(1.5,4.5);
		nuvem(3.0,4.5);
	glPopMatrix();

	personagem();

	arvore(randQuantidadeArvore1,0);		//Sequências de arvores(qntdArvore, posinicial)
	arvore(randQuantidadeArvore2,1);
	arvore(randQuantidadeArvore3,2);

	arvore(randQuantidadeArvore1,3);
	arvore(randQuantidadeArvore2,5);
	arvore(randQuantidadeArvore3,4);
}


void DesenhaTexto(char *string, GLfloat xPos, GLfloat yPos)
{
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(xPos,yPos);

        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);

	glPopMatrix();
}


void desenha()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.95f,0.95f,0.95f,1.0f);
	cenario();
	DesenhaTexto(placar,-1.0f,0.85f);

	glFlush();
}


void Timer(int value)						//Move o cenário de acordo com um tempo
{
	if(pause < 0 && colisao() == 0)							//PAUSA O JOGO
	{
		xPosArvore -= 0.012f;					//Distância movida

		if(direcao == 1)						//Move os braços/pernas para frente
		{
			movimento += 0.003;					//Movimento de translação
			if(movimento > 0.02f)				//Limite do movimento
				direcao = -1;					//Ao chegar no limite inverte o processo
		}
		if(direcao == -1)						//Move os braços/pernas para tras
		{
			movimento -= 0.003;
			if(movimento < -0.02f)
					direcao = 1;
		}


		if(ativarPulo == 1)						//Controla o movimento para cima
		{
			chao = 0;
			pulo += 0.015f;						//Incrementa o movimento de translação do pulo
			if(pulo >= 0.35f)					//Ao chegar no limite, desativa o pulo
				ativarPulo = 0;
		}

		if(ativarPulo == 0 && pulo > 0.0f)		//Controla o movimento para baixo
			pulo -= 0.008f;

		if(pulo <= 0)							//Verifica se o personagem esta no chao para poder ativar o pulo
		{
			chao = 1;
			pulo = 0.0f;
		}

		movimentoNuvem -= 0.01f;
		if(movimentoNuvem < -12.0f)
		{
			movimentoNuvem = 10.0f;
		}

		if(xPosArvore < -6.4)					//Verifica se é o fim da sequência
		{
			xPosArvore = 1.0f;					//Zera as sequências de árvores e recomeça da posição inicial
			do									//Gera quantidades aleatórias de árvores para cada sequência
			{
				randQuantidadeArvore1 = rand()%5;
				randQuantidadeArvore2 = rand()%5;
				randQuantidadeArvore3 = rand()%5;
			}
			while(randQuantidadeArvore1 == 0 || randQuantidadeArvore2 == 0 || randQuantidadeArvore3 == 0);		//Evita sequências sem árvores
		}
		glutPostRedisplay();
		sprintf(placar, "%d", pontos);
		pontos = pontos + 1;
	}										//FIM PAUSE

    glutTimerFunc(velocidade,Timer, 1);		//Tempo de movimento do cenário
}



int colisao()
{
	int resultado = 0;							//0 = sem colisão

	if(pulo <= 0.08f )
	{
		if(xPosPersonagem >= xPosArvore-0.05 && xPosPersonagem <= xPosArvore+(randQuantidadeArvore1*0.1) +0.01)	//0.5 = tamanho da arvore para os lados
		{resultado = 1;}
		if(xPosPersonagem >= xPosArvore+1-0.05 && xPosPersonagem <= (xPosArvore+1)+(randQuantidadeArvore2*0.1) +0.01)
		{resultado = 1;}
		if(xPosPersonagem >= xPosArvore+2-0.05 && xPosPersonagem <= (xPosArvore+2)+(randQuantidadeArvore3*0.1) +0.01)
		{resultado = 1;}
		if(xPosPersonagem >= xPosArvore+3-0.05 && xPosPersonagem <= (xPosArvore+3)+(randQuantidadeArvore1*0.1) +0.01)
		{resultado = 1;}
		if(xPosPersonagem >= xPosArvore+5-0.05 && xPosPersonagem <= (xPosArvore+5)+(randQuantidadeArvore2*0.1) +0.01)
		{resultado = 1;}
		if(xPosPersonagem >= xPosArvore+4-0.05 && xPosPersonagem <= (xPosArvore+4)+(randQuantidadeArvore3*0.1) +0.01)
		{resultado = 1;}
	}

	return resultado;
}



void TeclasEspeciais(int key)
{
    if(key == GLUT_KEY_UP)						//Controla o movimento para cima
    {
    	if(chao == 1)							//Só permite pular se o personagem estiver no chao
    		ativarPulo = 1;
    }
    if(key == GLUT_KEY_DOWN)
    {
    	ativarPulo = 0;
    	if(ativarPulo == 0 && pulo > 0.0f)		//Controla o movimento para baixo
    		pulo -= 0.05f;
    }
    glutPostRedisplay();
}


void GerenciaTeclado(unsigned char key)
{
    switch (key) {
            case 'R':
            case 'r':					// Reinicia o jogo com outra sequência
            	xPosArvore = -6.4f;
            	if(pause == 1)
            		pause = pause * -1;

            	pulo = 0;
            	ativarPulo = 0;
            	chao = 1;
            	pontos = 0;
            	movimentoNuvem = 10.0f;
            break;
            case 'P':
            case 'p':					// Pausa o jogo
            	pause = pause * -1;
            break;
            case 27:					//Fecha o jogo
            	glutDestroyWindow(0);
            	exit(0);
            break;
    }
    glutPostRedisplay();
}


void funcaomenu(int item)						//Função para o menu do botão direito do mouse
{
 switch (item)
 {
 	 case 1:
 		GerenciaTeclado('P');
 	 break;
 	 case 2:
 		GerenciaTeclado('R');
 	 break;
 	 case 3:
 		GerenciaTeclado(27);					//27 = Tecla ESC
 	 break;
 }
 glutPostRedisplay();
 return;
}


int main(int argc, char** argv)
{
	 glutInit(&argc, argv);
     glutCreateWindow("SINTO O CHEIRO DE TRETA");
     glutInitWindowSize(800,800);
     glutInitWindowPosition(100,100);
     glutDisplayFunc(desenha);
     glutSpecialFunc(TeclasEspeciais);
     glutKeyboardFunc(GerenciaTeclado);
     glutTimerFunc(33, Timer, 1);

     glutCreateMenu(funcaomenu);
     glutAddMenuEntry("Pausar/iniciar o Jogo", 1);
     glutAddMenuEntry("Reiniciar o Jogo", 2);
     glutAddMenuEntry("Fechar o Jogo", 3);
     glutAttachMenu(GLUT_RIGHT_BUTTON);

     glutMainLoop();
     return(0);
}
