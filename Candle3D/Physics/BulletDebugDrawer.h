#pragma once

#include <Bullet\btBulletDynamicsCommon.h>
#include <glm\glm.hpp>
#include <GL\glew.h>

class BulletDebugDrawer: public btIDebugDraw{
public:
	void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix){
		glUseProgram(0); // Use Fixed-function pipeline (no shaders)
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&pViewMatrix[0][0]);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(&pProjectionMatrix[0][0]);
	}
	virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color){
		glLineWidth(1.0f);
		glColor3f(color.x(), color.y(), color.z());
		glBegin(GL_LINES);
			glVertex3f(from.x(), from.y(), from.z());
			glVertex3f(to.x(), to.y(), to.z());
		glEnd();
	}
	virtual void drawContactPoint(const btVector3 &,const btVector3 &,btScalar,int,const btVector3 &){}
	virtual void reportErrorWarning(const char *){}
	virtual void draw3dText(const btVector3 &,const char *){}
	virtual void setDebugMode(int p){
		m = p;
	}
	int getDebugMode(void) const {return 3;}
	int m;
};