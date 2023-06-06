#include "CLI.hpp"
#include "engine.hpp"

// CLI interface
int main(int argc, char **argv) {
    CLI::App app{"App description"};

    // Define options
    std::string inp = "res/examples/testing.ng";
    app.add_option("-i", inp, "Input file");

    std::string out = "";
    app.add_option("-o", out, "Output file");

    CLI11_PARSE(app, argc, argv);

    // Define options
    engine::parse(inp);
    engine::printElements();
    string htmlFile = engine::generatePage();

    if (out == "") {
      cout << htmlFile;
    } else {
      ofstream fout{out}; // this is dangerous and can overwrite files
      fout << htmlFile;
    }

    return 0;
}
