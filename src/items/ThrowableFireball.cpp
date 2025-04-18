#include <gmlib/mod/item/CustomItemRegistry.h>
#include <gmlib/mod/item/base/ICustomItem.h>
#include <mc/deps/core/math/Vec3.h>
#include <mc/legacy/ActorUniqueID.h>
#include <mc/world/Container.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/actor/ActorDefinitionIdentifier.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/actor/projectile/Throwable.h>
#include <mc/world/gamemode/InteractionResult.h>
#include <mc/world/level/BlockPos.h>
#include <mc/world/level/BlockSource.h>

#include "FireChargeItem.h"

using namespace gmlib::mod;

// 要让客户端行为正常，必须继承 GMLIB 提供的基类
class ThrowableFireball : public ICustomItem {
    // 避免菱形继承问题，使用成员而非多继承
    FireChargeItem mOriginItem;

public:
    ThrowableFireball() : ICustomItem("minecraft:fire_charge"), mOriginItem() { setDescriptionId("fireball"); }

    ItemIcon getIcon() const override { return "fireball"; }

    std::string getDisplayName() const override { return "item.fireball.name"; }

    // 重写为可投掷的物品
    bool isThrowable() const override { return true; }

    int getUseDuration() const override { return 10; }

    int getCooldownTime() const override { return 10; }

    std::string getCooldownCategory() const override { return "minecraft:fire_charge"; }

    // 使用原版行为
    ::Actor* createProjectileActor(
        ::BlockSource&     region,
        ::ItemStack const& item,
        ::Vec3 const&      pos,
        ::Vec3 const&      direction
    ) const override {
        return mOriginItem.createProjectileActor(region, item, pos, direction);
    }

    bool
    dispense(::BlockSource& region, ::Container& container, int slot, ::Vec3 const& pos, uchar face) const override {
        return mOriginItem.dispense(region, container, slot, pos, face);
    }

    bool isDestructive(int a) const override { return mOriginItem.isDestructive(a); }

    ::InteractionResult
    _useOn(::ItemStack& instance, ::Actor& entity, ::BlockPos pos, uchar face, ::Vec3 const& clickPos) const override {
        return mOriginItem._useOn(instance, entity, pos, face, clickPos);
    }

    bool _calculatePlacePos(::ItemStackBase& item, ::Actor& actor, uchar& face, ::BlockPos& pos) const override {
        return mOriginItem._calculatePlacePos(item, actor, face, pos);
    }

    ::ItemStack& use(::ItemStack& item, ::Player& player) const override {
        player.useItem(item, ItemUseMethod::Throw, true);
        player.swing();
        if (auto projectile =
                Throwable::spawnPlayerProjectile(ActorDefinitionIdentifier("minecraft:small_fireball"), player)) {
            projectile->setOwner(player.getOrCreateUniqueID());
            player.startCooldown(this, false);
        }
        return item;
    }
};

GMLIB_REGISTER_ITEM(ThrowableFireball);