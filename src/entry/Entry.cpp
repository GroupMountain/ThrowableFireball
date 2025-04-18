#include "entry/Entry.h"
#include "ll/api/mod/RegisterHelper.h"

namespace gm {

ThrowableFireball& ThrowableFireball::getInstance() {
    static ThrowableFireball instance;
    return instance;
}

bool ThrowableFireball::load() {
    getSelf().getLogger().info("ThrowableFireball loaded!");
    getSelf().getLogger().info("Author: GroupMountain");
    return true;
}

bool ThrowableFireball::enable() { return true; }

bool ThrowableFireball::disable() { return true; }

} // namespace gm

LL_REGISTER_MOD(gm::ThrowableFireball, gm::ThrowableFireball::getInstance());
