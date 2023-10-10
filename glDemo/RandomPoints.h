#pragma once

#include "core.h"

// Model single point - attributes and memeber functions (methods) public by default for a structure (struct)
struct CGPoint {

	glm::vec2 position;
	glm::vec4 colour;
	float size;

	// Default constructor - zero everything out!
	CGPoint();
};

// Class to encapsulate storage, creation and rendering of a collection of random points
class RandomPoints {

	std::vector<CGPoint> points;

public:

	// Constructor.  numPoints specifies how main points to store
	RandomPoints(GLuint numPoints);

	// Render points
	void render();
	void renderTexturedPoints(GLuint texture);
};
