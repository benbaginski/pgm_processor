#ifndef PGM_H
#define PGM_H
#include <string>
#include <vector>
#include <istream>
#include <fstream>
#include <map>

class pgmImage{

private:
	std::string name;
	std::string fileName;
	std::string header;

	int width;
	int height;
	int minI;
	int maxI;

	int range;

	std::vector< std::vector<int> > image;
	std::map<int, long> histogram;
	std::map<int, long> cuml_histogram;

public:
	//Constructors
	pgmImage();

	//File Operations
	int read_image();
	int write_image();
	int write_image(std::string outFile);

	//Histogram
	void calculate_histogram();
	void print_histogram();
	void print_cuml_histogram();

	//Statistical Operations
	double get_mean(int x, int y, int range=1);
	double get_stddev(int x, int y, int range=1);
	int readMin();
	int readMax();

	//Image Flip/Rotate
	void flipVert();
	void flipHorz();
	void rotateLeft();
	void rotateRight();

	//Image Manipulation
	void normalize();
	void hist_normalize();
	void edge_normalize(int range=1);
	void blur(int range=1);
	void negative();


	//Setters
	void setName(std::string n){name=n;};

	//Getters
	int getWidth(){return width;};
	int getHeight(){return height;};
	double getMax(){return maxI;};
	double getMin(){return minI;};
	std::string getName(){return name;};
	int getPixel(int x, int y){return image[x][y];};
};


#endif // PGM_H
