#define CONSONANTS_SIZE 27
wchar_t consonants[CONSONANTS_SIZE][4]={
    L"ph",
    L"th",
    L"tr",
    L"gi",
    L"d",
    L"ch",
    L"nh",
    L"ng",
    L"ngh",
    L"kh",
    L"g",
    L"gh",
    L"c",
    L"q",
    L"k",
    L"t",
    L"r",
    L"h",
    L"b",
    L"m",
    L"v",
    L"đ",
    L"n",
    L"l",
    L"x",
    L"p",
    L"s",
    };
wchar_t utterances_consonant_init[CONSONANTS_SIZE][4] = {
    L"f",
    L"t_h",
    L"ts\\",
    L"z",
    L"z",
    L"ts\\",
    L"J",
    L"N",
    L"N",
    L"x",
    L"G",
    L"G",
    L"k",
    L"k",
    L"k",
    L"t",
    L"z",
    L"h",
    L"b",
    L"m",
    L"v",
    L"d",
    L"n",
    L"l",
    L"s",
    L"p",
    L"s",
};
wchar_t utterances_consonant_fin[CONSONANTS_SIZE][4] = {
    L"",
    L"",
    L"",
    L"",
    L"",
    L"k_+",
    L"N_+",
    L"Nm",
    L"",
    L"",
    L"",
    L"",
    L"kp",
    L"",
    L"",
    L"t",
    L"",
    L"",
    L"",
    L"m",
    L"",
    L"",
    L"n",
    L"",
    L"",
    L"p",
    L"",
};
wchar_t* convert_consonant_fin_to_utterance(wchar_t *consonant){
    if(wcscmp(consonant,L"c")==0||wcscmp(consonant,L"ch")==0){
        
    }
}