/*
Application of Dijkstra Algorithm
for solving Shortest Path Problem
 */

#include <iostream>

using namespace std;

//	Global Variable Declaration
float matrix[10][10];

void build_matrix(int vertice);
void print_path(int par[], int child);
float dijkstra(int vertice);

// procedure to build matrix of distance
void build_matrix (int vertice) {

//	Local Variable Declaration
	int i, j;
	cout<<"- Input matrix of distance between vertices (input 999 if there's no edge between them) -";
	cout<<endl;
	for (i = 0; i < vertice; i++) {
		for (j = 0; j < vertice; j++) {
			if (i != j) {
				do {
					cout<<"# length between node ["<<i+1<<"] and node ["<<j+1<<"] : ";
					cin>>matrix[i][j];
				} while (matrix[i][j] < 0);    // Ensuring repetition if user input a negative number
			}
			else if (i == j) {
				matrix[i][j] = 999;    // all diagonal entries are set to 0
			}
		}
		cout<<endl;
	}

}

void print_path(int par[], int child) {
	int i, j;

	i = child;
	cout<<endl<<"- The path are : "<<endl;
	cout<<"end <- "<<child<<" <- ";
	while (i != 0) {
		cout<<par[i];
		if (par[i] != 0) {
			cout<<" <- ";
		} else {
			cout<<" <- begin";
		}
		i = par[i];
	}
	cout<<endl;
}

float dijkstra (int vertice) {

// Local Variable Declaration
	int i, j, i_visit[9], unvisit[10], num_unvisit = 10, num_visit = 0, current, S[10];
	float dist[10], ndist[10], least, alt, distance;
	int curr, parent[10], iteration = 0;

// main program
	for (i = 0; i < vertice; i++) {
		dist[i] = 999;    // set other distance to all other nodes to 999 (infinity)
		ndist[i] = dist[i];    // set intial new dist equals to dist
		unvisit[i] = i;    // add all vertices to unvisited array
		S[i] = 0;    // set all entries in S to be 0 since no vertice is visited yet
	}
	dist[0] = 0;    // set distance to inital node to 0
	while (num_unvisit != 0) {
		if (iteration < 2 or num_unvisit < 2) {
			cout<<endl<<"| Iteration - "<<iteration<<" |"<<endl;
		}
		least = dist[unvisit[0]];
		current = unvisit[0];
		curr = 0;
		// check the minimum distance from array unvisit
		for (i = 0; i < num_unvisit; i++) {
			if (dist[unvisit[i]] < least) {    // check is there any minimum distance than least
				least = dist[unvisit[i]];    // if it exist, assign least to that distance
				current = unvisit[i];
				curr = i;
				i = 0;    // set 'i' to 0 for double check the current least distance
			}
		}
		if (iteration < 2 or num_unvisit < 2) {
			cout<<"- Minimum value : "<<least<<endl;
			cout<<"- On node : "<<current<<endl;
		}
		// remove unvisit[i] from unvisit array
		// by forwarding entries and minus the array by 1
		num_unvisit--;
		for (i = curr; i < num_unvisit; i++) {
			unvisit[i] = unvisit[i+1];
		}
		// display unvisit array
		if (iteration < 2 or num_unvisit < 2) {
			cout<<endl<<"- Matrix unvisit : "<<endl;
			for (i = 0; i < num_unvisit; i++) {
				cout<<unvisit[i]<<" ";
			}
			cout<<endl;
		}
		// add the visited vertice to S array
		// by adding the num_visit by 1
		S[num_visit] = current;
		num_visit++;
		// display visited array
		if (iteration < 2 or num_unvisit < 2) {
			cout<<"- Matrix visit : "<<endl;
			for (i = 0; i < num_visit; i++) {
				cout<<S[i]<<" ";
			}
			cout<<endl;
		}
		// determine new possible distance
		// then compare them with previous corresponding distance
		// by determine the possible vertice target first
		for (j = 0; j < vertice; j++) {
			if (matrix[S[num_visit-1]][j] != 999) {    // the possible vertice target of current vertice
        alt = dist[S[num_visit-1]] + matrix[S[num_visit-1]][j];    // add total possible path from current vertice
				if (alt < dist[j]) {
					dist[j] = alt;
					parent[j] = S[num_visit-1];
				}
			}
		}
		if (iteration < 2 or num_unvisit < 2) {
			// display the new dist array
			cout<<endl<<"- The new distance array : "<<endl;
			for (i = 0; i < vertice; i++) {
				cout<<dist[i]<<" ";
			}
			// display the dist matrix
			cout<<endl<<"- Matrix distance of unvisit node :";
			for (i = 0; i < num_unvisit; i++) {
				cout<<dist[unvisit[i]]<<" ";
			}
			cout<<endl;
		}
		distance = least;
		if (num_unvisit < 1) {
			print_path(parent, current);
		}
		iteration++;
	}

	return distance;
}

int main () {

	//	Variable Declaration
	int n;
	float distance;

	//	Main Program
	cout<<"---------------------------------------------------------------"<<endl;
	cout<<"Program of Dijkstra Algorithm for solving Shortest Path Problem"<<endl;
	cout<<"---------------------------------------------------------------"<<endl<<endl;
	do {
		cout<<"Input number of vertices (max 10) : ";
		cin>>n;
		cout<<endl;
	} while(n < 0 or n > 10);

	build_matrix(n);
	distance = dijkstra(n);
	cout<<"- Minimum distance : "<<distance;

	return 0;
}
