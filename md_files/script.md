#  <设定> 
> 更加定量具体一些  或许算是杂七杂八的设定
###  0.设定中提出的问题
- 
    - 姓名采取固定化，还是玩家可以自己设定？
    > 自己设定， 限制一些条件和屏蔽词。
    
    - 游戏进度保存？
    > 暂定，如果做到，作为加分项。
    
    - 动作设定 是否包含跑的动作，以及跑动的时候是否消耗精力，还是精力仅仅用于组合技。
    > 目前贴图实现，仍以游戏的整体实现为主。
    
    - 速度设定还是是要看看地图在精确化。
    
    - 怪物打败后会不会刷新，重新出现？
    >**进行刷新**  
    >但同时要记录已经打败的数量不能减少。

    - 村镇的数量？ 位置？ `个人建议 一个 皇宫附近`
    
    - 对于没有任务发布的 或者已经完成任务的 村民，如何处理。 
    > 可以对话，但不再发布任务

    - 武器的形式？ 魔法戒指，水晶，宝石。
        -  [ ] 魔法戒指 攻击力+10 
        -  [ ] 魔力水晶 攻击力+15
        -  [ ] 魔法卷轴 攻击力+20

    - 装备 目前为设定为 头部，上衣，裤子
    > `或者将三者整合为套装？或者 简化把鞋子和裤子看作一部分？`
    > 上身 裤子 鞋子 

    - 技能设定 `进行了部分量化`  
    > 组合技 *通过按键组合触发*  
    ~~- 对于攻击系统，进行敌方和友方的判定 `个人建议`~~
  
    - 一些食物类的采集物是否要归为料理类 可以食用？ 
     > 放置于背包 用于回血
     > 此外 背包界面可以时间停止

    - 特殊物品是什么？`自行设定了一个公主留下的线索的特殊物品` 
    > 集齐钥匙，然后boss战区域设置为迷宫或禁区，集齐钥匙打开。

    - 背包界面 简单草图如下，  也可以竖着放，后期调整。
    > 人物 装备格子 [ ] [ ] [ ]  
    > 人物 武器格子 [ ] [ ] [ ]
    > ***
    > 背包大小 ---可以先用宏变量设置为10 后期在进行修改。
    > [ ] [ ] [ ] [ ] [ ]
    > [ ] [ ] [ ] [ ] [ ]    
***
## 1.背景
-   基础设定
    - 背景：高魔世界，武器技能食品等可以被交易。
    >此处为了避免货币，通过完成任务来获取奖励物品
 
    - 依据国产动画《纳米神兵》内的元素相克的设定，金>木>土>水>火>金  
    > 相邻两个元素相克。不相邻元素不考虑其影响。
      
    - 世界根据五个元素粗略划分。
    > 此处根据地图进一步完善

    - 武器主要用于增加攻击数值。更倾向于没有冷兵器的魔法攻击。 
    > 此处武器可以理解为魔法水晶之类的或许更为恰当。
    
    - 故事（主线任务）设定：常见的勇者救公主故事。
        进入游戏后，勇者处于皇宫，和国王大臣等对话，了解到公主被魔物抓走，接受救公主的主线任务。然后闯荡世界。
        以动画或者文本方式实现？

    - 人物、武器、任务、可互动对象 等更精细的划分详见下文。

***

## 2.人物：
- <主控>：
    - 勇者：
        - 玩家自行选择：元素属性，外貌性别。
            - 元素属性 ： 金/木/水/火/土
            - 外貌：（给出选项进行选择而不是玩家自己捏）
                - 长发、短发
                - 发色 黑、白、金等等
                - 肤色 黄、白、黑
                - 等等
            - 服装：(同上)
                - 初始服装 不同种类贴图。 
        -  对其设定初始装备和初始技能（1级魔法攻击 ）和初始等级（0级）初始血量（20）初始精力（20），初始速度设定（slow）。
        -  等级划分为5级，每攻克一种元素地区相应升一个等级。血量（+20），精力对应提升（+20）。
         
        -  个人攻击力 = 武器攻击力 + 技能对应攻击数值 + `等级对应基础攻击力(个人想法 待定 )` 
        - 精力用于组合攻击（如多个技能结合） `组合攻击种类 详见程设期末会议记录 `
        -精力按照时间回复。
        - 背包设定：
            - 装备 （头部，上衣，裤子，鞋子）用于增加  防御。
            - 武器（随身携带三个及以下武器）
                - 用于增加 攻击。 
                - 不采用冷兵器。 
            - 技能 （可以随身携带三个技能）
            - 采集物品 最多20个
            >对背包大小进行限制 （共30个格子，一个武器站一个格子，但是采集物一个格子里可以放多个）
- NPC :
    - 友方 （不可攻击）
        - 公主：
            - 命名：`QUEEN`  
            - 更多的是背景板的作用。
        - 国王：
            - 命名： `KING`
            - 主线任务发布者。
        - 大臣 ：
            - 命名： `MINISTER`
            - 装备升级。
        - 村民：（人数：三到五人？）
            - 发布任务的人（衣物装备、武器、料理、技能 各一人） 
            - 命名 `ClothesProvider` `WeaponProvider ` `FoodProvider ` `SkillProvider`
            > 从其获取装备， 武器，补给，技能等等
            -  对于没有任务发布的，或者已经完成发布任务（`或许可以采取重复发布任务的方式`  ）的村民。
            >  背景板 或者 设置简单的聊天框 如“不知道公主现在怎么样了”，“希望公主能平安无事啊”等有关主线剧情的语句，或者 “我家里种的菜快好了”“欢迎你来我家做客”的家常语句。
    - 敌方
        - 怪物：按五种属性划分。
        - 等级：为简化 设置为低级和高级 
        - 命名简单设置为 `低/高+级+元素名+怪物` 
        - 为简化，暂且不给怪物可以持有武器以及装备的设定
        - 低级怪物 
            - 攻击方式 2种 :1级魔法攻击和2级魔法攻击
            - 血量：25
            - 采取近距离攻击方式
        -  高级怪物
            - 攻击方式 2种 ：2级魔法攻击和3级魔法攻击 
            - 血量 ：50
        > 怪物与勇者的等级对应关系稍后考虑 。或者不对应，攻击伤害更多取决于 攻击力大小和元素相克的设定 而不是等级。

***
## 3.装备（此处指衣物、武器、技能）：
> 个人认为耐久度实现较为复杂，暂且待定。
- 装备 `（头部，上衣，裤子，鞋子）主要用于增加  防御`     
    - 上衣
        - 初始上衣： 防御 + 3
        - 盔甲上衣： 防御 +5
    - 裤子 
        - 初始裤子： 防御 + 3
        - 盔甲裤： 防御 +5
    - 鞋子 
        - 初始鞋子: 防御 + 3
        - 急速鞋： 速度翻倍 防御 +5 
    > 所有装备可以进行升级，升级后防御力翻倍。最高为三级。或者不考虑平衡性，不设置上限。

    > 装备通过大臣处升级。可以记录一下打败怪物的数量，如果超过多少就可以升级。
- 武器 同样可以升级
    - 用于增加 攻击。 
    - 不采用冷兵器。
    - 或许可以采用 `个人想法，不一定非要这几个`
    -   魔法戒指 攻击力+10 
    -   魔力水晶 攻击力+15
    -   魔法卷轴 攻击力+20
- 
- 技能 
    - 1级魔法攻击 伤害值 +10 （近距离）
    - 2级魔法攻击 伤害值 +10 （远距离）
    - 3级魔法攻击 伤害值 +20 （近距离）
    > 距离判定还是要根据地图

    - 加速技能 速度*2 （如果怪物能够猛冲，勇者也要会加速躲避）
    - 烹饪技能 例如将水果烹饪后可以回复的血量增加。
    - 组合技能 
        - （2级+2级+1级 触发暴击 总伤害+30）
        - （2级+2级+3级 触发暴击 总伤害+40）

    > 感觉这个不算单独的技能，
***
## 4.任务：
- 主线任务
    - 勇者救公主 
    - 分阶段完成，五个区域 任务不分先后。
  
- 支线任务（金木水火土）
    - 金元素区域 ：村民的支线任务 走迷宫，寻找宝藏。
     > 如 与村民交互，对话框“勇者，我在XX发现一个迷宫，我很好奇但是有些怪物，能请您去探索一下吗”，去探索迷宫，打败迷宫中的怪物，获取宝物（如2级技能），和村民交互后，得到一份料理感谢。
    
    - 木元素区域 ：村民的支线任务 采集 换取
    > 如 与村民交互 对话框“勇者，我需要一些xx的水果/草药，但是那里存在怪物，能帮我带一些回来吗”， 前往该区域，打怪物，得到采集物，和村民交互后，得到一份/套 装备感谢。
    
    - 水元素区域 ：村民的支线任务 钓鱼
    > 如 与村民交互 对话框“勇者，我需要一条鱼，但是那里存在怪物，能帮我一下吗”， 前往该区域，打怪物，钓鱼，和村民交互后，得到3级技能感谢。

    - 火元素区域 ：打怪
    > 如 与村民交互 对话框“勇者，我曾经在火元素区域生活，但是现在那里存在怪物，能帮我驱逐他们吗”， 前往该区域，打怪物，和村民交互后，得到武器感谢。

    - 土元素区域 ： 寻找丢失的物件 （本质上还是打怪）
    -> 如 与村民交互 对话框“勇者，我曾经去土元素区域探索，丢失了一件武器，能帮我找回来吗”， 前往该区域，打怪物，怪物身上掉落武器，和村民交互后，得到武器感谢。
 
***
## 5.交互对象：
- 采集：
  > 为了简化，就将采集物品用大类的方式 命名，例如，苹果梨香蕉等不做区分，统称为水果。
    - 自然类 
      1.不可食用
      - 树木  `TREE`   
      > 交互方式 砍伐 （但是用魔法砍伐？） 
      
      - 木头  `WOOD`  `取火用于烹饪的交互  `**待定**
      - 石头  `STONE` 
      > 在背包外
      >  1、拾取（放入背包） 2、举起（举到头顶）（但如果这样的话，就还要做一个扔出的动作，**待定**）
      >***
      > 在背包内
      >  1、扔掉（拿出背包，放到地面） 2、举起（**同上**）

      2.可食用
      - 水果  `FRUIT` 血量+5
      - 蔬菜  `vegetable`血量+7
      - 草药  `HERB`  血量+10
      - 鱼    `FISH`
      > 在背包外
      >  1、拾取 
      > *** 
      > 在背包内
      >  1、食用 2、烹饪 

    - 料理
      - 水果料理  血量+10
      - 草药料理  血量+20
      > 食用
      
    - 怪物掉落类
      - 武器  
      - 装备
      > 1、拾取 2、佩戴 3、扔掉
      - 怪物精华 （可以作为任务兑换品）
      > 拾取

   
    -  特殊物品
       -  公主留下的传送水晶碎片？`只是一个命名，可以再定` 
       >  假设在打败高级怪物后获得，最终线索全部找到后，生成一个锚点传送到公主被关押的地方，最终BOSS战。
- NPC：详见 人物板块 ***包括友方和敌方***
***
***
## 6.剧情-对话
**设定**
+  ***勇者***     
+  玩家自定义 <u>外貌、元素属性</u>

**剧情开端**`主线`
+ 国王："你就是揭榜要去寻找失踪的公主的勇者吗，年轻人。"
+ 勇者："是的。我，<u>勇者的名字</u>，希望去寻找公主。"
+ 国王："既然你有这样的勇气，那我来告诉你公主的线索。"
+ （国王从桌子上拿起一封破旧的信件，缓缓展开）
> 可以做一个信缓缓打开的小动画，或单纯的文本框
+ 国王："公主消失前只留下一封书信。信中提到她被怪物抓走，但幸而她在五大区域留下了线索，只有找到这些线索，才能找到公主的下落。"
> 五个区域 具体命名还是看地图做成什么样吧。
+ 国王："你的任务是前往这五大区域，寻找她留下的线索。每个区域都藏有与元素相关的怪物，只有证明你的勇气和智慧，才能获得通往公主的真正线索。"
+ （国王的脸上流露出一丝忧虑）
+ 国王："我担心公主可能已经遭遇不测，被关押在某个地方。她的失踪可能与怪物有关。你必须小心行事。"

+ 勇者："我会不惜一切代价找到公主，拯救她和王国！"
+ （勇者握紧拳头，决心已定）

**每找到一个线索，与国王交互**`主线`
+ 国王："真高兴你找到了一个线索，目前你已经找到了<u>x</u>个线索，还有<u>5-x</u>个线索，加油吧，年轻人，希望我的女儿早日归来。"
**找到全部线索**   `主线`
+ 国王："太好了，我们找到了全部的线索，让我们把它们组合起来。"
>生成一个传送点点
+ 国王："这，这是，传送点，这极有可能会传送到公主那边去，年轻人，你做好准备去拯救公主了吗"
> 勇者："是的我做好准备了"
>> 传送到最终的竞技场打BOSS ,救公主。

> 勇者："不，我还没有准备好"
>> 国王："希望你尽快做好准备啊，勇者。"

**与国王交互** `一般情况下`
+ 国王："你如果需要帮助可以去找大臣，他会帮你升级的。"

**与大臣交互**
- 先判断是否能升级 （记录打败怪物的数量）
+ 能，大臣："勇者，您现在可以升级装备和等级了，让我来帮助提高您的战力吧。"
- 不能，大臣："勇者，您现在的历练还不够，请继续去冒险吧。" 