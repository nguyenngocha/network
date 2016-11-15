/* towlower example */
#include <stdio.h>
#include <wchar.h>
#include <string.h>
void toLower(wchar_t* string){
    wchar_t upper[] = L"ÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐÉÈẺẼẸÊÉỀỂỄỆÍÌỈĨỊÓÒỎÕỌÔỖỒỔỖỘƠỚỜỞỠỢÚÙỦŨỤƯỨỪỬỮỰ";
    wchar_t lower[] = L"áàảãạăắằẳẵặâấầẩẫậđéèẻẽẹêếềểễệíìỉĩịóòỏõọôốồổỗộơớờởỡợúùủũụưứừửữự";
    // wchar_t upper[] = L"AÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐEÉÈẺẼẸÊÉỀỂỄỆIÍÌỈĨỊOÓÒỎÕỌÔỖỒỔỖỘƠỚỜỞỠỢUÚÙỦŨỤƯỨỪỬỮỰ";
    // wchar_t lower[] = L"aáàảãạăắằẳẵặâấầẩẫậđeéèẻẽẹêếềểễệiíìỉĩịoóòỏõọôốồổỗộơớờởỡợuúùủũụưứừửữự";
    int i=0;
    wchar_t *temp;
    while(string[i]!=L'\0'){
        temp=wcsrchr(upper,string[i]);
        if(temp){
            wprintf(L"%lc len = %d\n",lower[temp-upper],wcslen(upper));
           string[i]=lower[temp-upper];
        }
        else
            if(string[i]>=L'A'&&string[i]<=L'Z')
                string[i]+=32;
        i++;
    }
}
int main ()
{
  int i=0;
// wprintf (L"Characters: %lc %lc \n", L'a', 65);
//   wprintf (L"Decimals: %d %ld\n", 1977, 650000L);
  wchar_t str[]=L"AÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐEÉÈẺẼẸÊÉỀỂỄỆOÓÒỎÕỌÔỖỒỔỖỘƠỚỜỞỠỢUÚÙỦŨỤƯỨỪỬỮỰ";
  toLower(str);
  wprintf (L"Decimals: %ls\n", L"AÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐEÉÈẺẼẸÊÉỀỂỄỆOÓÒỎÕỌÔỖỒỔỖỘƠỚỜỞỠỢUÚÙỦŨỤƯỨỪỬỮỰ");
  return 0;
}