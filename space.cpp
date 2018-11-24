#include "pch.h"
#include "space.h"

space::space(int xsz, int ysz)
{
	// pre_init variables 
	Xsz = Ysz = Xn = Yn = Xp = Yp = Xs = Ys = Xe = Ye = Side = Cell = FC = -1;
	sz_stat = cr_stat = false; // access status 
	// take correct MTX size, and set sz_status 
	if (xsz > 10 && xsz < 100 && xsz % 2 != 0) Xsz = xsz;
	if (ysz > 10 && ysz < 100 && ysz % 2 != 0) Ysz = ysz; 
	// access for function ~ create():
	if (Xsz != -1 && Ysz != -1) { sz_stat = true; } // access is allowed
		else { errmsg("sz_stat"); } // access is denied 
}

space::~space()
{
}

void space::show()
{
	// cheking access
	if (cr_stat == false ) { errmsg("cr_stat"); return; } 

	// display matrix 
	system("cls");	  // cleaning
	cout << endl;     // x_offset
	for (int X = 0; X < Xsz; X++) {   // x: string
		cout << "  "; // y_offset
		for (int Y = 0; Y < Ysz; Y++) // y: row 
			cout << ' ' << MTX[X][Y]; // cell ~ x'y
		cout << endl; } // end of string

	// info string 
	cout << endl
		<< "   XYp: " << Xp << "`" << Yp
		<< "   XYs: " << Xs << "`" << Ys
		<< "   XYe: " << Xe << "`" << Ye << endl;
}

void space::create()
{
	// check access
	if (sz_stat == false) { errmsg("sz_stat"); return; }

	// init all space && counts 
	for (int X = 0; X < Xsz; X++)
		for (int Y = 0; Y < Ysz; Y++)
			MTX[X][Y] = bord;  
	cr_stat = false; // while maze is not all ready
	Xp = Yp = Xs = Ys = Xe = Ye = Side = Cell = -1;
	FC = 0; srand(time(0)); // randome

	// SET GRID - create maze
	for (int X = 1; X < Xsz; X += 2)
		for (int Y = 1; Y < Ysz; Y += 2) {
			MTX[X][Y] = road; FC++; // create cell

			// search avaliable side
			(MTX[X - 1][Y] != road && X - 1 > 0) ? side[0] = true : side[0] = false; // UP
			(MTX[X][Y + 1] != road && Y + 1 < Ysz - 1) ? side[1] = true : side[1] = false; // RT
			(MTX[X + 1][Y] != road && X + 1 < Xsz - 1) ? side[2] = true : side[2] = false; // DW
			(MTX[X][Y - 1] != road && Y - 1 > 0) ? side[3] = true : side[3] = false; // LF

			// if we have avaliable side 
			if ((side[0] + side[1] + side[2] + side[3]) != 0)
				while (true) { Cell = rand() % 4;// select random side  
					if (side[Cell] == true) { switch (Cell) {
						case 0: MTX[X - 1][Y] = road; break;
						case 1: MTX[X][Y + 1] = road; break;
						case 2: MTX[X + 1][Y] = road; break;
						case 3: MTX[X][Y - 1] = road; break; }
						FC++; break; } } // added 1 free cell 
		} // end set gred 

	// beta create in-out mirror algo 
	if (rand()%2 == 0) { 
		do { Xs = 0; Ys = 1 + (rand() % (Ysz - 2)); Xe = Xsz - 1; Ye = 1 + (rand() % (Ysz - 2));
		} while((MTX[Xs + 1][Ys] == bord) || (MTX[Xsz - 2][Ye] == bord));
	} else { 
		do { Xs = 1 + (rand() % (Xsz - 2)); Ys = 0; Xe = 1 + (rand() % (Xsz - 2)); Ye = Ysz - 1;
		} while ((MTX[Xs][Ys + 1] == bord) || (MTX[Xe][Ysz - 2] == bord)); }

	 // initialization
	Xn = Yn = -1; FC++; // out cell 
	Xp = Xs; Yp = Ys;   // sync 
	MTX[Xp][Yp] = hero; // in
	MTX[Xe][Ye] = road; // out 
	cr_stat = true;	    // access
}

void space::utravel()
{
	// check access
	if (sz_stat == false) { errmsg("sz_stat"); return; }

	// move hero 
	while ((Xn != Xs || Yn != Ys) && (Xn != Xe || Yn != Ye)) {
		// input new cell
		show(); cout << "\n   ~$ Enter XY: ";
		switch (cin.get()) {
		case 'W': case 'w': Xn = Xp - 1; Yn = Yp; break; // up
		case 'S': case 's': Xn = Xp + 1; Yn = Yp; break; // dw
		case 'D': case 'd': Xn = Xp; Yn = Yp + 1; break; // rt
		case 'A': case 'a': Xn = Xp; Yn = Yp - 1; break; // lf
		default: continue;
		}
		// check cell
		if (MTX[Xn][Yn] != bord && Xn >= 0 && Xn < Xsz && Yn >= 0 && Yn < Ysz) 
			move(Xn, Yn, 'u'); 
	} // end

	// when we finished 
	(Xp == Xe && Yp == Ye) ? resmsg(true) : resmsg(false);
}

void space::atravel()
{
	// check access
	if (sz_stat == false) { errmsg("sz_stat"); return; }

	// detect avalible cell
	if (MTX[Xp - 1][Yp] != bord && Xp - 1 >= 0) { atravel(-1, 0); return; };
	if (MTX[Xp][Yp - 1] != bord && Yp - 1 >= 0) { atravel(0, -1); return; };
	if (MTX[Xp + 1][Yp] != bord && Xp + 1 < Xsz) { atravel(+1, 0); return; };
	if (MTX[Xp][Yp + 1] != bord && Yp + 1 < Ysz) { atravel(0, +1); return; };
	resmsg(false); // if not avaliable cell 
}

void space::atravel(int Xn, int Yn)
{
	// cheking wayout
	if (((Xp + Xn == Xs) && (Yp + Yn == Ys)) || ((Xp == Xe) && (Yp == Ye))) {
		if (Xp != Xe && Yp != Ye) move(Xn, Yn, 'a'); // final move
		(Xp == Xe && Yp == Ye) ? resmsg(true) : resmsg(false); return; }

	// move hero 
	if (MTX[Xp + Xn][Yp + Yn] != bord) { 
		move(Xn, Yn, 'a'); rturn(&Xn, &Yn); atravel(Xn, Yn); 
	} else { lturn(&Xn, &Yn); atravel(Xn, Yn); }
}

void space::move(int Xn, int Yn, char id)
{
	MTX[Xp][Yp] = used;
	if (id == 'a') {Xp += Xn; Yp += Yn;} else {Xp = Xn; Yp = Yn;};
	MTX[Xp][Yp] = hero;
	//show(); // show matrix
}

void space::rturn(int* Xn, int* Yn)
{
	if (*Xn == -1 && *Yn == 0) { *Xn = 0; *Yn = +1;} else
	if (*Xn == 0 && *Yn == -1) { *Xn = -1; *Yn = 0;} else 
	if (*Xn == +1 && *Yn == 0) { *Xn = 0; *Yn = -1;} else 
	if (*Xn == 0 && *Yn == +1) { *Xn = +1; *Yn = 0;};
}

void space::lturn(int* Xn, int* Yn)
{
	if (*Xn == -1 && *Yn == 0) { *Xn = 0; *Yn = -1;} else
	if (*Xn == 0 && *Yn == -1) { *Xn = +1; *Yn = 0;} else 
	if (*Xn == +1 && *Yn == 0) { *Xn = 0; *Yn = +1;} else 
	if (*Xn == 0 && *Yn == +1) { *Xn = -1; *Yn = 0;};
}

void space::resmsg(bool stat)
{
	show(); // show matrix 
	stat ? cout << "\n   ~$ FINISHED!!!!\n" : cout << "\n   ~$ MAZE FILED!!\n"; 
	system("pause");
}

void space::errmsg(string name)
{
	cout << "   ~$ error: " << setw(6) << left <<  name << " = false\n";
	system("pause");
}