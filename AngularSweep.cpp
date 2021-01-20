#include <bits/stdc++.h> 
using namespace std; 

const int MAX_POINTS = 500; 
typedef complex<double> Point; 

Point arr[MAX_POINTS]; 
double dis[MAX_POINTS][MAX_POINTS]; 

bool mycompare(pair<double,bool> A, pair<double,bool> B){ 
	if(A.first<B.first) 
		return true; 
	else if(A.first>B.first) 
		return false; 
	else
		return (A.second==1); 
} 
int getPointsInside(int i, double r, int n){ 
	// This vector stores alpha and beta and flag 
	// is marked true for alpha and false for beta 
	vector<pair<double, bool> > angles; 
	

	for (int j=0; j<n; j++) 
	{ 
		if (i != j && dis[i][j] <= 2*r) 
		{ 
			// acos returns the arc cosine of the complex 
			// used for cosine inverse 
			double B = acos(dis[i][j]/(2*r)); 

			// arg returns the phase angle of the complex 
			double A = arg(arr[j]-arr[i]); 
			double alpha = A-B; 
			double beta = A+B; 
			angles.push_back(make_pair(alpha, true)); 
			angles.push_back(make_pair(beta, false)); 
		} 
	} 

	// angles vector is sorted and traversed 
	sort(angles.begin(), angles.end(), mycompare); 

	// count maintains the number of points inside 
	// the circle at certain value of theta 
	// res maintains the maximum of all count 
	int count = 1, res = 1; 
	vector<pair<double, bool> >::iterator it; 
	for (it=angles.begin(); it!=angles.end(); ++it) 
	{ 
		// entry angle 
		if ((*it).second) 
			count++; 

		// exit angle 
		else
			count--; 

		if (count > res) 
			res = count; 
	} 

	return res; 
} 

// Returns count of maximum points that can lie 
// in a circle of radius r. 
int maxPoints(Point arr[], int n, int r) 
{ 
	// dis array stores the distance between every 
	// pair of points 
	for (int i=0; i<n-1; i++) 
		for (int j=i+1; j<n; j++) 

			// abs gives the magnitude of the complex 
			// number and hence the distance between 
			// i and j 
			dis[i][j] = dis[j][i] = abs(arr[i]-arr[j]); 

	// This loop picks a point p 
	int ans = 0; 
	for (int i=0; i<n; i++) 

		// maximum number of points for point arr[i] 
		ans = max(ans, getPointsInside(i, r, n)); 

	return ans; 
} 

// Driver code 
int main() 
{ 
	Point arr[] = {Point(-15,12),Point(-10,7),Point(-989,-3),Point(-2,4),Point(-4,-4),
					Point(4,-5),Point(200,8),Point(4,12),Point(6,13),Point(1,6),Point(3,7),
					Point(5,81),Point(200,800),Point(412,122),Point(16,13),Point(11,6),Point(31,71),
					Point(50,181)}; 
	int r = 10; 

	int n = sizeof(arr)/sizeof(arr[0]); 

	cout << "The maximum number of points are: "
		<< maxPoints(arr, n, r); 

	return 0; 
} 

