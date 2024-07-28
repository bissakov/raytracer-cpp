#include <src/canvas.h>
#include <src/file_io.h>
#include <src/point_vector.h>
#include <src/test_suite.h>
#include <src/utils.h>
#include <tests/test_canvas.h>

#include <cmath>
#include <string>

void TestCanvas(TestFramework *framework) {
  framework->AddTest("Create canvas", []() -> bool {
    Canvas canvas = {10, 20};
    return AssertEq(canvas.width, 10) && AssertEq(canvas.height, 20);
  });

  framework->AddTest("Check all default canvas colors (black)", []() -> bool {
    Canvas canvas = {10, 20};
    Color black = {0, 0, 0};

    bool res = true;
    for (int i = 0; i < canvas.height; ++i) {
      for (int j = 0; j < canvas.width; ++j) {
        Pixel current_pixel = canvas.PixelAt(j, i);
        res = res && (current_pixel.color == black);
      }
    }

    return AssertEq(res, true);
  });

  framework->AddTest("Write color of the pixel", []() -> bool {
    Canvas canvas = {5, 10};
    Color red = {1, 0, 0};

    int x = 2;
    int y = 3;
    canvas.WritePixelColor(x, y, red);
    Pixel red_pixel = canvas.PixelAt(2, 3);

    return AssertEq(red_pixel.color, red) && AssertEq(red_pixel.x, x) &&
           AssertEq(red_pixel.y, y);
  });

  framework->AddTest("Save canvas to PPM", [framework]() -> bool {
    Canvas canvas = {500, 300};

    Color blue = {0, 0.34f, 0.72f};
    Color yellow = {1, 0.85f, 0};

    int stripe_thickness = 20;

    for (int j = 0; j < canvas.height; ++j) {
      for (int i = 0; i < canvas.width; ++i) {
        if ((i / stripe_thickness + j / stripe_thickness) % 2 == 0) {
          canvas.WritePixelColor(i, j, blue);
        } else {
          canvas.WritePixelColor(i, j, yellow);
        }
      }
    }

    std::string file_path = framework->root_folder_path + "\\data\\canvas.ppm";
    bool res = canvas.SaveToPPM(file_path);

    return AssertEq(res, true);
  });

  framework->AddTest("Load canvas from PPM", [framework]() -> bool {
    Canvas canvas = {0, 0};

    std::string input_file_path =
        framework->root_folder_path + "\\data\\canvas.ppm";
    bool res1 = canvas.LoadFromPPM(input_file_path);

    std::string output_file_path =
        framework->root_folder_path + "\\data\\canvas_output.ppm";
    bool res2 = canvas.SaveToPPM(output_file_path);

    bool are_files_same = CompareFiles(input_file_path, output_file_path);

    return AssertEq(are_files_same, res1 == res2);
  });

  framework->AddTest("Map the trajectory of projectile", [framework]() -> bool {
    Canvas canvas = {900, 550};

    Projectile proj;
    // proj.position = {0.1f, static_cast<float>(canvas.height), 0};
    proj.position = {0.0f, 1.0f, 0.0f};
    proj.velocity = {1.0f, 1.8f, 0.0f};
    proj.velocity = proj.velocity.Normalize() * 11.25f;

    Environment env;
    env.gravity = {0.0f, -0.1f, 0.0f};
    env.wind = {-0.01f, 0.0f, 0.0f};

    Color red = {1.0f, 0.0f, 0.0f};

    while (proj.position.y > 0.0f) {
      int pos_x = static_cast<int>(floor(proj.position.x));
      int pos_y = static_cast<int>(floor(proj.position.y));
      pos_y = static_cast<int>(abs(canvas.height - floor(proj.position.y)));

      if (canvas.IsPixelInRange(pos_x, pos_y)) {
        canvas.WritePixelColor(pos_x, pos_y, red);
      }

      proj.position = proj.position + proj.velocity;
      proj.velocity = proj.velocity + env.gravity + env.wind;
    }

    std::string output_file_path =
        framework->root_folder_path + "\\data\\projectile.ppm";
    bool res = canvas.SaveToPPM(output_file_path);

    return AssertEq(res, true);
  });
}
