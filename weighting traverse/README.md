现有一些数组（整形/字符串类型皆可）a[7],b[4],c[3], d[2],e[4],里面存放的都是“0”或“1”，数组的长度不一。如图：  
![](http://d.pcs.baidu.com/thumbnail/ce11c0efb9505e41c275aac744c1c7bc?fid=3423036723-250528-736359963173036&time=1429632000&rt=pr&sign=FDTAER-DCb740ccc5511e5e8fedcff06b081203-IHj8uiCryEC816XuQWtld%2fBGdpA%3d&expires=8h&prisign=unknow&chkbd=0&chkv=0&size=c1280_u800&quality=90)  
现在需要对数组进行加权，然后按照权值进行遍历，依次寻找第一个“0”出现的位置。
例如，c数组加权为5，e加权为4，b加权为3，d加权为2，a加权为1；那么第一个0出现在e2，输出“e2”。
![](http://d.pcs.baidu.com/thumbnail/e6e7ee6f018ee0296527c98704f9cd88?fid=3423036723-250528-1018850392797568&time=1429632000&rt=pr&sign=FDTAER-DCb740ccc5511e5e8fedcff06b081203-2Ba5qbcsH%2bQKVvk1NK7KhNp9oJY%3d&expires=8h&prisign=unknow&chkbd=0&chkv=0&size=c1280_u800&quality=90)  

1. 翻转`alter();`  
alter（），将对应的数组中的值翻转
（如alter（b2）：b2的值从“0”变为“1”）  
2. 寻找`search();`  
即按权值顺序寻找第一个“0”出现的位置。
（如：search（）；输出e2）  
3. 修改不同的`weight[]`可以改变遍历的顺序。
