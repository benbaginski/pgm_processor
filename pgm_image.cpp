#include <algorithm>
#include <cmath>
#include <iostream>
#include <istream>
#include <sstream>
#include "pgm_image.h"
using namespace std;

pgmImage::pgmImage(){}

//File Operations
int pgmImage::read_image(){
	
	string inFile;

	cout << "Enter File to Open: " << endl;
	cin >> inFile;

	//Open File
	ifstream istr(inFile);
	if(istr.fail()){
		cout << "Unable To Open Image." << endl;
		return -1;
	}

	fileName = inFile;

	//Read Headers
	getline(istr, header);
	getline(istr, name);
	istr >> width >> height;
	istr >> range;

	image.resize(height);
	for(auto& i : image){
		i.resize(width);
	}

	//Read Image Data
	for(auto& h : image){
		for(auto& w : h){
			int pixel;
			istr >> pixel;
			w = pixel;
		}
	}
	
	calculate_histogram();

	return 0;
}

int pgmImage::write_image(){

	ofstream ofstr(fileName);
	if(ofstr.fail()){
		cout << "Unable to Write Image." << endl;
		return -1;
	}

	//Write Headers
	ofstr << header << endl;
	ofstr << name << endl;
	ofstr << width << " " << height << endl;
	ofstr << range << endl << endl;
	
	//Write Image
	for(auto h : image){
		for(auto w: h){
			ofstr << w << " ";
		}
		ofstr << endl;
	}

	return 0;
}

int pgmImage::write_image(string outFile){

	ofstream ofstr(outFile);
	if(ofstr.fail()){
		cout << "Unable to Write Image." << endl;
		return -1;
	}

	fileName = outFile;

	//Write Headers
	ofstr << header << endl;
	ofstr << name << endl;
	ofstr << width << " " << height << endl;
	ofstr << range << endl << endl;
	
	//Write Image
	for(auto h : image){
		for(auto w: h){
			ofstr << w << " ";
		}
		ofstr << endl;
	}

	return 0;
}

void pgmImage::undo(){
	vector< vector<int> > temp;
	temp = image;
	image = last_image;
	last_image = temp;
	calculate_histogram();
}

//Image Histogram
void pgmImage::calculate_histogram(){
	for(int i = 0; i <= 255; i++){
		histogram[i] = 0;
		cuml_histogram[i] = 0;
	}

	for(auto h : image){
		for(auto w : h){
			histogram[w]++;
		}
	}
	cuml_histogram[0] = histogram[0];
	for(int i = 1; i <= 255; i++){
		cuml_histogram[i] = histogram[i] + cuml_histogram[i-1];
	}

	maxI = readMax();
	minI = readMin();
}

void pgmImage::print_histogram(){
	for(const auto m : histogram){
		cout << m.first << " " << m.second << endl;
	}
}

void pgmImage::print_cuml_histogram(){
	for(const auto m : cuml_histogram){
		cout << m.first << " " << m.second << endl;
	}
}

//Image Statistics
double pgmImage::get_mean(int x, int y, int range){
	double mean = 0.0;
	double window_size = 0.0;

	for(int h = y-range; h <= y+range; h++){
		for(int w = x-range; w <= x+range; w++){
			if(w>=0 && w < width && h>=0 && h<height){
				mean = image[h][w] + mean;
				window_size++;
			}
		}
	}
	return mean/window_size;
}

double pgmImage::get_stddev(int x, int y, int range){
	double mean = get_mean(x, y, range);
	double stddev = 0.0;
	double window_size = 0.0;

	for(int h = y-range; h <= y+range; h++){
		for(int w = x-range; w <= x+range; w++){
			if(w>=0 && w < width && h>=0 && h<height){
				stddev = pow((image[h][w]-mean), 2) + stddev;
				window_size++;
			}
		}
	}
	return sqrt((1/(window_size-1)*(stddev)));
}

int pgmImage::readMin(){
	for(int i = 0; i <= 255; i++){
		if(histogram[i] != 0) return i;
	}
	return 0;
}

int pgmImage::readMax(){
	for(int i = 255; i >= 0; i--){
		if(histogram[i] != 0) return i;
	}
	return 255;
}

//Image Transforms
void pgmImage::flipVert(){
	last_image = image;
	reverse(image.begin(), image.end());
}

void pgmImage::flipHorz(){
	last_image = image;
	for(auto& row : image){
		reverse(row.begin(), row.end());
	}
}

void pgmImage::rotateRight(){
	//Todo
}

void pgmImage::rotateLeft(){
	//Todo
}

//Image Filters
void pgmImage::normalize(){
	last_image = image;

	double mi = getMin();
	double ma = getMax();
	for(auto& row : image){
		for(auto& pixel : row){
			pixel = ( (pixel - mi) * ( 255 / (ma - mi) ) );
		}
	}
	calculate_histogram();
}

void pgmImage::hist_normalize(){
	last_image = image;
	double mi = getMin();
	for(auto& row : image){
		for(auto& pixel : row){
			pixel = ((cuml_histogram[pixel] - mi) / ((width*height)-1))*255;
			pixel = min(255,max(0, pixel));
		}
	}
	calculate_histogram();
}

void pgmImage::edge_normalize(int range){
	last_image = image;	
	vector< vector<int> > edge = image;

	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			int pixel = image[h][w] - (get_mean(w, h, range)/get_stddev(w, h, range));
			pixel = min(255,max(0, pixel));
			edge[h][w] = pixel; 
		}
	}
	image = edge;
	calculate_histogram();
}

void pgmImage::negative(){
	last_image = image;
	for(auto& row : image){
		for(auto& pixel : row){
			pixel = abs(pixel-range);
		}
	}
	calculate_histogram();
}

void pgmImage::blur(int range){
	last_image = image;	
	vector< vector<int> > edge = image;

	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			edge[h][w] = get_mean(w, h, range);
		}
	}

	image = edge;
	calculate_histogram();
}

//Image Kernels
void pgmImage::applyKernel(vector< vector<int> > kernel){
	last_image = image;	
	vector< vector<int> > tmp = image;
	int maskRange = (kernel.size()-1)/2;

	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			int newValue = 0;

			for(int y = 0; y < (int)kernel.size(); y++){
				for(int x = 0; x < (int)kernel.size(); x++){
					int kern = kernel[y][x];
					int hI = min(height - 1, max(0, h - y - maskRange));
					int wI = min(width  - 1, max(0, w - x - maskRange));
					newValue = newValue + kern * image[hI][wI];
				}
			}
			tmp[h][w] = max(0,min(255,newValue));
		}
	}
	image = tmp;
	calculate_histogram();	
}