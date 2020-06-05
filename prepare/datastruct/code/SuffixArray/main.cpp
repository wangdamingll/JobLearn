#include <iostream>
#include "SuffixArray.hpp"

using namespace std;

void TestCreateSuffixArray(const string& abr,vector<int>& sufarr,vector<int>& LCP){
#if 0
    //最坏O(N^2logN)
//    cout << "SLOW ALGORITHM" << endl;
    CreateSuffixArraySlow( abr, sufarr, LCP );
//    for( int i = 0; i < abr.length( ); ++i )
//        cout << i << " " << sufarr[ i ] << " " << LCP[ i ]<<" " <<abr.substr(sufarr[i]) << endl;
#else
    //最坏O(N)
//    cout << "FAST ALGORITHM" << endl;
    CreateSuffixArray( abr, sufarr, LCP );
//    for( int i = 0; i < abr.length( ); ++i )
//        cout << i << " " << sufarr[ i ] << " " << LCP[ i ]<<" " <<abr.substr(sufarr[i]) << endl;
#endif
}

//查找模式P是否在abr中
bool FindSubStr(const string& abr,const vector<int>& sufarr,const string& p){
    uint32_t low = 0;
    uint32_t high = sufarr.size()-1;
    uint32_t mid =0;
    bool isFind = false;
    while(low<=high){
        mid = (low+high)/2;
        const string subStr = abr.substr(sufarr[mid]);
        if(std::strcmp(p.c_str(),subStr.c_str())==0){
            isFind=true;
            break;
        }else if(std::strcmp(p.c_str(),subStr.c_str())<0){
            high=mid-1;
        }else if(std::strcmp(p.c_str(),subStr.c_str())>0){
            low = mid+1;
        }
    }
    if(isFind) return true;
    return (low<=(sufarr.size()-1) && abr.substr(sufarr[low]).find(p)!=std::string::npos);
}

// Test program
int main( ){
    const string abr = "hello banana";
    vector<int> sufarr( abr.length( ) );
    vector<int> LCP( abr.length( ) );

    //创建后缀数组
    TestCreateSuffixArray(abr,sufarr,LCP);

    //查找p是否在T源串中
    const string p = "ell";
    bool ret = FindSubStr(abr,sufarr,p);
    if(ret){
        std::cout<<"find"<<std::endl;
    }else{
        std::cout<<"not find"<<std::endl;
    }

    return 0;
}
