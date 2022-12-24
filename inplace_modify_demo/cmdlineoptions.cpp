#include "cmdlineoptions.h"
#include "utilities.h"

#include <codecvt>

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

using namespace std;

bool CCmdLineOptions::Parse(int argc, char** argv)
{
    CLI::App app{ "inplace_modify_demo" };

    std::string czi_filename;
    app.add_option("-f,--filename", czi_filename, "The CZI-file to be processed.")
        ->check(CLI::ExistingFile)
        ->required();

    try
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e)
    {
        app.exit(e);
        return false;
    }

    this->czi_filename_ = convertToWide(czi_filename);
    return true;
}

const std::wstring& CCmdLineOptions::GetCZIFilenameW() const
{
    return this->czi_filename_;
}