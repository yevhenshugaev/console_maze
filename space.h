#pragma once
class space
{
public : // functions for user
	space(int, int);
	~space();
	void show();							// show maze
	void create();							// create maze
	void utravel();							// manual control
	void atravel();							// auto control 

private: // memory variables 
	int Xsz, Ysz;							// 10x10 < MTX size < 100x100 && %2!=0
	int Xp, Yp, Xs, Ys, Xe, Ye, Xn, Yn;		// p_now, s_start, e_end, n_new: post
	int Cell, Side, FC;						// temp, temo, free cells count, update screen 
	bool side[4], sz_stat, cr_stat, stat;	// stat uldr_cells, access, access
	char hero = '@';
	char bord = '#';
	char road = ' ';
	char used = '^';
	char MTX[100][100]; 

private: // functions for algo
	void move(int, int, char);				// set new post -> update mtx -> show 
	void rturn(int*, int*);					// turn the hero by 90` to the right 
	void lturn(int*, int*);					// turn the hero by 90` to the left
	void atravel(int, int);					// auto control !recursive!
	void resmsg(bool);						// show result of a travel 
	void errmsg(std::string);				// show functions error message 
};

