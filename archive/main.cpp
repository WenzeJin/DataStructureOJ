#include <string>
#include <iostream>
#include <vector>

int * kmpStr(std::string tar, std::string mod) 
{
    int *res = new int[100002];
    int res_pt = 1;
    int res_cnt = 0;
    int tl = tar.length();
    int ml = mod.length();
    mod.push_back('*');

    int *next = new int[ml + 1];

    if(ml <= 0) 
    {
        delete[] res;
        return nullptr;
    }


    int k = 0;
    int j = 1;
    next[0] = -1;
    while (j <= ml) {		//计算next[j]
        k = next[j-1];
        while(1) { 
            if ( k == -1 || mod[j-1] == mod[k]) {
                k++;
                next[j] = k;
                j++;
                break;
            }
            else k = next[k];
        }
    }

    size_t lt = tar.length();
    int tar_pt = 0;
    int mod_pt = 0;

    while (mod_pt <= ml && tar_pt < tl) 
    {
        if (tar[tar_pt] == mod[mod_pt]) 
        {
            tar_pt++;
            mod_pt++;
            if (mod_pt == ml) 
            {
                res[res_pt] = tar_pt - ml;
                res_pt++;
                res_cnt++;
            }
        } else {
            if(next[mod_pt] == -1) {
                tar_pt++;
                mod_pt = 0;
            } else {
                mod_pt = next[mod_pt];
            }
        }
    }

    res[0] = res_cnt;
    return res;
}

int main() {
    int n;
    std::cin >> n;
    std::string mod;
    std::cin >> mod;
    std::string mod1;
    std::string mod2;
    for (int i = 0; i < mod.length(); i++) {
        if (mod[i] == '*') {
            mod1 = mod.substr(0, i);
            mod2 = mod.substr(i + 1, mod.length() - i - 1);
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        std::string tar;
        std::cin >> tar;
        int *res1 = kmpStr(tar, mod1);
        int *res2 = kmpStr(tar, mod2);
        int l1 = mod1.length();
        
        if(!res1 && !res2) {
            std::cout << (tar.length() > 0 ? "true" : "false") << std::endl;
        } else if(!res1) {
            bool notfound = true;
            for (int j = 1; j <= res2[0]; j++)
            {
                if(res2[j] >= 1) {
                    notfound = false;
                    std::cout << "true" << std::endl;
                    break;
                }
            }
            if (notfound)
                std::cout << "false" << std::endl;
        } else if(!res2) {
            bool notfound = true;
            for (int j = 1; j <= res1[0]; j++) 
            {
                if(res1[j] <= tar.length() - l1 - 1) 
                {
                    notfound = false;
                    std::cout << "true" << std::endl;
                    break;
                }
            }
            if (notfound)
                std::cout << "false" << std::endl;
        } else {
            bool notfound = true;
            for (int p1 = 1; p1 <= res1[0] && notfound; p1++) {
                for (int p2 = res2[0]; p2 >= 1; p2 --) {
                    if(res1[p1] + l1 + 1 == res2[p2]) {
                        std::cout << "true" << std::endl;
                        notfound = false;
                        break;
                    }
                    else if (res1[p1] + l1 + 1 > res2[p2])
                    {
                        break;
                    }
                }
            }
            if(notfound) {
                std::cout << "false" << std::endl;
            }
        }
    }
}