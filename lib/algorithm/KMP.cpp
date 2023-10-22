#include <string>
#include <iostream>

int kmpStr(std::string tar, std::string mod) 
{
    int tl = tar.length();
    int ml = mod.length();

    int * next = new int[ml];

    if(mod.length() <= 0) 
    {
        return -1;
    }


    int k = -1;
    int right = 1;
    while (right < ml)
    { 
        if(k == -1 || mod[k] == mod[right]) 
        {
            next[right] = k + 1;
            k++;
            right++;
        } else {
            while(k != -1 && mod[k] != mod[right]) 
            {
                k = next[k];
            }
        }
    }

    size_t lt = tar.length();
    int tar_pt = 0;
    int mod_pt = 0;

    while (mod_pt < ml && tar_pt < tl) 
    {
        if (tar[tar_pt] == mod[mod_pt]) 
        {
            tar_pt++;
            mod_pt++;
        } else {
            if(next[mod_pt] == -1) {
                tar_pt++;
                mod_pt = 0;
            } else {
                mod_pt = next[mod_pt];
            }
        }
    }

    if (mod_pt == ml) 
    {
        return tar_pt - ml;
    }

    return -1;
}