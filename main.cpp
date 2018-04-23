#include <fstream>
#include <fstream>
#include <iostream>
#include <string>
#include "pgm_image.h"
using namespace std;

int main(int argc, char* argv[]){
	
	pgmImage image;

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
			image.edge_normalize();
			image.write_image();
		}
		else if(cmd.compare("b") == 0){
			cout << "Enter Size:" << endl;
			int size;
			cin >> size;
			image.blur(size);
			image.write_image();
		}
		else if(cmd.compare("p") == 0){
			image.print_histogram();
		}
		else if(cmd.compare("pc") == 0){
			image.print_cuml_histogram();
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