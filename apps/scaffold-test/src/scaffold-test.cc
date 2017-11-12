#include <memory>

#include <libOlga/App.hh>

class MyApp : public App {
  void setup() override {}
  std::string appName() const override { return "scaffold-test"; }
};

int main(int argc, char **argv) {
  const std::unique_ptr<App> app = std::make_unique<MyApp>();
  app->configure(argc, argv);
  app->runMainLoop();
}
