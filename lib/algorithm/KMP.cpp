#include <string>
#include <vector>
#include <iostream>

int kmpStr(std::string tar, std::string mod) 
{
    std::vector<size_t> next;
    
    if(mod.length() <= 0) 
    {
        return -1;
    }

    int lm = mod.length();

    next.push_back(0);
    size_t left = 0;
    size_t right = 1;
    while (right < lm)
    { 
        if(mod[left] == mod[right]) 
        {
            next.push_back(next[left - 1] + 1);
            left++;
            right++;
        }
        else if (left != 0)
        {
            left = next[left - 1];
        }
        else
        {
            next.push_back(0);
            right++;
        }
    }

    next[0] = 0;
    size_t lt = tar.length();
    size_t tar_pt = 0;
    size_t mod_pt = 0;

    while (mod_pt < lm && tar_pt < lt) 
    {
        if (tar[tar_pt] == mod[mod_pt]) 
        {
            tar_pt++;
            mod_pt++;
        }
        else if (mod_pt != 0) 
        {
            mod_pt = next[mod_pt - 1];
        }
        else
        {
            tar_pt++;
        }
    }

    if (mod_pt == lm) 
    {
        return tar_pt - lm;
    }

    return -1;
}