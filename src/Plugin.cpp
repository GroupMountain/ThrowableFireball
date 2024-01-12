#include "Plugin.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace plugin {

Plugin::Plugin(ll::plugin::NativePlugin& self) : mSelf(self) {
    // Code for loading the plugin goes here.
}

bool Plugin::enable() {
    // Code for enabling the plugin goes here.
    auto minLibVersion = SemVersion(0, 4, 2, "", "");
    if (!GMLIB::Version::checkLibVersionMatch(minLibVersion)) {
        logger.error("Fail to load ThrowableFireball!");
        logger.error("GMLIB Version is outdated! Please update your GMLIB!");
        logger.error(
            "Current GMLIB Version {}, Required Lowest GMLIB Version {}",
            GMLIB::Version::getLibVersionString(),
            minLibVersion.asString()
        );
        return false;
    }
    ThrowableFireball();
    logger.info("ThrowableFireball loaded successfully!");
    logger.info("Author: Tsubasa6868");
    logger.info("Repository: https://github.com/GroupMountain/ThrowableFireball");
    return true;
}

bool Plugin::disable() {
    // Code for disabling the plugin goes here.
    return true;
}

} // namespace plugin