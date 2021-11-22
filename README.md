# serialization
Boost.Serializationを真似て作ったシリアライザ  
現状はJsonのみ対応

# ビルド方法
```shell
mkdir build
cd build
cmake ..
make

./sample
```

# できること
boostのシリアライザがどうなっているのか気になったので、似たような挙動のシリアライザを作成してみました。  
簡単な記述を追加するだけで、クラスの変数をJson形式で保存、読み込みしてくれます。  

## 使い方

はじめに、以下のファイルをインクルードします。
```
#include "fileio_json.hpp"
```

例えば、以下のようなクラスにおいて、
```cpp
class Sample {
public:
  Sample():value({1,2,3}){}
private:
  std::vector<double> value;
};
```

以下のような記述を追加すれば、
```cpp
class Sample {
public:
  Sample():value({1,2,3}){}
private:
  std::vector<double> value;

//ここを追加
protected:
  friend class access;
  template<class T>
  void serialize(T &ar) {
      ar & ARCHIVE_NAMEDVALUE(value);
  }
//ここまで追加
};
```

以下のようなコードでJsonの保存、読み込みができます。
```cpp
int main(){

    //検証用データを作成
    Sample sample;

    //データをJson化
    JsonOutputArchive ar_out;
    ar_out << sample;
    std::string json_str = ar_out.commit();

    //Jsonデータをロード
    JsonInputArchive ar_in(json_str);
    ar_in>>sample;

    return 0;
}
```

作成されるJsonは、以下のようになります。
```Json
[{"value":[1,2,3]}]
```

# 内部構造
![内部構造](https://github.com/Alreschas/serialization/blob/main/documents/%E5%86%85%E9%83%A8%E6%A7%8B%E9%80%A0.svg)
