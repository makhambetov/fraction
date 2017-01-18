#include <iostream>
#include "cFrac.h"
using namespace std;

//����������� �� ���������
CFrac::CFrac()
	{
		m_nChis = 0;
		m_nZnam = 0;
	}

//����������� ������������� ���������� � ������������
CFrac::CFrac(int nChis, int nZnam)
	{
		m_nChis = nChis;
		m_nZnam = nZnam;
	}

//����������� �����������
CFrac::CFrac(CFrac &�Frac)
	{
		m_nChis = �Frac.GetChis();
		m_nZnam = �Frac.GetZnam();
	}

//����������� ������������� �������
CFrac::CFrac(char *pszStr) //: CFrac()
{
	this->SetFrac(pszStr);
}

//����������� ������������� ����� ������
CFrac::CFrac(int nNum)
{
	this->SetInt(nNum);
}
		
//Set � Get ������
void CFrac::SetChis(int nNum){m_nChis = nNum;}
void CFrac::SetZnam(int nNum){m_nZnam = nNum;}
int CFrac::GetChis(){return m_nChis;}
int CFrac::GetZnam(){return m_nZnam;}

//����� ������ �� �����
void CFrac::Display()
{
	if(m_nChis == 0) cout << 0 << "\n";
	else cout << m_nChis << "/" << m_nZnam << "\n";
}
//����� ������ �� ����� � ���� ���������� ����� 7/3 -> 2(1/3)
void CFrac::DisplayProper()
{
	if(m_nChis > m_nZnam){
		int nInt = m_nChis % m_nZnam;
		cout << nInt << "(" << m_nChis-(m_nZnam*nInt) << "/" << m_nZnam << ")"<< "\n";
	}
	else
		Display();
}

//����� ������������� ������� ������, ������������ ������
void CFrac::SetFrac(char *pszStr)
{
	m_nChis = 0;
	m_nZnam = 0;
	char *pszSlash = strchr(pszStr, '/'); //���������� ����� ������� '/' � ������
	
	//���������, ������ �� ������ '/'
	if (pszSlash)
	{
		int nLenC = pszSlash - pszStr;			  //����� ���������
		int nLenZ = strlen(pszStr) - nLenC - 1;  //����� �����������

		for (int i = 0, p = nLenC-1; i < nLenC; i++)
		{
			m_nChis += (pszStr[i] - 48) * pow(10, p);
			p--;
		}	

		for (int i = 0, p = nLenZ-1; i < nLenZ; i++)
		{
			m_nZnam += (pszStr[i + nLenC + 1] - 48) * pow(10, p);
			p--;
		}
		this->Reduction();
	}
	//������ � ������ ���������� � ������ ������� '/'
	else
	{
		cout << "������! ������� ��������� �����.\n";
		return;
	}
}

//����� ���������� ����� ������ ����� 5 -> 5/1
void CFrac::SetInt(int nNum)
{
	m_nChis = nNum;
	m_nZnam = 1;
}

//����� ���������� �����   5/10 -> 1/2
void CFrac::Reduction()
{
	int nChis = this->GetChis();
	int nZnam = this->GetZnam();
	for (int i = nChis; i > 0 ; i--){
		if(nChis % i == 0){
			if(nZnam % i == 0){
				m_nChis /= i;
				m_nZnam /= i;
				break;
			}
		}
	}
}

//���������� ��������� =
CFrac& CFrac::operator=(CFrac &cFrac)
{
	//this->SetChis(0);
	//this->SetZnam(0);
	this->m_nChis = cFrac.GetChis();
	this->m_nZnam = cFrac.GetZnam();
	this->Reduction();
	return *this;
}
CFrac&  CFrac::operator=(char *pszStr)
{
	SetFrac(pszStr);
	return *this;

}

//���������� ��������� +
CFrac& CFrac::operator+(CFrac &cFrac)
{
	if(this->m_nZnam == cFrac.GetZnam())
	{
		this->m_nChis += cFrac.m_nChis;
		this->Reduction();
		return *this;
	}
	else
	{
		this->m_nChis = (this->GetChis() * cFrac.GetZnam()) + (cFrac.GetChis() * this->GetZnam());
		this->m_nZnam *= cFrac.GetZnam();
		this->Reduction();
		return *this;
	}
}
CFrac& CFrac::operator+(char *pszStr)
{
	CFrac CTemp(pszStr);
	operator+(CTemp);
	return *this;
}

//���������� ��������� -
CFrac& CFrac::operator-(CFrac &cFrac)
{
	if(this->m_nZnam == cFrac.GetZnam())
	{
		this->m_nChis -= cFrac.GetChis();
		this->Reduction();
		return *this;
	}
	else
	{
		this->m_nChis = 
			(this->m_nChis * cFrac.GetZnam()) - 
			(cFrac.GetChis() * this->m_nZnam);
		this->m_nZnam *= cFrac.GetZnam();
		this->Reduction();
		return *this;
	}
}
CFrac& CFrac::operator-(char * pszStr)
{
	CFrac cTemp(pszStr);
	operator-(cTemp);
	return *this;
}

//���������� ��������� *
CFrac& CFrac::operator*(CFrac &cFrac)
{
	this->m_nChis *= cFrac.GetChis();
	this->m_nZnam *= cFrac.GetZnam();
	this->Reduction();
	return *this;
}
CFrac& CFrac::operator*(char * pszStr)
{
	CFrac cTemp(pszStr);
	operator*(cTemp);
	return *this;
}

//���������� ��������� /
CFrac& CFrac::operator/(CFrac &cFrac)
{
	this->m_nChis *= cFrac.GetZnam(); 
	this->m_nZnam *= cFrac.GetChis();
	this->Reduction();
	return *this;
}
CFrac& CFrac::operator/(char * pszStr)
{
	CFrac cTemp(pszStr);
	operator/(cTemp);
	return *this;
}


void main(){
	setlocale(LC_ALL, "RUSSIAN");
	
	//��������

	cout <<"----------------------------------\n";
	cout << "������������� ������:\n";
	CFrac drob1;
	cout << "CFrac drob1; \t- "; drob1.Display();

	CFrac drob2("3/2");
	cout << "CFrac drob2(\"3/2\"); - "; drob2.Display();

	CFrac drob3(drob2);
	cout << "CFrac drob3(drob2); - "; drob3.Display();

	CFrac drob4(3, 9);
	cout << "CFrac drob4(3, 9); - "; drob4.Display();

	CFrac drob5(14);
	cout << "CFrac drob5(14); - "; drob5.Display();

	cout <<"----------------------------------\n";

	cout << "\n����� �� ����� � ���� ���������� �����:\n";
	cout << "������������ ����: "; drob3.Display();
	cout << "���������� ����: "; drob3.DisplayProper();

	cout <<"----------------------------------\n";

	cout << "\n�������� ����������:\n";
	cout << "drob1 = drob2"; drob1 = drob2;
	cout << "\ndrob1 = "; drob1.Display();
	cout << "\ndrob1 = \"4/7\""; drob1 = "4/7";
	cout << "\ndrob1 = "; drob1.Display();

	cout <<"----------------------------------\n";

	cout << "\n�������� ��������:\n";
	cout << "drob1 = drob2 + drob3"; drob1 = drob2 + drob3;
	cout << "\ndrob1 = "; drob1.Display();
	cout << "\ndrob1 = drob1 + \"4/7\""; drob1 = drob1 + "4/7";
	cout << "\ndrob1 = "; drob1.Display();

	cout <<"----------------------------------\n";

	cout << "\n�������� ���������:\n";
	cout << "drob2 = drob1 - drob3"; drob2 = drob1 - drob3;
	cout << "\ndrob2 = "; drob2.Display();
	cout << "\ndrob2 = drob2 - \"4/7\""; drob2 = drob2 - "4/7";
	cout << "\ndrob2 = "; drob2.Display();

	cout <<"----------------------------------\n";

	cout << "\n�������� ���������:\n";
	cout << "drob2 = drob1 * drob3"; drob2 = drob1 * drob3;
	cout << "\ndrob2 = "; drob2.Display();
	cout << "\ndrob2 = drob2 * \"4/7\""; drob2 = drob2 * "4/7";
	cout << "\ndrob2 = "; drob2.Display();

	cout <<"----------------------------------\n";

	cout << "\n�������� �������:\n";
	cout << "drob2 = drob1 / drob3"; drob2 = drob1 / drob3;
	cout << "\ndrob2 = "; drob2.Display();
	cout << "\ndrob2 = drob2 / \"4/7\""; drob2 = drob2 / "4/7";
	cout << "\ndrob2 = "; drob2.Display();


	cin.get();
}
