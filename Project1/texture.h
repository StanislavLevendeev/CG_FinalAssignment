#include <string>
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// Load a .BMP file using our custom loader
GLuint loadBMP(const char * imagepath);

//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
//// or do it yourself (just like loadBMP_custom and loadDDS)
//// Load a .TGA file using GLFW's own loader
//GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

class Texture
{	
private:
	GLuint rendererID;
	std::string filePath;
	int width, height, BPP;
	//unsigned char* localBuffer;
public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetBPP() const { return BPP; }
	inline GLuint GetID() const { return rendererID; }
	inline std::string GetPath() const { return filePath; }
	//inline unsigned char* GetLocalBuffer() const { return localBuffer; }

};


#endif