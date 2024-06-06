#ifndef CORE_H
#define CORE_H

namespace elementled {

struct appConfig{
    int width   = 0;
    int height  = 0;
    std::string title;
    std::string scene;
    std::string version;
};

    appConfig CreateApplication();
    void RunApplication(const appConfig& config);
    void PrintHelloWorld();
}
#endif // CORE_H
