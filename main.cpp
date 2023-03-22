#include <iostream>
#include <string>
using namespace std;

string arrLps(const string& txt, int k) //������� ��������� ���������, ������� "�", ������� � ������ �������� ������ 
{
    string lps(k, ' ');    //������ ������ ������� � ������������� "�", � ��������� ���������
    for (int i = 0; i < k; i++)
    {
        lps[i] = txt[i];
    }
    //cout << "� ������ " << txt << " , ��������� lps ����� " << lps << endl;
    return lps;
}

void computeLPS(string pat, int* lps)
{
    int j = 0;

    lps[0] = 0; // lps[0] is always 0 

    int i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0) {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(const string& pat, const string& txt)
{
    int* lps = new int[pat.size()];

    computeLPS(pat, lps);

    int periodic = 0;   //���-�� ����������
    int i = 0;
    int j = 0;
    while (i < txt.size())
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == pat.size()) 
        {
            periodic++; //������� ���-�� ���������� ��������� � ������
            j = lps[j - 1];
        }
        else 
            if (i < txt.size() && pat[j] != txt[i]) 
            {
                if (j != 0)
                {
                    
                    j = lps[j - 1];
                }
                else
                {
                    return -1;  //���� ��������� ��� ��������� ��������� �� ��������� ���������� -1
                    i = i + 1;
                }
            }
    }
    return periodic;    //���������� ���-�� �����������  
}

bool IsKPeriodic(const string& txt, int k)
{
    if (k <= 0) //�������� ����� �������� ��������� �� ���� ����� 0 ��� �������������� ��������
    {
        cout << "��������� ��������� " << k << " �� ������ ���� ������ ��� ����� ����" << endl;
        cout << endl;
        return false;
    }
    if (k > txt.size()) //�������� ����� �������� ��������� �� ��������� ����� ������
    {
        cout << "��������� ��������� " << k << " ��������� ����� ������ " << txt << endl;
        cout << endl;
        return false;
    }

    if (txt.size() % k) //�������� ����� ����� ������ ���� ������ �������� ����� "�"
    {
        cout << "������ " << txt << " �� ������ " << k << endl;
        cout << endl;
        return false;
    }
  
  string lps = arrLps(txt, k);  //�������� ������� �������� ���������
  int periodic = KMPSearch(lps, txt);   //�������� ������� ���, ������� ���������� ���������� � ������ � ���������� ��� -1 ��� ������������� ����� ���������
  if (periodic == -1)   //��������� ���-�� ����������, ���� ��� ������ -1, �� � ������ ���� ������ ������� � ������ �� ������
  {
    cout << "������ " << txt << " �� ������ " << k << endl;
    cout << endl;
    return false;
  }
  cout << "������ " << txt << " ������ " << k << " � ��������� "<< lps <<" ����������� " << periodic << " ���(�)" << endl;
  cout << endl;
  return true;
}


int main()
{
    setlocale(LC_ALL, "");

    string txt0 = "ABABDABACDABABCABA";
    int k = 3;
    IsKPeriodic(txt0, k);


    string txt1 = "foofoofoofoo";
    int r = 3;
    IsKPeriodic(txt1, r);

    string txt2 = "SJFSDOOJ";
    int � = -3;
    IsKPeriodic(txt2, �);

    string txt3 = "ABABAABABAABABA";
    int g = 5;
    IsKPeriodic(txt3, g);
    
    return 0;
}
