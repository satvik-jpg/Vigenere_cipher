// ..........................................le Chiffre Indechiffrable.........................................//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <bits/stdc++.h>
using namespace std;
map<char, int> m;
string textstrip(string name)
{
    ifstream file;
    file.open(name);
    stringstream buffer;
    buffer << file.rdbuf();
    string c, c2;
    c = buffer.str();
    long long i;
    for (i = 0; i < c.size(); i++)
    {
        if ((c[i] >= 'a' && c[i] <= 'z'))
            c2 = c2 + c[i];
        else if (c[i] >= 'A' && c[i] <= 'Z')
            c2 = c2 + char(c[i] - 'A' + 'a');
    }
    return c2;
}
map<char, int>::iterator letter_distribution(char *ptr, int move, int size)
{
    m.clear();
    // this function accepts a string comprsising of only lower case letters
    // then this function uses map container of STL to count the frequency of each character and arrange the characters lexicographically
    for (int i = 0; i < size; i = i + move)
    {
        m[*(ptr + i)]++;
    }
    auto it = m.begin();
    // it is an iterator pointing to the first pair of map
    return it;
}
string substitution_encrypt(string file, int key)
{
    // this function uses substitution cipher to encrypt the data
    string s;
    long long i;
    for (i = 0; i < file.size(); i++)
    {
        if (file[i] + key > 'z')
            s = s + (char)(file[i] + key - 'z' + 'a' - 1);
        else
            s = s + (char)(file[i] + key);
    }
    return s;
}
int cryptanalyse_substitution(char *ptr, int move, int size)
{

    int max = 0;
    char val;
    // this function takes a string encrypted using substitution cipher and predicts the key
    map<char, int>::iterator it_c = letter_distribution(ptr, move, size);
    for (auto temp = it_c; temp != m.end(); temp++)
    {
        if (temp->second > max)
        {
            max = temp->second;
            val = temp->first;
        }
    }

    if (val >= 'e')
        return (val - 'e');
    else
        return ('z' - 'e' + val - 'a' + 1);
}
string vigenere_encrypt(string data, string pass)
{
    /*this fiunction takes a data, encrypt it using the password 'pass'
    following the vigenere cipher method and returns the encrypted data*/
    string s = "";
    for (int i = 0, j = 0; i < data.size(); i++, j++)
    {
        int len = data[i] - 'a' + 1;
        if (pass[j] + len - 1 > 'z')
        {
            s += char(pass[j] + len - 1 - 'z' + 'a' - 1);
        }
        else
        {
            s += char(pass[j] + len - 1);
        }
        if (j == pass.size() - 1)
            j = -1;
    }
    return s;
}
string cryptanalyse_vigenere_afterlength(char *ptr, int len, int size)
{
    string pass = "";
    for (int i = 0; i < len; i++)
    {
        int pos = cryptanalyse_substitution(ptr + i, len, size);
        if (pos == 0)
            pass = pass + 'a';
        else
            pass = pass + (char)('b' + pos - 1);
    }
    return pass;
}
int cryptanalyse_vigenere_findlength(string file)
{
    int v;
    map<int, int> m;
    int max = 0;
    for (int i = 0; i < 10000; i++)
    {
        for (int j = i + 1; j < 10000; j++)
        {
            if (file.substr(i, 4) == file.substr(j, 4))
            {
                for (int k = 2; k <= (j - i) / 2; k++)
                {
                    if ((j - i) % k == 0)
                        m[k]++;
                }
            }
        }
    }
    for (auto val : m)
    {
        if (val.second > max)
        {
            max = val.second;
            v = val.first;
        }
    }
    return v;
}
string cryptanalyse_vigenere(string file)
{
    int ln = cryptanalyse_vigenere_findlength(file);
    return (cryptanalyse_vigenere_afterlength(&file[0], ln, file.size()));
}
int main()
{

    string file = textstrip("sherlock.txt"); // returns the contents of the file with special charcaters and digits removed
    // map<char, int>::iterator it = letter_distribution(&file[0], 1, file.size());
    //    this function returns an iterartor pointing to the starting pair of the map which contains the frequency distribution of each character.

    /*for (auto temp = it; temp != m.end(); temp++)
        cout << (temp->first) << ":" << (temp->second * 1.0 / file.size()) * 100 << '%' << endl;

    /* .....the few lines written above calculates the percentage of each letter present.Initially I calculated it only on lowercase letters.
     According to the data given in the code book 'e' should be the most frequently occcuring character
     but it was not in the lowercase data . This clearly indicates that removing all the uppercase letters had a very dramatic effect
     on the text.....
    */
    // string encrypt = substitution_encrypt(file, 6);
    //   encrypts the data using substitution cipher
    //    encrypt contains the data encrypted using substitution cipher
    // int key = cryptanalyse_substitution(&encrypt[0], 1, encrypt.size());

    string v_encrypt = vigenere_encrypt(file, "hesaidgo");

    // v_encrypt contains the data encrypted using the vigenere cipher method
    // string password = cryptanalyse_vigenere_afterlength(&v_encrypt[0], 5, v_encrypt.size() / 5);
    // int pass_length = cryptanalyse_vigenere_findlength(v_encrypt);
    string hurrah_vigenere = cryptanalyse_vigenere(v_encrypt);
    cout << hurrah_vigenere;
}
