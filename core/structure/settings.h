#ifndef AV_TEST_COMPARATOR_CORE_STRUCTURE_SETTINGS_H
#define AV_TEST_COMPARATOR_CORE_STRUCTURE_SETTINGS_H
namespace core::structure {
    class settings {
        settings() {
            error.display = false;
            debug.display = false;
        }

    public:
        static settings *instance;

        static settings *getInstance() {
            if (!instance)
                instance = new settings;
            return instance;
        }

        struct error {
            bool display;
        } error{};

        struct debug {
            bool display;
        } debug{};
    };
}
#endif //AV_TEST_COMPARATOR_CORE_STRUCTURE_SETTINGS_H
