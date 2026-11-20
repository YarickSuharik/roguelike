#include "skeleton.hpp"
#include "ai_controller.hpp"
#include <iostream>
#include <memory>
#include <utility>

namespace rl {

    Skeleton::Skeleton()
        : Skeleton("Skeleton", Position(0, 0), std::weak_ptr<World>(), "S") {
        std::cout << "[Skeleton] Default constructor\n";
    }

    Skeleton::Skeleton(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol)
        : Skeleton(std::move(name), startPos, worldContext, std::move(symbol), std::string()) {}

    Skeleton::Skeleton(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol, std::string loot)
        : Character(std::move(name), startPos, worldContext, std::move(symbol)),
          m_loot(std::make_shared<std::string>(std::move(loot))) {
        std::cout << "[Skeleton] Constructor: " << getActorName() << "\n";
    }

    Skeleton::Skeleton(const Skeleton& other)
        : Character(other), m_loot(other.m_loot) {
        std::cout << "[Skeleton] Copy constructor: " << getActorName() << "\n";
    }

    Skeleton::Skeleton(Skeleton&& other) noexcept
        : Character(std::move(other)), m_loot(std::move(other.m_loot)) {
        std::cout << "[Skeleton] Move constructor: " << getActorName() << "\n";
    }

    Skeleton& Skeleton::operator=(const Skeleton& other) {
        if (this != &other) {
            Character::operator=(other);
            m_loot = other.m_loot;
        }

        std::cout << "[Skeleton] Copy assignment: " << getActorName() << "\n";
        return *this;
    }

    Skeleton& Skeleton::operator=(Skeleton&& other) noexcept {
        if (this != &other) {
            Character::operator=(std::move(other));
            m_loot = std::move(other.m_loot);
        }

        std::cout << "[Skeleton] Move assignment: " << getActorName() << "\n";
        return *this;
    }

    Skeleton::~Skeleton() {
        std::cout << "[Skeleton] Destructor: " << getActorName() << "\n";
    }

    void Skeleton::onSpawned() {
        setController(std::make_unique<AIController>());
    }

    std::string Skeleton::getLoot() const {
        return m_loot ? *m_loot : std::string();
    }

    std::string Skeleton::getFirstLoot() const {
        if (!m_loot) {
            return std::string();
        }

        std::string::size_type separator = m_loot->find(' ');

        if (separator == std::string::npos) {
            return *m_loot;
        }

        return m_loot->substr(0, separator);
    }

    bool Skeleton::hasLoot(const std::string& item) const {
        if (!m_loot) {
            return false;
        }

        return m_loot->find(item) != std::string::npos;
    }

    bool Skeleton::lootEquals(const std::string& expected) const {
        return getLoot() == expected;
    }

    void Skeleton::addLoot(const std::string& item) {
        if (!m_loot) {
            m_loot = std::make_shared<std::string>();
        }

        if (!m_loot->empty()) {
            *m_loot += " ";
        }

        *m_loot += item;
    }

    void Skeleton::takeLootFrom(const Skeleton& source) {
        if (this == &source) {
            return;
        }

        addLoot(source.getLoot());
    }

    void Skeleton::shareLootWith(Skeleton& other) const {
        other.takeLootFrom(*this);
    }

    // поверхностная копия делит m_loot с оригиналом, поэтому клону строку отсоединяем
    std::unique_ptr<Character> Skeleton::clone() const {
        auto copy = std::make_unique<Skeleton>(*this);

        if (m_loot) {
            copy->m_loot = std::make_shared<std::string>(*m_loot);
        }

        return copy;
    }

}