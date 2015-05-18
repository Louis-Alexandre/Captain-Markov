#include "CollisionHandler.h"
#include "operationVector.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "Turn.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "VectorOfTurn.h"
#include "Game.h"
#include "bw.h"
#include "Position.h"
#include "beta.h"

using namespace std;
using namespace boost::numeric::ublas;

void game();
void test();

int main()
{
	game();
// 	test();
	return 0;
}

void game()
{
	Game game;
	game.init();
	game.mainLoop();
}

void test()
{
	
	matrix<double> P{8, 8};
	std::vector<double> pie{0, 0, 0, 0, 1, 0, 0, 0};
	
	fill(P, [&](int l, int c){
		if ( abs(l - c) < 2 || (l == 0 && c == 7) || (l == 7 && c == 0)) {
			return 1/3.0;
		}
		return 0.0;
	});
	
	matrix<double> Obs(6, 8);
	fill(Obs, [&](int l, int c){
		if (l == 0 && (c == 0 || c == 1 || c == 7)) {
			return 0;
		}
		
		if (l == 1 && (c == 0 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 2 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 3 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 4 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 5 && (c == 0 || c == 6 || c == 7)) {
			return 0;
		}
		return 1;
	});
	
matrix<double> Obs2(3, 8);
	fill(Obs2, [&](int l, int c){
		if (l == 0 && (c == 0 || c == 1 || c == 7)) {
			return 0;
		}
		
		if (l == 1 && (c == 0 || c == 1 || c == 2)) {
			return 0;
		}
		
		if (l == 2 && c != 2 ) {
			return 0;
		
		}

		return 1;
	});
	
	matrix<double> Obs3(5, 8);
	fill(Obs3, [&](int l, int c){
		if (l == 0 && (c == 0 || c == 1 || c == 7)) {
			return 0;
		}
		
		if (l == 1 && (c == 0 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 2 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 3 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 4 && c!= 5 ) {
			return 0;
		}
		
		return 1;
	});
	
		matrix<double> Obs4(9, 8);
	fill(Obs4, [&](int l, int c){
		if (l == 0 && (c == 0 || c == 1 || c == 7)) {
			return 0;
		}
		
		if (l == 1 && (c == 0 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 2 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 3 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 4 && (c == 5 || c == 6 || c == 4)) {
			return 0;
		}
		
		if (l == 5 && (c == 4 || c == 5 || c == 3)) {
			return 0;
		}
		
		if (l == 6 && (c == 5 || c == 6 || c == 4)) {
			return 0;
		}
		
		if (l == 7 && (c == 5 || c == 6 || c == 7)) {
			return 0;
		}
		
		if (l == 8 && c!= 7 ) {
			return 0;
		}
		
		
		return 1;
	});
	
	matrix<double> Obs5(3, 8);
	fill(Obs5, [&](int l, int c){
		if (l == 0 && (c == 0 || c == 1 || c == 7)) {
			return 0;
		}
		
		if (l == 1 && (c == 0 || c == 7 || c == 6)) {
			return 0;
		}
		
		if (l == 2 && c != 6 ) {
			return 0;
		
		}

		
		return 1;
	});
	
			matrix<double> Obs6(9, 8);
	fill(Obs6, [&](int l, int c){
		if (l == 0 && (c == 0 || c == 1 || c == 7)) {
			return 0;
		}
		
		if (l == 1 && (c == 0 || c == 1 || c == 2)) {
			return 0;
		}
		
		if (l == 2 && (c == 2 || c == 1 || c == 3)) {
			return 0;
		}
		
		if (l == 3 && (c == 3 || c == 2 || c == 4)) {
			return 0;
		}
		
		if (l == 4 && (c == 5 || c == 3 || c == 4)) {
			return 0;
		}
		
		if (l == 5 && (c == 4 || c == 5 || c == 3)) {
			return 0;
		}
		
		if (l == 6 && (c == 5 || c == 6 || c == 4)) {
			return 0;
		}
		
		if (l == 7 && (c == 5 || c == 4 || c == 3)) {
			return 0;
		}
		
		if (l == 8 && c!= 3 ) {
			return 0;
		}
		
		
		return 1;
	});
	
	// showMat(Beta(Obs, P, pie));
	
	showMat(BW({Obs,Obs2,Obs3,Obs4,Obs5,Obs6,Obs5,Obs5,Obs5,Obs5},P,pie,1000));


	//showMat(Obs6);
	//showMat(Position(Obs6,BW({Obs,Obs2,Obs3,Obs4,Obs5},P,pie,10),pie));
	//showMat(Position(Obs6,P,pie));
}
