#include <iostream>
#include <string>
using namespace std;

string arrLps(const string& txt, int k) //функци€ создающа€ подстроку, длинной "к", начина€ с начала основной строки 
{
    string lps(k, ' ');    //создаЄм строку длинной в периодичность "к", и заполн€ем пробелами
    for (int i = 0; i < k; i++)
    {
        lps[i] = txt[i];
    }
    //cout << "¬ строке " << txt << " , подстрока lps будет " << lps << endl;
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

    int periodic = 0;   //кол-во повторений
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
            periodic++; //считаем кол-во повторений подстроки в строке
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
                    return -1;  //если подстрока при очередном сравнении не совпадает возвращаем -1
                    i = i + 1;
                }
            }
    }
    return periodic;    //возвращаем кол-во повторенний  
}

bool IsKPeriodic(const string& txt, int k)
{
    if (k <= 0) //проверка чтобы заданна€ кратность не была равна 0 или отрицательному значению
    {
        cout << "«аданнна€ кратность " << k << " не должна быть меньше или равно нулю" << endl;
        cout << endl;
        return false;
    }
    if (k > txt.size()) //проверка чтобы заданна€ кратность не превышала длину строки
    {
        cout << "«аданнна€ кратность " << k << " превышает длину строки " << txt << endl;
        cout << endl;
        return false;
    }

    if (txt.size() % k) //проверка чтобы длина строки была кратна заданной числу "к"
    {
        cout << "строка " << txt << " не кратна " << k << endl;
        cout << endl;
        return false;
    }
  
  string lps = arrLps(txt, k);  //вызываем функцию создани€ подстроки
  int periodic = KMPSearch(lps, txt);   //вызываем функцию  ћѕ, котора€ сравнивает поддстроки в строке и возвращает или -1 или положительное число повтоений
  if (periodic == -1)   //провер€ем кол-во стравнений, если  ћѕ вернул -1, то в строке есть лишние символы и строка не кратна
  {
    cout << "строка " << txt << " не кратна " << k << endl;
    cout << endl;
    return false;
  }
  cout << "строка " << txt << " кратна " << k << " и подстрока "<< lps <<" повтор€етс€ " << periodic << " раз(а)" << endl;
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
    int е = -3;
    IsKPeriodic(txt2, е);

    string txt3 = "ABABAABABAABABA";
    int g = 5;
    IsKPeriodic(txt3, g);
    
    return 0;
}
