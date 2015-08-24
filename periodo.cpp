#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;


void showNestedVector(vector<vector<float> > nestedVect) {
	for (int i=0; i<nestedVect.size(); i++) {
		for (int j=0; j<nestedVect[i].size(); j++) {
			cout << "Vector [" << i << "," << j
			     << "]: " << nestedVect[i][j]
			     << endl;
		}
	}
}		


float sum1DVector(vector<float> oneDVector) {
	float container = 0.0;
	for (int i=0; i<oneDVector.size(); i++)
		container += oneDVector[i];
	return container;
}


float sumWxH(vector<float> W, vector<float> H) {
	float container = 0.0;
	for (int i=0; i<W.size(); i++) 
		container += (W[i] * H[i]);
	return container;
}


vector<vector<float> > readMatrix() {
	string filename = "data.txt";
	string line;
	float value;
	vector<float> container;
	vector<vector<float> > matrix;

	ifstream infile(filename.c_str(), ios_base::in);
	
	if (!infile) {
		cout << "No se encontro el archivo data.txt." << endl;
		exit(1);
	}

	while (!infile.eof()) {
		getline(infile, line);
		istringstream iss(line);
		while (iss >> value)
			container.push_back(value);
		matrix.push_back(container);
		container.clear();
	}

	//showNestedVector(matrix);
	return matrix;
}


int main() {
	float sumW, prodWxH;
	vector<vector<float> > matrix;

	matrix = readMatrix();
	sumW = sum1DVector(matrix[0]);
	prodWxH = sumWxH(matrix[0], matrix[1]);

	cout << "La altura del centro de masa es: "
	     << prodWxH / sumW << endl;

	return 0;
}


