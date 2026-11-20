#pragma once
#include "character.hpp"
#include <memory>
#include <string>

namespace rl {

    class Skeleton : public Character {
    private:
        std::shared_ptr<std::string> m_loot;

    public:
        Skeleton();
        Skeleton(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol);
        Skeleton(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol, std::string loot);
        Skeleton(const Skeleton& other);
        Skeleton(Skeleton&& other) noexcept;
        Skeleton& operator=(const Skeleton& other);
        Skeleton& operator=(Skeleton&& other) noexcept;
        virtual ~Skeleton();

        virtual void onSpawned() override;

        std::string getLoot() const;
        std::string getFirstLoot() const;
        bool hasLoot(const std::string& item) const;
        bool lootEquals(const std::string& expected) const;
        void addLoot(const std::string& item);
        void takeLootFrom(const Skeleton& source);
        void shareLootWith(Skeleton& other) const;

        virtual std::unique_ptr<Character> clone() const override;
    };

}