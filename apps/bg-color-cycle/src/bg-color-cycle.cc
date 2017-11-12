#include <cmath>
#include <memory>

#include <libOlga/App.hh>
#include <libOlga/Color.hh>

Color colors[5] = {Color(1.0, 1.0, 1.0, 1.0), Color(0.0, 0.0, 0.0, 1.0),
                   Color(1.0, 0.0, 0.0, 1.0), Color(0.0, 1.0, 0.0, 1.0),
                   Color(0.0, 0.0, 1.0, 1.0)};

class BgColorCycle : public App {
  void setup() override { setBackgroundColor(colors[0]); }
  std::string appName() const override { return "bg-color-test"; }

  void renderFrame(__attribute__((unused)) Double atTime,
                   U64 frameNumber) override {
    const long color_index = std::lround(frameNumber / 120) % 5;
    setBackgroundColor(colors[color_index]);
  }
};

int main(int argc, char **argv) {
  const std::unique_ptr<App> app = std::make_unique<BgColorCycle>();
  app->configure(argc, argv);
  app->runMainLoop();
}
