
#include "RandomPoints.h"

using namespace std;

//
// CGPoint implementation
//

// Default constructor - zero everything out!
CGPoint::CGPoint() {

	position = glm::vec2(0.0f, 0.0f);
	colour = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	size = 0.0f;
}


//
// RandomPoints implementation
//

// Constructor.  numPoints specifies how main points to store
RandomPoints::RandomPoints(GLuint numPoints) {

	points = vector<CGPoint>(numPoints, CGPoint());

	random_device rd;
	mt19937 randomEngine = mt19937(rd());
	uniform_real_distribution<float> posRange = uniform_real_distribution<float>(-1.0f, 1.0f);
	uniform_real_distribution<float> colourRange = uniform_real_distribution<float>(0.0f, 1.0f);
	uniform_real_distribution<float> sizeRange = uniform_real_distribution<float>(1.0f, 500.0f);

	for (GLuint i = 0; i < numPoints; i++) {

		float x = posRange(randomEngine);
		float y = posRange(randomEngine);

		points[i].position = glm::vec2(x, y);

		float r = colourRange(randomEngine);
		float g = colourRange(randomEngine);
		float b = colourRange(randomEngine);

		points[i].colour = glm::vec4(r, g, b, 1.0f);

		points[i].size = sizeRange(randomEngine);
	}
}

void RandomPoints::render() {

	for (int i = 0; i < points.size(); i++) {

		glPointSize(points[i].size);

		// Unfortunately we have to begin-end on every single point since state changes (point size) must occur outside this block :(
		glBegin(GL_POINTS);

		glColor4f(points[i].colour.r,
			points[i].colour.g,
			points[i].colour.b,
			points[i].colour.a);

		glVertex2f(points[i].position.x, points[i].position.y);

		glEnd();
	}
}

void RandomPoints::renderTexturedPoints(GLuint texture) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SPRITE);

	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < points.size(); i++) {

		glPointSize(points[i].size);

		// Unfortunately we have to begin-end on every single point since state changes (point size) must occur outside this block :(
		glBegin(GL_POINTS);

		glColor4f(points[i].colour.r,
			points[i].colour.g,
			points[i].colour.b,
			points[i].colour.a);

		glVertex2f(points[i].position.x, points[i].position.y);

		glEnd();
	}

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_TEXTURE_2D);
}
