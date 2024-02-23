// C++ program to words in a sentence.
#include <bits/stdc++.h>
 #include <fstream>
 using namespace std;
void removeDupWord(char str[])
{
    // Returns first token 
    char *token = strtok(str, " ");
  
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}
 
// Driver code
int main()
{
    string str = "Geeks          for Geeks";
    std::vector<std::string> parts;
            std::string part;
            std::istringstream iss(str);
            while(iss>>part){
                parts.push_back(part);
                cout<<part<<endl;
            }
    
    return 0;
}