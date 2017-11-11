#include <memory>

#include <libOlga/App.hh>

class MyApp : public App {
  void setup() override {}
};

int main(int argc, char **argv) {
  const std::unique_ptr<App> app = std::make_unique<MyApp>();
  app->configure(argc, argv);
  app->runMainLoop();
}
