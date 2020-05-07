#include <iostream>
#include <chrono>
#include <vector>

//二分查找
int BinarySearch(std::vector<int>& arr,int low,int hight,int val){
    int mid =0;
    while(low<=hight){
        mid = (low+hight)/2;
        if(arr[mid] == val){
            return mid;
        }else if(arr[mid]>val){
            hight=mid-1;
        }else{
            low=mid+1;
        }
    }

    return -1;
}

//递归二分查找
int Rec(std::vector<int>& arr,int low,int hight,int val){
    if(low>hight){//这里是大于
        return -1;
    }

    int mid = (low+hight)/2;
    if(arr[mid] == val){
        return mid;
    }else if(arr[mid]>val){
        return Rec(arr,low,mid-1,val);
    }else if(arr[mid]<val){
        return Rec(arr,mid+1,hight,val);
    }
    return -1;
}


int main() {
    std::vector<int> arr;
    for(int i=1;i<100000000;i++){
        arr.emplace_back(i);
    }
    int size = arr.size();

    auto start = std::chrono::steady_clock::now();
    int index = BinarySearch(arr,0,size-1,2);
    if(index>=0){
        std::cout<<"index:"<<index<<" val:"<<arr[index]<<std::endl;
    }else{
        std::cout<<"no val"<<std::endl;
    }

    index = BinarySearch(arr,0,size-1,11);
    if(index>=0){
        std::cout<<"index:"<<index<<" val:"<<arr[index]<<std::endl;
    }else{
        std::cout<<"no val"<<std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout<<"BinarySearch:time:"<<time.count()<<std::endl;
    std::cout<<"------------------------"<<std::endl;

    start = std::chrono::steady_clock::now();
    index = Rec(arr,0,size-1,2);
    if(index>=0){
        std::cout<<"index:"<<index<<" val:"<<arr[index]<<std::endl;
    }else{
        std::cout<<"no val"<<std::endl;
    }

    index = Rec(arr,0,size-1,11);
    if(index>=0){
        std::cout<<"index:"<<index<<" val:"<<arr[index]<<std::endl;
    }else{
        std::cout<<"no val"<<std::endl;
    }
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout<<"Rec:time:"<<time.count()<<std::endl;
    return 0;
}
