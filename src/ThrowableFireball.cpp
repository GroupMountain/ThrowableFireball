#include "Global.h"
#include <GMLIB/Server/ItemStackAPI.h>
#include <GMLIB/Server/PlayerAPI.h>


void ThrowableFireball() {
    ll::event::EventBus::getInstance().emplaceListener<ll::event::player::PlayerUseItemEvent>(
        [](ll::event::player::PlayerUseItemEvent& event) {
            auto pl   = (GMLIB_Player*)&event.self();
            auto item = (GMLIB_ItemStack*)pl->getMainHandSlot();
            if (item->getTypeName() == "minecraft:fire_charge") {
                auto fireball = pl->shootProjectile("minecraft:small_fireball", 2, 3);
                if (fireball) {
                    item->removeCount(1);
                    pl->refreshInventory();
                    event.cancel();
                }
            }
        },
        ll::event::EventPriority::High
    );
}