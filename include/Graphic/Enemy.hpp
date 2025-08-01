#pragma once
#include <Graphic/Base.hpp>
#include <Utility/Logger.hpp>
#include <Graphic/Sprite.hpp>
class Enemy : public GraphicBase
{
public:
        Enemy(Engine &g_Engine);
protected:
        sf::RectangleShape m_Shape;
        sf::IntRect m_TextureRect;
        int m_Index;
        int m_HP;
        Engine& m_Engine;
        float m_Radius;
        int m_LastAttackID;

};

class Slime: public Enemy
{
private:
        EventDispatcher::EventListener m_Listener;
public:
        Slime(Engine &g_Engine);
        ~Slime() = default;
        bool Update(const sf::Time& DT) override;
        bool HandleEvent(std::shared_ptr<BaseEvent> Event);
        bool HandleInput(const sf::Event& Event) override;
        bool FixLagUpdate(const sf::Time&DT) override;
        void SetPosition(const sf::Vector2f& position) override;
        bool SetIntRect (const sf::IntRect& rect);
        void SetScale(const sf::Vector2f& scale) override;
        void draw(sf::RenderTarget &Target, sf::RenderStates states) const override;
        GlobalEventType GetCollisionEventType() const override;
        float GetYAxisPoint() override;

};
