#include "fileio_json.hpp"
#include <iostream>

class Sample2 {
public:
    Sample2(){}

    Sample2(double val1,double val2,double val3) :
        s2_val1({val1,val2,val3})
    {
    }

public:
    std::vector<double> s2_val1;

protected:
    friend class access;
    template<class T>
    void serialize(T &ar) {
        ar & ARCHIVE_NAMEDVALUE(s2_val1);
    }
};

class Sample1{
public:
    Sample1() {
    }

public:
    int s1_val1 = 0;
    double s1_val2 = 0;
    std::string s1_val3;
    std::vector<Sample2> s1_val4;
    std::map<std::string,Sample2> s1_val5;

protected:
    friend class access;
    template<class T>
    void serialize(T &ar) {
        ar & ARCHIVE_NAMEDVALUE(s1_val1);
        ar & ARCHIVE_NAMEDVALUE(s1_val2);
        ar & ARCHIVE_NAMEDVALUE(s1_val3);
        ar & ARCHIVE_NAMEDVALUE(s1_val4);
        ar & ARCHIVE_NAMEDVALUE(s1_val5);
    }
};

int main(){

    //検証用データを作成
    Sample1 s1_from;
    s1_from.s1_val1 = 10;
    s1_from.s1_val2 = 12.3;
    s1_from.s1_val3 = "test";
    s1_from.s1_val4 = {Sample2(1,2,3),Sample2(4,5,6)};
    s1_from.s1_val5 = {{"key1",Sample2(1,2,3)},{"key2",Sample2(4,5,6)}};

    //データをJson化※メイン処理
    JsonOutputArchive ar_out;
    ar_out << s1_from;
    std::string json_str = ar_out.commit();


    //Json化した文字列を表示
    std::cout<<"exported json string:"<<std::endl;
    std::cout<<json_str<<std::endl;
    std::cout<<std::endl;

    //Jsonデータをロード※メイン処理
    Sample1 s1_to;
    JsonInputArchive ar_in(json_str);
    ar_in>>s1_to;


    //ロードしたクラスの変数を表示
    std::cout<<"imported class variables:"<<std::endl;
    std::cout<<"s1_val1(int): "<<s1_to.s1_val1<<std::endl;
    std::cout<<"s1_val2(double): "<<s1_to.s1_val2<<std::endl;
    std::cout<<"s1_val3(string): "<<s1_to.s1_val3<<std::endl;
    std::cout<<"s1_val4(vector):"<<std::endl;
    for (auto s2 : s1_to.s1_val4) {
        std::cout<<"  s2_val1 :[ ";
        for (auto val : s2.s2_val1) {
            std::cout << val<<" ";
        }
        std::cout<<"]"<<std::endl;
    }

    std::cout << "s1_val5(map):"<< std::endl;
    for (const auto& [key, s2] : s1_to.s1_val5) {
        std::cout<<"  key: "<< key<<", ";

        std::cout<<"s2_val1: [ ";
        for (auto val : s2.s2_val1) {
            std::cout << val<<" ";
        }
        std::cout<<"]"<<std::endl;
    }

    return 0;
}
