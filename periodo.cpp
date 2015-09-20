#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <cmath>

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


float sumVectMult
(vector<float> Vect1, vector<float> Vect2, float factor, int index) {
	float container = 0.0;
	for (int i=0; i<index; i++) 
		container += (Vect1[i] * Vect2[i] * factor);
	return container;
}


float sumVectMult2
(vector<float> Vect1, vector<float> Vect2, float factor, int index) {
	float container = 0.0;
	for (int i=0; i<index; i++)
		container += (Vect1[i] * factor * pow(Vect2[i], 2.0));
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
	for (int i=index-1; i>=0; i--) {
		if (i == index - 1) 
			container.push_back(SVector[i]); 
		else if (i == index - 2) 
			container.push_back(SVector[i+1] + SVector[i]);
		else {
			indexVect = container.size()-1;
			container.push_back(SVector[i] +
					    container[indexVect]); }
	}
	return container;
}	


vector<float>
SumP(vector<float> SSVector, vector<float> lenght,  int index) {
	vector<float> container;
	for (int i=0; i<index; i++)
		container.push_back((SSVector[i] + SSVector[i+1]) *
				     lenght[i] / 2.0);
	return container;
}


vector<float>
SumF(vector<float> SumP, int index) {
	vector<float> container;
	int indexVect;
	for (int i=index-1; i>=0; i--) {
		if(i == index-1)
			container.push_back(SumP[i]);
		else if (i == index-2)
			container.push_back(SumP[i] + SumP[i+1]);
		else {
			indexVect = container.size() - 1;
			container.push_back(SumP[i] +
					    container[indexVect]); }
	}
	return container;
}


vector<float>
SumY(vector<float> SumF, int index, float E) {
	vector<float> container;
	for (int i=0; i<index; i++)
		container.push_back(SumF[i] * 12 / (144.0 * E));
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

	const double pi = atan(1.0)*4.0;
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
	reverse(SSS.begin(), SSS.end());
	
	
	vector<float> sP;
	sP = SumP(SSS, lenghts, qty);
	

	vector<float> sF;
	sF = SumF(sP, qty);
	reverse(sF.begin(), sF.end());

	
	vector<float> sY;
	sY = SumY(sF, qty, 3e7);

	float SWY, SWY2;
	SWY = sumVectMult(weights, sY, 1000, qty);
	SWY2 = sumVectMult2(weights, sY, 1000, qty);

	// displayVector(sY, qty);
	// cout << "SWY = " << SWY << endl;
	// cout << "SWY2 = " << SWY2 << endl;
	
	float T;
	T= 2.0 * pi * sqrt(SWY2 / (386.4 * SWY));

	cout << T << endl;

	
	// sumW = sum1DVector(weights, qty);

	return 0;
}


