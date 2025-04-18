#pragma once
#include "mc/_HeaderOutputPredefine.h"
#include "mc/world/item/Item.h"

class Actor;
class BlockPos;
class BlockSource;
class Container;
class InteractionResult;
class ItemStack;
class ItemStackBase;
class Vec3;

class FireChargeItem : public ::Item {
public:
    FireChargeItem() : Item("minecraft:fire_charge", 0) {}

    virtual ::Actor*
    createProjectileActor(::BlockSource& region, ::ItemStack const&, ::Vec3 const& pos, ::Vec3 const& direction) const;

    virtual bool dispense(::BlockSource& region, ::Container& container, int slot, ::Vec3 const& pos, uchar face) const;

    virtual bool isDestructive(int) const;

    virtual ::InteractionResult
    _useOn(::ItemStack& instance, ::Actor& entity, ::BlockPos pos, uchar face, ::Vec3 const& clickPos) const;

    virtual bool _calculatePlacePos(::ItemStackBase&, ::Actor& actor, uchar& face, ::BlockPos& pos) const;

    virtual ~FireChargeItem() = default;

public:
    MCAPI bool _tryLightPortal(::Actor& actor, ::BlockPos actionPos) const;
};
