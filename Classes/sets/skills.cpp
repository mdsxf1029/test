#include"skills.h" 
#include"BattleScene.h"
//技能类
class Skill;

Skill::Skill(const SkillInfo& info) :_info(info) {}                                      //构造函数
Skill::~Skill() {}      											                     //析构函数    

/*朝某个方向发射特效*/
float Skill::cast(cocos2d::Node* caster, const cocos2d::Vec2& targetPos) {
    if (!caster) return false;
	Vec2 _skillDirection = targetPos - caster->getPosition();                           // 计算从玩家到鼠标点击位置的方向向量
    _skillDirection.normalize();                                                        // 将方向向量归一化
    float angle = std::atan2(_skillDirection.y, _skillDirection.x);                     // 计算从玩家到鼠标点击位置的角度（弧度）
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);                                // 将弧度转换为角度

    return angleInDegrees;
}

/*判断是否在攻击范围内*/
bool Skill::isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos, const cocos2d::Vec2& clickPos) const {
    float distance = casterPos.distance(targetPos);//计算距离
    Vec2 _skillDirection = clickPos - casterPos;                                        // 计算从玩家到鼠标点击位置的方向向量
    Vec2 _enemyDirection = targetPos - casterPos;										// 计算从玩家到敌人的方向向量

    _skillDirection.normalize();                                                        // 将方向向量归一化
    _enemyDirection.normalize();                                                        // 将方向向量归一化             
    /*计算从玩家到鼠标点击位置的角度（弧度）*/ 
    float angle = std::atan2(_skillDirection.y, _skillDirection.x);                     // atan2返回的是弧度   玩家到鼠标
    float enemyangle = std::atan2(_enemyDirection.y, _enemyDirection.x);                // atan2返回的是弧度   玩家到敌人
    /*将弧度转换为角度*/ 
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);                                // 转换为角度
    float enemyangleInDegrees = CC_RADIANS_TO_DEGREES(enemyangle);                      // 转换为角度
   
	float degreegap = abs(angleInDegrees - enemyangleInDegrees);                        //计算两个角度差值
	if (degreegap > 180)																//如果角度差值大于180
		degreegap = 360 - degreegap;                                                    //将大的角度差值转换为小的角度差值
	if (degreegap < _info.degreerange && distance <= _info.range)   		            //判断是否在攻击范围内 
        return true;
    else
        return false;
}
bool  Skill::isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos) const  //敌人攻击玩家
{
    float distance = casterPos.distance(targetPos);                                     //计算距离
	if (distance <= _info.range)														//判断是否在攻击范围内
        return true;
    else
        return false;
}
void Skill::setColor(ElementType type)
{
    switch (type)
    {
        case ElementType::Gold:
            _effect->setStartColor(Color4F(1.0f, 0.84f, 0.0f, 1.0f));                   // 更明亮的金色
            _effect->setEndColor(Color4F(0.85f, 0.65f, 0.13f, 0.7f));                   // 偏暗的金色，带透明度
            _effect->setStartColorVar(Color4F(0.1f, 0.1f, 0.0f, 0.0f));                 // 轻微的颜色变化
            break;

        case ElementType::Wood:
            _effect->setStartColor(Color4F(0.0f, 0.8f, 0.2f, 1.0f));                    // 自然的绿色
            _effect->setEndColor(Color4F(0.0f, 0.6f, 0.0f, 0.7f));                      // 深绿色，带透明度
			_effect->setStartColorVar(Color4F(0.0f, 0.1f, 0.1f, 0.0f));				    // 轻微的颜色变化
            break;

        case ElementType::Water:
            _effect->setStartColor(Color4F(0.0f, 0.5f, 1.0f, 1.0f));                    // 明亮的蓝色
            _effect->setEndColor(Color4F(0.0f, 0.3f, 0.8f, 0.7f));                      // 深蓝色，带透明度
			_effect->setStartColorVar(Color4F(0.0f, 0.1f, 0.1f, 0.0f));                 // 轻微的颜色变化  
            break;

        case ElementType::Fire:
            _effect->setStartColor(Color4F(1.0f, 0.2f, 0.0f, 1.0f));                    // 偏橙的红色
            _effect->setEndColor(Color4F(1.0f, 0.0f, 0.0f, 0.7f));                      // 纯红色，带透明度
			_effect->setStartColorVar(Color4F(0.1f, 0.1f, 0.0f, 0.0f)); 			    // 轻微的颜色变化 
            break;

        case ElementType::Earth:
            _effect->setStartColor(Color4F(0.6f, 0.4f, 0.2f, 1.0f));                    // 土黄色
            _effect->setEndColor(Color4F(0.4f, 0.3f, 0.1f, 0.7f));                      // 深褐色，带透明度
			_effect->setStartColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.0f));                 // 轻微的颜色变化
            break;

        default:
            break;
    }
}