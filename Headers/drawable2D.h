#ifndef DRAWABLE2D_H
#define DRAWABLE2D_H

#include <shader.h>	
#include <color.h>
#include <vector.h>
#include <memory>

// Base class for all 2D drawings

class Drawable2D {
protected:

	std::shared_ptr<Shader> shader; //Shader with soft pointer

	Color color; // Base color
	Vec2 position; // Position. This will have effect on visual output
	Vec2 origin; // TO DO: We need origin to rotate.

	std::unique_ptr<float[]> vertices; // pointer to vertices
	std::unique_ptr<unsigned int[]> indices; // pointer to indices

	unsigned int VBO; // Vertex buffer object
	unsigned int VAO; // Vertex Attribute object
 	unsigned int EBO; // Element buffer object
 
	Drawable2D(); // Default constructor
	Drawable2D(Drawable2D& copy); // Copy constructor
	virtual ~Drawable2D(); // Destructor

	//Assignment operator overload
	Drawable2D& operator=(const Drawable2D& other);
	virtual void ApplyChanges() = 0; // You must override this! This function need to change vertex buffer if needed.

public:
	//Overrided Render method.
	virtual void Render() = 0; 
	//Set color
	void SetColor(const Color& color); 
	//Set origin * Will also call ApplyChanges() *
	void SetOrigin(const Vec2& origin); 
	//Set position * Will also call ApplyChanges() *
	void SetPosition(const Vec2& position); 
	//Add to position * Will also call ApplyChanges() *
	void Move(const Vec2& movement); 
	
};

#endif // !DRAWABLE2D_H
