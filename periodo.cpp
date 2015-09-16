#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;


void displayVector(vector<float> oneDVector, int index) {
	for (int i=0; i<index; i++)
		cout << "Vector [" << i << "]: " << oneDVector[i]
			     << endl;
} 


void showNestedVector(vector<vector<float> > nestedVect) {
	for (int i=0; i<nestedVect.size(); i++) {
		for (int j=0; j<nestedVect[i].size(); j++) {
			cout << "Vector [" << i << "," << j
			     << "]: " << nestedVect[i][j]
			     << endl;
		}
	}
}		


float sum1DVector(vector<float> oneDVector, int index) {
	float container = 0.0;
	for (int i=0; i<index; i++)
		container += oneDVector[i];
	return container;
}


float sumWxH(vector<float> W, vector<float> H) {
	float container = 0.0;
	for (int i=0; i<W.size(); i++) 
		container += (W[i] * H[i]);
	return container;
}


vector<float> 
Moment(vector<float> weight, vector<float> lenght, int index) {
	vector<float> container;
	for (int i=0; i<weight.size(); i++) {
		if (i==0)
			container.push_back(weight[i] * lenght[i]);
		else
			container.push_back(container[i-1] +
				           sum1DVector(weight, i+1) *
				           lenght[i]); 
	}
	return container;
}


vector<float>
RAT(vector<float> moments, vector<float> MInertia, int index) {
	vector<float> container;
	for (int i=0; i<index; i++)
		container.push_back(moments[i] * 1000 / MInertia[i]);
	return container;
}


vector<float>
S(vector<float> RAT, vector<float> lenght, int index) {
	vector<float> container;
	for (int i=0; i<index; i++) {
		if (i == 0)
			container.push_back(RAT[i]*lenght[i] / 2.0);
		else
			container.push_back((RAT[i] + RAT[i-1]) *
					    lenght[i] / 2.0);
	}
	return container;
}


vector<float>
SumS(vector<float> SVector, int index) {
	vector<float> container;
	int indexVect;
	for (int i=index; i>=0; i--) {
		if (i == index)
			container.push_back(SVector[i]);
		else if (i == index - 1)
			container.push_back(SVector[i] + SVector[i-1]);
		else
			indexVect = container.size();
			container.push_back(SVector[i] +
					    container[indexVect]);
		}
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
	int qty;
	float sumW, prodWxH, height;
	vector<vector<float> > matrix;

	matrix = readMatrix();
	qty = matrix[0][0];
	
	vector<float> weights, lenghts, MInertia;
	weights = matrix[1];
	lenghts = matrix[2];
	MInertia = matrix[3];

			
	vector<float> SMoments;
	SMoments = Moment(weights, lenghts, qty);

	vector<float> SRAT;
	SRAT = RAT(SMoments, MInertia, qty);


	vector<float> SS;
	SS = S(SRAT, lenghts, qty);

	
	vector<float> SSS;
	SSS = SumS(SS, qty);


	displayVector(SSS, qty);

	cout << matrix[0][0] << endl;
	
	
	sumW = sum1DVector(weights, qty);

	return 0;
}


