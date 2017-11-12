#include <memory>

#include <libOlga/App.hh>
#include <libOlga/Color.hh>

class MyApp : public App {
  void setup() override { setBackgroundColor(Color(0.0, 1.0, 0.0, 1.0)); }
  std::string appName() const override { return "scaffold-test"; }

  // void renderFrame (double atTime, int64_t frameNumber) override {
  //   std::cout << atTime << '.' << frameNumber << std::endl;
  // }
};

int main(int argc, char **argv) {
  const std::unique_ptr<App> app = std::make_unique<MyApp>();
  app->configure(argc, argv);
  app->runMainLoop();
}
