#include <fstream>
#include <fstream>
#include <iostream>
#include <string>
#include "pgm_image.h"
using namespace std;

int main(int argc, char* argv[]){
	
	pgmImage image;
	cout << "Image operations are automatically written to open file." << endl;

	while(true){
		cout << "Enter a Command: " << endl;
		string cmd;
		getline(cin, cmd);

		if(cmd.compare("r") == 0){
			if(image.read_image()==0)
			cout << "Min: " << image.getMin() << " Max: " << image.getMax() << endl;
			cin.ignore();
		}
		else if(cmd.compare("w") == 0){
			string outFile;
			cout << "Enter File Name: " << endl;
			cin >> outFile;
			image.write_image(outFile);
			cin.ignore();
		}
		else if(cmd.compare("v") == 0){
			image.flipVert();
			image.write_image();
		}
		else if(cmd.compare("h") == 0){
			image.flipHorz();
			image.write_image();
		}
		else if(cmd.compare("neg") == 0){
			image.negative();
			image.write_image();
		}
		else if(cmd.compare("nor") == 0){
			image.normalize();
			image.write_image();
		}
		else if(cmd.compare("hor") == 0){
			image.hist_normalize();
			image.write_image();
		}
		else if(cmd.compare("en") == 0){
			cout << "Enter Mask Size: " << endl;
			int size;
			cin >> size;
			image.edge_normalize(size);
			image.write_image();
			cin.ignore();
		}
		else if(cmd.compare("b") == 0){
			cout << "Enter Size:" << endl;
			int size;
			cin >> size;
			image.blur(size);
			image.write_image();
			cin.ignore();
		}
		else if(cmd.compare("p") == 0){
			image.print_histogram();
		}
		else if(cmd.compare("sh") == 0){
			vector< vector<int> > kernel = {{0,-1,0},{-1,5,-1},{0,-1,0}};
			image.applyKernel(kernel);
			image.write_image();
		}
		else if(cmd.compare("ed") == 0){
			vector< vector<int> > kernel = {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
			image.applyKernel(kernel);
			image.write_image();
		}
		else if(cmd.compare("eb") == 0){
			vector< vector<int> > kernel = {{-2,-1,0},{-1,1,1},{0,1,2}};
			image.applyKernel(kernel);
			image.write_image();
		}
		else if(cmd.compare("pc") == 0){
			image.print_cuml_histogram();
		}
		else if(cmd.compare("un") == 0){
			image.undo();
			image.write_image();
		}
		else if(cmd.compare("?") == 0){
			cout << "Commands:" << endl;
			cout << "r   - read in new file" << endl;
			cout << "w   - write to new file" << endl;
			cout << "p   - print histogram" << endl;
			cout << "pc  - print cumulative histogram" << endl;
			cout << "v   - flip vertical" << endl;
			cout << "h   - flip horizontal" << endl;
			cout << "neg - negative" << endl;
			cout << "nor - normalize" << endl;
			cout << "hor - histogram normalize" << endl;
			cout << "en  - edge normalize" << endl;
			cout << "sh  - shapen" << endl;
			cout << "ed  - edge detect" << endl;
			cout << "eb  - emboss" << endl;
			cout << "un  - undo" << endl;
			cout << "q   - quit" << endl;
		}
		else if(cmd.compare("q") == 0){
			return 0;
		}
		else{
			cout << "Enter ? for Help" << endl;
		}
		cout << endl;
	}
}