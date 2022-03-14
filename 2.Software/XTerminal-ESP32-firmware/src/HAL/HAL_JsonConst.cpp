#include <map>
#ifdef ARDUINO
#include "WString.h"
#else
#include "WString/WString.h"
#endif
// extern std::map<String, int> weather_str2int;
// extern String* ari_level_int2str;

String ari_level_int2str[]={
        "Excellent",//0
        "JustFine",//1
        "LightPollution",
        "MidPollution",
        "HeavyPollution",
        "SeriousPollution",//5
};
//std::map<int, String> ari_level_int2str[]={
//        {0,"Excellent"},//0
//        {1,"JustFine"},//1
//        {2,"LightPollution"},
//        {3,"MidPollution"},
//        {4,"HeavyPollution"},
//        {5,"SeriousPollution"}//5
//};
String weather_int2name[]={
        "Sunny",//0
        "Gloomy",//1
        "Rainy",
        "Cloudy",//1
        "HailStone",
        "Fogy",
        "DustStorm",//5
        "ThunderStorm",
        "Snow",
};

std::map<String, int> weather_str2int = {
        {"qing", 0},
        {"yin", 1},
        {"yu", 2},
        {"yun", 3},
        {"bingbao", 4},
        {"wu", 5},
        {"shachen", 6},
        {"lei", 7},
        {"xue", 8}
};


std::map<String, String> windir_cn2en={
        {"东风", "west"},
        {"南风", "south"},
        {"西风", "east"},
        {"北风", "north"},
        {"西北风", "eastnorth"},
        {"东北风", "westnorth"},
        {"东南风", "westsouth"},
        {"西南风", "eastsouth"},
};

std::map<String, String> city_cn={
        {"北京","Beijing"},
        {"天津","Tianjin"},
        {"上海","Shanghai"},
        {"重庆","Chongqing"},
        {"银川","Yinchuan"},
        {"石嘴山","Shizuishan"},
        {"吴忠","Wuzhong"},
        {"固原","Guyuan"},
        {"中卫","Zhongwei"},
        {"乌鲁木齐","Wulumuqi"},
        {"克拉玛依","Kelamayi"},
        {"拉萨","Lasa"},
        {"呼和浩特","Huhehaote"},
        {"包头","Baotou"},
        {"乌海","Wuhai"},
        {"赤峰","Chifeng"},
        {"通辽","Tongliao"},
        {"鄂尔多斯","Eerduosi"},
        {"呼伦贝尔","Hulunbeier"},
        {"巴彦淖尔","Bayannaoer"},
        {"乌兰察布","Wulanchabu"},
        {"南宁","Nanning"},
        {"柳州","Liuzhou"},
        {"桂林","Guilin"},
        {"梧州","Wuzhou"},
        {"北海","Beihai"},
        {"崇左","Chongzuo"},
        {"来宾","Laibin"},
        {"贺州","Hezhou"},
        {"榆林","Yulin"},
        {"百色","Baise"},
        {"河池","Hechi"},
        {"钦州","Qinzhou"},
        {"防城港","Fangchenggang"},
        {"贵港","Guigang"},
        {"哈尔滨","Haerbin"},
        {"大庆","Daqing"},
        {"齐齐哈尔","Qiqihaer"},
        {"佳木斯","Jiamusi"},
        {"鸡西","Jixi"},
        {"鹤岗","Hegang"},
        {"双鸭山","Shuangyashan"},
        {"牡丹江","Mudanjiang"},
        {"宜春","Yichun"},
        {"七台河","Qitaihe"},
        {"黑河","Heihe"},
        {"绥化","Suihua"},
        {"长春","Changchun"},
        {"吉林","Jilin"},
        {"四平","Siping"},
        {"辽源","Liaoyuan"},
        {"通化","Tonghua"},
        {"白山","Baishan"},
        {"松原","Songyuan"},
        {"白城","Baicheng"},
        {"沈阳","Shenyang"},
        {"大连","Dalian"},
        {"鞍山","Anshan"},
        {"抚顺","Fushun"},
        {"本溪","Benxi"},
        {"丹东","Dandong"},
        {"锦州","Jinzhou"},
        {"营口","Yingkou"},
        {"阜新","Fuxin"},
        {"辽阳","Liaoyang"},
        {"盘锦","Panjin"},
        {"铁岭","Tieling"},
        {"朝阳","Chaoyang"},
        {"葫芦岛","Huludao"},
        {"石家庄","Shijiazhuang"},
        {"唐山","Tangshan"},
        {"邯郸","Handan"},
        {"秦皇岛","Qinghuangdao"},
        {"保定","Baoding"},
        {"张家口","Zhangjiakou"},
        {"承德","Chengde"},
        {"廊坊","Langfang"},
        {"沧州","Cangzhou"},
        {"衡水","Hengshui"},
        {"邢台","Xingtai"},
        {"济南","Jinan"},
        {"青岛","Qingdao"},
        {"淄博","Zibo"},
        {"枣庄","Zaozhuang"},
        {"东营","Dongying"},
        {"烟台","Yantai"},
        {"潍坊","Weifang"},
        {"济宁","Jining"},
        {"泰安","Taian"},
        {"威海","Weihai"},
        {"日照","Rizhao"},
        {"莱芜","Laiwu"},
        {"临沂","Linyi"},
        {"德州","Dezhou"},
        {"聊城","Liaocheng"},
        {"菏泽","Heze"},
        {"滨州","Binzhou"},
        {"南京","Nanjing"},
        {"镇江","Zhenjiang"},
        {"常州","Changzhou"},
        {"无锡","Wuxi"},
        {"宿州","Suzhou"},
        {"徐州","Xuzhou"},
        {"连云港","Lianyungang"},
        {"淮安","Huaian"},
        {"盐城","Yancheng"},
        {"扬州","Yangzhou"},
        {"台州","Taizhou"},
        {"南通","Nantong"},
        {"宿迁","Suqian"},
        {"合肥","Hefei"},
        {"蚌埠","Bengbu"},
        {"芜湖","Wuhu"},
        {"淮南","Huainan"},
        {"亳州","Bozhou"},
        {"阜阳","Fuyang"},
        {"淮北","Huaibei"},
        {"滁州","Chuzhou"},
        {"安庆","Anqing"},
        {"巢湖","Chaohu"},
        {"马鞍山","Maanshan"},
        {"宣城","Xuancheng"},
        {"黄山","Huangshan"},
        {"池州","Chizhou"},
        {"铜陵","Tongling"},
        {"杭州","Hangzhou"},
        {"嘉兴","Jiaxing"},
        {"湖州","Huzhou"},
        {"宁波","Ningbo"},
        {"金华","Jinhua"},
        {"温州","Wenzhou"},
        {"丽水","Lishui"},
        {"绍兴","Shaoxing"},
        {"衢州","Quzhou"},
        {"舟山","Zhoushan"},
        {"抚州","Fuzhou"},
        {"厦门","Xiamen"},
        {"泉州","Quanzhou"},
        {"三明","Sanming"},
        {"南平","Nanping"},
        {"漳州","Zhangzhou"},
        {"莆田","Putian"},
        {"宁德","Ningde"},
        {"龙岩","Longyan"},
        {"广州","Guangzhou"},
        {"深圳","Shenzhen"},
        {"汕头","Shantou"},
        {"惠州","Huizhou"},
        {"珠海","Zhuhai"},
        {"揭阳","Jieyang"},
        {"佛山","Foshan"},
        {"河源","Heyuan"},
        {"阳江","Yangjiang"},
        {"茂名","Maoming"},
        {"湛江","Zhanjiang"},
        {"梅州","Meizhou"},
        {"肇庆","Zhaoqing"},
        {"韶关","Shaoguan"},
        {"潮州","Chaozhou"},
        {"东莞","Dongguan"},
        {"中山","Zhongshan"},
        {"清远","Qingyuan"},
        {"江门","Jiangmen"},
        {"汕尾","Shanwei"},
        {"云浮","Yunfu"},
        {"海口","Haikou"},
        {"三亚","Sanya"},
        {"昆明","Kunming"},
        {"曲靖","Qujing"},
        {"玉溪","Yuxi"},
        {"保山","Baoshan"},
        {"昭通","Zhaotong"},
        {"丽江","Lijiang"},
        {"普洱","Puer"},
        {"临沧","Lincang"},
        {"贵阳","Guiyang"},
        {"六盘水","Liupanshui"},
        {"遵义","Zunyi"},
        {"安顺","Anshun"},
        {"成都","Chengdu"},
        {"绵阳","Mianyang"},
        {"德阳","Deyang"},
        {"广元","Guangyuan"},
        {"自贡","Zigong"},
        {"攀枝花","Panzhihua"},
        {"乐山","Leshan"},
        {"南充","Nanchong"},
        {"内江","Neijiang"},
        {"遂宁","Suining"},
        {"广安","Guangan"},
        {"泸州","Luzhou"},
        {"达州","Dazhou"},
        {"眉山","Meishan"},
        {"宜宾","Yibin"},
        {"雅安","Yaan"},
        {"资阳","Ziyang"},
        {"长沙","Changsha"},
        {"株洲","Zhuzhou"},
        {"湘潭","Xiangtan"},
        {"衡阳","Hengyang"},
        {"岳阳","Yueyang"},
        {"郴州","Chenzhou"},
        {"永州","Yongzhou"},
        {"邵阳","Shaoyang"},
        {"怀化","Huaihua"},
        {"常德","Changde"},
        {"益阳","Yiyang"},
        {"张家界","Zhangjiajie"},
        {"娄底","Loudi"},
        {"武汉","Wuhan"},
        {"襄樊","Xiangfan"},
        {"宜昌","Yichang"},
        {"黄石","Huangshi"},
        {"鄂州","Ezhou"},
        {"随州","Suizhou"},
        {"荆州","Jingzhou"},
        {"荆门","Jingmen"},
        {"十堰","Shiyan"},
        {"孝感","Xiaogan"},
        {"黄冈","Huanggang"},
        {"咸宁","Xianning"},
        {"郑州","Zhengzhou"},
        {"洛阳","Luoyang"},
        {"开封","Kaifeng"},
        {"漯河","Luohe"},
        {"安阳","Anyang"},
        {"新乡","Xinxiang"},
        {"周口","Zhoukou"},
        {"三门峡","Sanmenxia"},
        {"焦作","Jiaozuo"},
        {"平顶山","Pingdingshan"},
        {"信阳","Xinyang"},
        {"南阳","Nanyang"},
        {"鹤壁","Hebi"},
        {"濮阳","Puyang"},
        {"许昌","Xuchang"},
        {"商丘","Shangqiu"},
        {"驻马店","Zhumadian"},
        {"太原","Taiyuan"},
        {"大同","DaTong"},
        {"忻州","Xinzhou"},
        {"阳泉","Yangquan"},
        {"长治","Changzhi"},
        {"晋城","Jincheng"},
        {"朔州","Shuozhou"},
        {"晋中","Jinzhong"},
        {"运城","Yuncheng"},
        {"临汾","Linfen"},
        {"吕梁","Lvliang"},
        {"西安","Xian"},
        {"咸阳","Xianyang"},
        {"铜川","Tongchuan"},
        {"延安","Yanan"},
        {"宝鸡","Baoji"},
        {"渭南","Weinan"},
        {"汉中","Hanzhoung"},
        {"安康","Ankang"},
        {"商洛","Shangluo"},
        {"兰州","Lanzhou"},
        {"天水","Tianshui"},
        {"平凉","Pingliang"},
        {"酒泉","Jiuquan"},
        {"嘉峪关","Jiayuguan"},
        {"金昌","Jinchang"},
        {"白银","baiyiin"},
        {"武威","Wuwei"},
        {"张掖","Zhangye"},
        {"庆阳","Qingyang"},
        {"定西","Dingxi"},
        {"陇南","Longnan"},
        {"西宁","Xining"},
        {"南昌","Nanchang"},
        {"九江","Jiujiang"},
        {"赣州","Ganzhou"},
        {"吉安","Jian"},
        {"鹰潭","Yingtan"},
        {"上饶","Shangrao"},
        {"萍乡","Pingxiang"},
        {"景德镇","Jingdezhen"},
        {"新余","Xinyu"}
};