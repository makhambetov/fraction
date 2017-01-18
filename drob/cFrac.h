#pragma once

class CFrac
{
private:
	int m_nChis;
	int m_nZnam;
public:
	CFrac();
	CFrac(int, int);
	CFrac(CFrac&);
	CFrac(char*);
	CFrac(int);
//	~CFrac();

	void SetChis(int);
	void SetZnam(int);
	int GetChis();
	int GetZnam();
	void SetFrac(char*);
	void SetInt(int);
	void Display();
	void Reduction();
	void DisplayProper();

	CFrac& operator=(CFrac&);
	CFrac& operator=(char*);
	CFrac& operator+(CFrac&);
	CFrac& operator+(char*);
	CFrac& operator-(CFrac&);
	CFrac& operator-(char*);
	CFrac& operator*(CFrac&);
	CFrac& operator*(char*);
	CFrac& operator/(CFrac&);
	CFrac& operator/(char*);
};
